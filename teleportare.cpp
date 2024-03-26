#include <fstream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
#define INF 2000000000

using namespace std;

vector<vector<pair<int, int>>> adj;
// Graful de adiacenta cu muchiile obisnuite
vector<vector<pair<int, int>>> tp;
// Graful de adiacenta cu teleportari
vector<int> dist;
// Distanta minima de la nodul 1 pana la fiecare nod

int main() {
    ifstream in("teleportare.in");
    ofstream out("teleportare.out");

    int N, M, K;
    in >> N >> M >> K;

    adj.resize(N + 1);
    tp.resize(N + 1);
    dist.resize(N + 1, INF);
    // Initializam toate distantele cu INF

    // Citim muchiile
    for (int i = 0; i < M; ++i) {
        int X, Y, T;
        in >> X >> Y >> T;
        adj[X].push_back({Y, T});
        adj[Y].push_back({X, T});
    }

    // Citim teleportarile
    for (int i = 0; i < K; ++i) {
        int X, Y, P;
        in >> X >> Y >> P;
        tp[X].push_back({Y, P});
        tp[Y].push_back({X, P});
    }

    // Coada de prioritati pentru algoritmul Dijkstra
    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
            > pq;

    dist[1] = 0;  // Distanta de la nodul 1 la el însuși este 0
    pq.push({0, 1});  // Incepem Dijkstra de la nodul 1

    // Implementarea algoritmului Dijkstra
    while (!pq.empty()) {
        int u = pq.top().second;  // Nodul curent
        int d = pq.top().first;  // Distanta pana la nodul curent
        pq.pop();

        // Ignoram muchiile care au fost scoase din coada, dar nu sunt optime
        if (d != dist[u]) continue;

        // Parcurgem toate muchiile obisnuite
        for (auto edge : adj[u]) {
            int v = edge.first;  // Nodul vecin
            int w = edge.second;  // Costul muchiei

            // Daca putem imbunatati distanta pana la nodul vecin
            // o imbunatatim si adaugam nodul vecin in coada
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }

        // Parcurgem toate teleportarile
        for (auto edge : tp[u]) {
            int v = edge.first;  // Nodul in care ne teleportam
            int w = edge.second;  // Periodicitatea teleportarii
            int wait = (dist[u] % w == 0) ? 0 : w - (dist[u] % w);
            // Timpul pe care il asteptam pana la urmatoarea teleportare

            // Daca putem imbunatati distanta pana la
            // nodul in care ne teleportam, o imbunatatim si adaugam nodul
            if (dist[u] + wait + 1 < dist[v]) {
                dist[v] = dist[u] + wait + 1;
                pq.push({dist[v], v});
            }
        }
    }

    out << dist[N] << "\n";

    return 0;
}
