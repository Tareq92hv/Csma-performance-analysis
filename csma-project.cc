#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/csma-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("CsmaExtendedProject");

int main (int argc, char *argv[])
{
    uint32_t nNodes = 5;
    CommandLine cmd;
    cmd.AddValue ("nNodes", "Number of CSMA nodes", nNodes);
    cmd.Parse (argc, argv);

    NodeContainer nodes;
    nodes.Create (nNodes);

    CsmaHelper csma;
    csma.SetChannelAttribute ("DataRate", StringValue ("10Mbps"));
    csma.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (1)));

    NetDeviceContainer devices = csma.Install (nodes);

    InternetStackHelper internet;
    internet.Install (nodes);

    Ipv4AddressHelper ipv4;
    ipv4.SetBase ("10.1.1.0", "255.255.255.0");
    ipv4.Assign (devices);

    // === SERVER ===
    uint16_t port = 9;
    UdpEchoServerHelper server (port);
    ApplicationContainer serverApp = server.Install (nodes.Get (0));
    serverApp.Start (Seconds (1.0));
    serverApp.Stop (Seconds (30.0));

    // === CLIENTS (HÖG BELASTNING) ===
    for (uint32_t i = 1; i < nNodes; ++i)
    {
        UdpEchoClientHelper client (
            Ipv4Address ("10.1.1.1"), port);

        client.SetAttribute ("MaxPackets", UintegerValue (100000));
        client.SetAttribute ("Interval", TimeValue (MilliSeconds (1))); // aggressiv trafik
        client.SetAttribute ("PacketSize", UintegerValue (1024));

        ApplicationContainer app = client.Install (nodes.Get (i));
        app.Start (Seconds (2.0));
        app.Stop (Seconds (30.0));
    }

    FlowMonitorHelper flowmon;
    Ptr<FlowMonitor> monitor = flowmon.InstallAll ();

    Simulator::Stop (Seconds (30.0));
    Simulator::Run ();

    monitor->CheckForLostPackets ();
    Ptr<Ipv4FlowClassifier> classifier =
        DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
    FlowMonitor::FlowStatsContainer stats = monitor->GetFlowStats ();

    double totalRxBytes = 0;
    double totalDelay = 0;
    uint64_t totalRxPackets = 0;
    uint64_t totalTxPackets = 0;
    std::vector<double> delays;

    for (auto &flow : stats)
    {
        totalRxBytes += flow.second.rxBytes;
        totalRxPackets += flow.second.rxPackets;
        totalTxPackets += flow.second.txPackets;

        if (flow.second.rxPackets > 0)
        {
            totalDelay += flow.second.delaySum.GetSeconds ();
            delays.push_back (
                flow.second.delaySum.GetSeconds () /
                flow.second.rxPackets);
        }
    }

    double throughput =
        (totalRxBytes * 8.0) / (28.0 * 1e6); // Mbps

    double avgDelay = totalDelay / totalRxPackets;

    double variance = 0;
    for (double d : delays)
        variance += pow (d - avgDelay, 2);
    variance /= delays.size ();

    std::sort (delays.begin (), delays.end ());
    double p95 = delays[(uint32_t)(0.95 * delays.size ())];

    double packetLoss =
        100.0 * (totalTxPackets - totalRxPackets) / totalTxPackets;

    std::cout << "Nodes: " << nNodes << std::endl;
    std::cout << "Throughput: " << throughput << " Mbps" << std::endl;
    std::cout << "Average Delay: " << avgDelay * 1000 << " ms" << std::endl;
    std::cout << "Packet Loss Rate: " << packetLoss << " %" << std::endl;
    std::cout << "Delay Variance: " << variance * 1e6 << " (ms^2)" << std::endl;
    std::cout << "95th Percentile Delay: " << p95 * 1000 << " ms" << std::endl;

    Simulator::Destroy ();
    return 0;
}

