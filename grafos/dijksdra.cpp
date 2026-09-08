#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int n, m;
vector<vector<pair<int, long long>>> adj;
vector<long long> distancias;

void dijkstra(int inicio) {

  priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> fila;
    
    distancias[inicio] = 0;
    fila.push({0, inicio});

    while (!fila.empty()) {
        long long d_atual = fila.top().first;
        int u = fila.top().second;
        fila.pop();

        if (d_atual > distancias[u]) continue;

        for (auto aresta : adj[u]) {
            int v = aresta.first;
            long long w = aresta.second;

            if (distancias[u] + w < distancias[v]) {
                distancias[v] = distancias[u] + w;
                fila.push({distancias[v], v});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);

    cin >> n >> m;

    adj.assign(n + 1, vector<pair<int, long long>>());
    distancias.assign(n + 1, INF);

    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        
        adj[u].push_back({v, w});
        // adj[v].push_back({u, w}); // Descomente para grafos bidirecionais
    }

    // Chama o Dijkstra saindo do nó 1
    dijkstra(1);

    for(int i = 1; i <= n; i++) {
        cout << distancias[i] << " ";
    }
    cout << "\n";

    return 0;
}
