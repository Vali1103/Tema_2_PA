#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int MAXN = 1e5 + 5;
int N, Q;
vector<int> adj[MAXN];
vector<int> tin(MAXN), tout(MAXN);
int timer = 0;

// parcurgerea in adancime a unui nod primit ca parametru
void dfs(int node, int parent) {
    tin[node] = ++timer;
    for (int child : adj[node]) {
        if (child != parent) {
            dfs(child, node);
        }
    }
    tout[node] = timer;
}

int main() {
    ifstream fin("magazin.in");
    ofstream fout("magazin.out");
    // citesc nr de noduri si nr de interogari
    fin >> N >> Q;

    // imi creez matricea de adiacenta din vectorul pe care il citesc
    for (int i = 2, parent; i <= N; ++i) {
        fin >> parent;
        adj[parent].push_back(i);
    }

    dfs(1, 0);  // realizam parcurgerea în adzncime a arborelui.

    vector<int> index_to_node(N+1);
    for (int i = 1; i <= N; i++) {
        index_to_node[tin[i]] = i;
    }

    for (int i = 0, x, y; i < Q; ++i) {
        // citesc interogarile
        fin >> x >> y;
        int pos = tin[x] + y;
        // Daca pozitia este in intervalul DFS al nodului x,
        // atunci nodul y este un descendent al lui x in ordinea DFS.
        if (pos <= tout[x]) {
            fout << index_to_node[pos] << "\n";
        } else {
            fout << -1 << "\n";
        }
    }

    fout.close();
    fin.close();
    return 0;
}
