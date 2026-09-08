#include <bits/stdc++.h>
using namespace std;
 
// Usamos 1e17 para evitar overflow quando somarmos os pesos (que vão até 10^9)
const long long INF = 1e17;  
const long long NINF = -1e17; // Nosso "Menos Infinito"

struct Aresta {
    int u, v;
    long long w;
};

int n, m;
vector<Aresta> arestas;
vector<long long> distancias;

void bellmanFord() {
    // Inicializamos com -Infinito, pois queremos maximizar
    distancias.assign(n + 1, NINF);
    distancias[1] = 0; // A sala inicial tem pontuação 0

    // FASE 1: Encontrar as maiores distâncias possíveis (n-1 vezes)
    for (int i = 1; i < n; i++) {
        for (auto edge : arestas) {
            if (distancias[edge.u] != NINF) {
                // Relaxamento invertido: se achar um caminho MAIOR, atualiza!
                if (distancias[edge.u] + edge.w > distancias[edge.v]) {
                    distancias[edge.v] = distancias[edge.u] + edge.w;
                }
            }
        }
    }

    // FASE 2: Propagação do Infinito (n vezes)
    // Se a gente AINDA consegue aumentar alguma pontuação, é um ciclo positivo.
    // Vamos marcar com INF e deixar isso se espalhar pelo grafo.
    for (int i = 1; i <= n; i++) {
        for (auto edge : arestas) {
            if (distancias[edge.u] != NINF) {
                // Se a origem do túnel já virou infinito OU se a pontuação aumentou
                if (distancias[edge.u] == INF || distancias[edge.u] + edge.w > distancias[edge.v]) {
                    distancias[edge.v] = INF;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);

    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        arestas.push_back({u, v, w});
    }

    bellmanFord();

    // Se o nó de destino foi contagiado pelo ciclo positivo
    if (distancias[n] == INF) {
        cout << -1 << "\n";
    } else {
        cout << distancias[n] << "\n";
    }

    return 0;
}
