# 📡 ns-3 CSMA Performance Analysis

This repository contains the complete simulation code, datasets, and analysis scripts used in the IEEE-style paper:

**Performance Evaluation of CSMA Networks Using ns-3**

The project evaluates the scalability and performance of Carrier Sense Multiple Access (CSMA)-based networks under increasing contention (number of nodes) using the ns-3 discrete-event network simulator.

---

## 🗃️ Repository Contents

| Filnamn | Beskrivning |
| :--- | :--- |
| `csma-project.cc` | ns-3 simuleringskod (C++). Ska placeras i ns-3:s `scratch/` katalog. |
| `results.csv` | Insamlade simuleringsresultat, inklusive throughput, delay, packet loss rate, delay variance, och percentiler. |
| `plot_results.py` | Python-skript för att generera alla prestandadiagram från `results.csv`. |
| `README.md` | Instruktioner för byggnation, körning och reproduktion av simuleringarna. |

---

## 💻 Systemkrav

### Programvara
* Ubuntu 22.04 LTS (rekommenderas)
* ns-3 version 3.39 eller senare
* Python 3.8 eller senare

### Python-beroenden
Installera nödvändiga Python-paket för plottning och datahantering:
```bash
sudo apt install python3-matplotlib python3-pandas

Hur man Bygger och Kör Simuleringen
Följ stegen nedan för att reproducera alla resultat som presenteras i rapporten.

1. Klona Repository
Klona projektet till din lokala maskin:
git clone [https://github.com/Tareq92hv/Csma-performance-analysis.git](https://github.com/Tareq92hv/Csma-performance-analysis.git)
cd Csma-performance-analysis

2. Kopiera Simuleringskoden till ns-3
Kopiera simuleringsfilen till scratch/ katalogen i din ns-3 installation (ersätt ~/ns-3-dev/ med din ns-3 root-katalog om den är annorlunda):
cp csma-project.cc ~/ns-3-dev/scratch/

3. Kör Simuleringarna
Navigera till ns-3:s rotkatalog och kör simuleringen för de tre konfigurerade nodantal som användes i studien:
cd ~/ns-3-dev
./ns3 run "csma-project --nNodes=5"
./ns3 run "csma-project --nNodes=10"
./ns3 run "csma-project --nNodes=20"
Notera: Varje simuleringskörning uppdaterar filen results.csv. Se till att köra alla tre för att få kompletta data.

Utgående Mätvärden
Varje simuleringskörning genererar följande prestandamått:

Throughput (Mbps)

Average end-to-end delay (ms)

Packet loss rate (%)

Delay variance

95th percentile delay

Generera Prestandadiagram
Efter att ha kört alla simuleringar, använd Python-skriptet för att generera diagrammen:
python3 plot_results.py
Detta skript producerar följande figurer i PNG-format:

throughput_vs_nodes.png

delay_vs_nodes.png

packet_loss_vs_nodes.png

Reproduktionsanteckningar
Alla simuleringar använder identiska trafik- och nätverksparametrar.

Random number generator seeds är fixerade för att säkerställa reproducerbarhet.

Simuleringens varaktighet, paketgenereringshastighet och CSMA-parametrar dokumenteras direkt i csma-project.cc.

Detta projekt tillhandahålls endast för akademiska och utbildningssyften.

🔗 Hur man Citerar
Vänligen citera detta repository i din rapport med följande BibTeX-format:
@misc{csma_ns3_repo,
  author = {Tareq Karaja},
  title  = {CSMA Performance Analysis using ns-3},
  year   = {2025},
  url    = {[https://github.com/Tareq92hv/Csma-performance-analysis](https://github.com/Tareq92hv/Csma-performance-analysis)}
}
