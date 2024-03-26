#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

int N, M, S;
// lista de adiacență pentru graful original
vector<int> adj[MAXN];
// lista de adiacență pentru graful invers
vector<int> rev[MAXN];
// lista de adiacență a Componentelor Tare Conexe (CTC)
vector<int> SCC[MAXN];
// pentru a urmări nodurile vizitate în timpul DFS
bool visited[MAXN];
// pentru a mapa fiecare nod la CTC-ul său
int comp[MAXN];
vector<int> order, component;
int numSCC;  // numărul de CTC-uri

// DFS pentru graful original
void dfs1(int v) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u])
            dfs1(u);
    }
    order.push_back(v);
}

// DFS pentru graful invers
void dfs2(int v, int c) {
    comp[v] = c;
    for (int u : rev[v]) {
        if (comp[u] == -1)
            dfs2(u, c);
    }
}

int main() {
    ifstream fin("ferate.in");
    ofstream fout("ferate.out");

    // Citirea numarului de noduri, muchii și nodul sursă
    fin >> N >> M >> S;
    // Citirea muchiilor de la u la v
    for (int i = 1, u, v; i <= M; i++) {
        fin >> u >> v;
        adj[u].push_back(v);
        rev[v].push_back(u);
    }

    memset(comp, -1, sizeof comp);
    for (int i = 1; i <= N; i++)
        if (!visited[i])
            dfs1(i);  // DFS pentru graful original
    for (int i = 1; i <= N; i++) {
        int v = order[N - i];
        if (comp[v] == -1)
            dfs2(v, numSCC++);  // DFS pentru graful invers
    }

    // Construirea listei de adiacență a CTC-urilor
    for (int i = 1; i <= N; i++)
        for (int j : adj[i])
            if (comp[i] != comp[j])
                SCC[comp[i]].push_back(comp[j]);

    vector<bool> isSource(numSCC, true);
    for (int i = 0; i < numSCC; i++)
        for (int j : SCC[i])
            isSource[j] = false;

    int cnt = 0;
    for (bool b : isSource)
        if (b)
            cnt++;

    fout << cnt << "\n";

    fin.close();
    fout.close();

    return 0;
}
