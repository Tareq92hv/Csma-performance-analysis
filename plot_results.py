import csv
import matplotlib.pyplot as plt

nodes = []
throughput = []
delay = []
packet_loss = []

with open('results.csv', 'r') as file:
    reader = csv.DictReader(file)
    for row in reader:
        nodes.append(int(row['Nodes']))
        throughput.append(float(row['Throughput_Mbps']))
        delay.append(float(row['AverageDelay_ms']))
        packet_loss.append(float(row['PacketLoss_percent']))

# Throughput vs Nodes
plt.figure()
plt.plot(nodes, throughput, marker='o')
plt.xlabel("Number of Nodes")
plt.ylabel("Throughput (Mbps)")
plt.title("Throughput vs Number of Nodes")
plt.grid(True)
plt.savefig("throughput_vs_nodes.png")
plt.close()

# Delay vs Nodes
plt.figure()
plt.plot(nodes, delay, marker='o')
plt.xlabel("Number of Nodes")
plt.ylabel("Average Delay (ms)")
plt.title("Average Delay vs Number of Nodes")
plt.grid(True)
plt.savefig("delay_vs_nodes.png")
plt.close()

# Packet Loss vs Nodes
plt.figure()
plt.plot(nodes, packet_loss, marker='o')
plt.xlabel("Number of Nodes")
plt.ylabel("Packet Loss (%)")
plt.title("Packet Loss vs Number of Nodes")
plt.grid(True)
plt.savefig("packet_loss_vs_nodes.png")
plt.close()

print("Diagrams created successfully.")

