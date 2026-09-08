#include <bits/stdc++.h>
using namespace std;
 
const int INF = 1e9; // Usamos 1 bilhão para simular o "infinito"

int n, m;
vector<vector<int>> distancias;

void floydWarshall() {
    // A essência do Floyd-Warshall:
    // k = Nó intermediário
    // i = Nó de origem
    // j = Nó de destino
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                
                // Só tentamos atualizar se for possível chegar até k e de k até j
                if (distancias[i][k] != INF && distancias[k][j] != INF) {
                    if (distancias[i][k] + distancias[k][j] < distancias[i][j]) {
                        distancias[i][j] = distancias[i][k] + distancias[k][j];
                    }
                }
                
            }
        }
    }
}

int main() {
    // A sua clássica otimização vital para os juízes online
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);

    cin >> n >> m;

    // Inicializa a matriz de distâncias (1-indexada, então tamanho n+1) com infinito
    distancias.assign(n + 1, vector<int>(n + 1, INF));

    // A distância de um nó para ele mesmo é sempre 0
    for(int i = 1; i <= n; i++) {
        distancias[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        
        // Em problemas de grafos pesados, pode haver duas ruas ligando u e v, 
        // então sempre salvamos a rua de MENOR peso (min).
        // * Se o grafo for direcionado, tire a segunda linha.
        distancias[u][v] = min(distancias[u][v], w); 
        distancias[v][u] = min(distancias[v][u], w); 
    }
    
    // Roda a mágica
    floydWarshall();

    // Printando a matriz de adjacência final para você visualizar
    cout << "\nMatriz de Menores Caminhos:\n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (distancias[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << distancias[i][j] << " ";
            }
        }
        cout << "\n";
    }

    return 0;
}
