#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
const ll LINF = 1e18 + 7LL;

// 1. BUSCAS BÁSICAS (DFS e BFS)
// Úteis para encontrar componentes conexos, ciclos ou menor caminho (sem peso).
struct GraphBasics {
    int n;
    vector<vector<int>> adj;
    vector<bool> vis;
    vector<int> dist; // Para BFS

    GraphBasics(int n) : n(n), adj(n), vis(n, false), dist(n, -1) {}

    void add_edge(int u, int v, bool directed = false) {
        adj[u].push_back(v);
        if (!directed) adj[v].push_back(u);
    }

    void dfs(int u) {
        vis[u] = true;
        for (int v : adj[u]) {
            if (!vis[v]) {
                dfs(v);
            }
        }
    }

    void bfs(int start) {
        queue<int> q;
        q.push(start);
        vis[start] = true;
        dist[start] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (!vis[v]) {
                    vis[v] = true;
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
    }
};

// 2. DIJKSTRA (Menor Caminho em Grafo com Pesos Positivos)
// Complexidade: O(E log V)
struct Dijkstra {
    int n;
    vector<vector<pair<int, ll>>> adj; // adj[u] = {v, peso}
    vector<ll> dist;
    vector<int> parent; // Para reconstruir o caminho

    Dijkstra(int n) : n(n), adj(n), dist(n, LINF), parent(n, -1) {}

    void add_edge(int u, int v, ll w, bool directed = false) {
        adj[u].push_back({v, w});
        if (!directed) adj[v].push_back({u, w});
    }

    void run(int start) {
        dist.assign(n, LINF);
        parent.assign(n, -1);
        priority_queue<pli, vector<pli>, greater<pli>> pq; // {distancia, vertice}

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[u]) continue; // Otimização importante

            for (auto edge : adj[u]) {
                int v = edge.first;
                ll w = edge.second;

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }
};

// 3. KRUSKAL (Árvore Geradora Mínima - MST)
// Requer a struct DSU (Disjoint Set Union) implementada anteriormente.
// Complexidade: O(E log E)
struct Edge {
    int u, v;
    ll w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

ll kruskal(int n, vector<Edge>& edges) {
    // DSU dsu(n); // Instancie o seu DSU aqui
    sort(edges.begin(), edges.end());
    ll mst_cost = 0;
    int edges_used = 0;

    for (Edge e : edges) {
        /* Descomente quando colocar o DSU junto:
        if (dsu.unite(e.u, e.v)) {
            mst_cost += e.w;
            edges_used++;
            if (edges_used == n - 1) break;
        }
        */
    }
    return mst_cost;
}

// ============================================================================
// 4. LOWEST COMMON ANCESTOR (LCA) - Binary Lifting
// Funciona apenas em ÁRVORES (grafos conexos e acíclicos).
// Complexidade: Pré-processamento O(N log N) | Consulta O(log N)
// ============================================================================
struct LCA {
    int n, l;
    vector<vector<int>> adj;
    int timer;
    vector<int> tin, tout;
    vector<vector<int>> up; // up[v][i] é o (2^i)-ésimo ancestral de v

    LCA(int n) : n(n), adj(n), timer(0) {
        tin.resize(n);
        tout.resize(n);
        l = ceil(log2(n));
        up.assign(n, vector<int>(l + 1));
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int v, int p) {
        tin[v] = ++timer;
        up[v][0] = p;
        for (int i = 1; i <= l; ++i)
            up[v][i] = up[up[v][i-1]][i-1];

        for (int u : adj[v]) {
            if (u != p) dfs(u, v);
        }
        tout[v] = ++timer;
    }

    bool is_ancestor(int u, int v) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }

    int query(int u, int v) {
        if (is_ancestor(u, v)) return u;
        if (is_ancestor(v, u)) return v;
        for (int i = l; i >= 0; --i) {
            if (!is_ancestor(up[u][i], v))
                u = up[u][i];
        }
        return up[u][0];
    }

    void build(int root = 0) {
        dfs(root, root);
    }
};

// 5. ORDENAÇÃO TOPOLÓGICA (Kahn's Algorithm)
// Usado em Grafos Direcionados Acíclicos (DAGs) para dependência de tarefas.
// Complexidade: O(V + E)

struct TopoSort {
    int n;
    vector<vector<int>> adj;
    vector<int> in_degree;

    TopoSort(int n) : n(n), adj(n), in_degree(n, 0) {}

    void add_edge(int u, int v) { // Grafo DIRECIONADO
        adj[u].push_back(v);
        in_degree[v]++;
    }

    // Retorna a ordem topológica ou um vetor vazio se houver ciclo
    vector<int> sort() {
        queue<int> q;
        vector<int> order;

        for (int i = 0; i < n; i++) {
            if (in_degree[i] == 0) q.push(i);
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);

            for (int v : adj[u]) {
                in_degree[v]--;
                if (in_degree[v] == 0) q.push(v);
            }
        }

        // Se order.size() < n, o grafo tem ciclo e não é um DAG
        if (order.size() < (size_t)n) return {}; 
        return order;
    }
};
