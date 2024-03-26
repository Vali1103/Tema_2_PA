#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

const int NMAX = (int)1e5 + 5;  // NMAX reprezintă dimensiunea
// maximă posibilă a problemei (100000)

// Variabilele globale necesare pentru rezolvarea problemei
int n, m;  // n este numărul de task-uri, iar m este numărul de dependențe
vector<int> adj[NMAX];  // lista de adiacență pentru a stoca dependențele
int in_degree[NMAX], task_set[NMAX];
// in_degree reține numărul de noduri de intrare pentru fiecare nod (task),
//  iar task_set reține setul de date necesar fiecărui task
queue<int> q[3];  // un vector de cozi pentru a reține
                    // task-urile care necesită fiecare set de date

// Funcția de rezolvare care primește un set curent de task-uri și
// returnează numărul minim de comutări de context necesare
int solve(queue<int> q[3], int in_degree[NMAX], int current_set) {
    int switches = 0;  // numărător pentru comutările de context
    while (q[1].size() + q[2].size() > 0) {
        // cât timp mai sunt task-uri de procesat
        if (q[current_set].empty()) {
            // dacă nu mai sunt task-uri care necesită setul curent de date
            current_set = 3 - current_set;  // comutăm setul de date
            switches++;  // și incrementăm numărul de comutări
        }
        // preluăm task-ul curent
        int node = q[current_set].front(); q[current_set].pop();
        for (auto it : adj[node]) {
            // pentru fiecare task care depinde de task-ul curent
            in_degree[it]--;
            // reducem numărul de noduri de intrare
            if (in_degree[it] == 0) {
                // dacă task-ul nu mai are alte dependențe
                q[task_set[it]].push(it);
                // îl adăugăm la coada corespunzătoare setului său de date
            }
        }
    }

    return switches;  // returnăm numărul total de comutări de context
}

int main() {
    ifstream fin("supercomputer.in");  // deschidem fișierul de intrare
    ofstream fout("supercomputer.out");  // deschidem fișierul de ieșire

    // citim datele problemei, nr de noduri si muchii
    // apoi nr de dependente de probleme
    fin >> n >> m;
    for (int i = 1; i <= n; i++) {
        fin >> task_set[i];
    }

    for (int i = 0; i < m; i++) {  // citim dependențele
        int u, v;  // u este task-ul de la care depinde v
        fin >> u >> v;
        adj[u].push_back(v);  // adăugăm dependența în lista de adiacență
        in_degree[v]++;  // și incrementăm numărul de noduri de intrare pentru v
    }
    fin.close();
    // Adăugăm task-urile care nu au noduri de intrare în cozile corespunzătoare
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            q[task_set[i]].push(i);
        }
    }

    // Creăm copii lui in_degree și a cozilor
    // pentru a putea rula solve cu diferite seturi de pornire
    int in_degree_copy[NMAX];
    copy(begin(in_degree), end(in_degree), begin(in_degree_copy));
    queue<int> q1[3] = { q[0], q[1], q[2] };
    queue<int> q2[3] = { q[0], q[1], q[2] };

    // Rulăm solve cu ambele seturi de pornire
    // și reținem numărul de comutări pentru fiecare
    int switches1 = solve(q1, in_degree_copy, 1);
    copy(begin(in_degree), end(in_degree), begin(in_degree_copy));
    int switches2 = solve(q2, in_degree_copy, 2);

    // Scriem numărul minim de comutări în fișierul de ieșire
    fout << min(switches1, switches2);
    fout.close();
    return 0;
}
