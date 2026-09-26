#include <bits/stdc++.h>
using namespace std;

// ============================================================================
// 1. BOILERPLATE (Template Base)
// ============================================================================
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define fst first
#define snd second

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int INF = 1e9 + 7;
const ll LINF = 1e18 + 7LL;
const int MOD = 1e9 + 7;

// Chama isso no início da main() sempre!
void fastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

// ============================================================================
// 2. DISJOINT SET UNION (DSU)
// Complexidade: O(alpha(N)) amortizado por operação (~ O(1))
// ============================================================================
struct DSU {
    vector<int> parent, size;
    
    DSU(int n) {
        parent.resize(n + 1);
        size.assign(n + 1, 1);
        iota(all(parent), 0); // Preenche com 0, 1, 2, ..., n
    }
    
    // Busca com compressão de caminho
    int find(int v) {
        if (v == parent[v]) return v;
        return parent[v] = find(parent[v]); 
    }
    
    // União por tamanho
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (size[a] < size[b]) swap(a, b);
            parent[b] = a;
            size[a] += size[b];
            return true;
        }
        return false; // Já estavam no mesmo conjunto
    }
};

// ============================================================================
// 3. FENWICK TREE (Binary Indexed Tree - BIT)
// Utilidade: Soma de prefixos e atualização pontual em O(log N)
// OBS: BIT trabalha com índices 1-based (1 até N)
// ============================================================================
struct BIT {
    int n;
    vector<ll> tree;
    
    BIT(int n) : n(n) { tree.assign(n + 1, 0); }
    
    // Adiciona 'delta' na posição 'i'
    void update(int i, ll delta) {
        for (; i <= n; i += i & -i)
            tree[i] += delta;
    }
    
    // Retorna a soma de 1 até 'i'
    ll query(int i) {
        ll sum = 0;
        for (; i > 0; i -= i & -i)
            sum += tree[i];
        return sum;
    }
    
    // Retorna a soma no intervalo [l, r]
    ll query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

// ============================================================================
// 4. SEGMENT TREE (com Lazy Propagation)
// Utilidade: Consultas e atualizações em intervalos [l, r] em O(log N)
// Este exemplo faz atualizações de SOMA e consultas de SOMA.
// OBS: Trabalha com índices 0-based (0 até N-1)
// ============================================================================
struct SegTreeLazy {
    int n;
    vector<ll> tree, lazy;
    
    SegTreeLazy(int n) : n(n) {
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }
    
    void push(int node, int l, int r) {
        if (lazy[node] != 0) {
            // Aplica a alteração no nó atual (ex: soma lazy * tamanho do intervalo)
            tree[node] += lazy[node] * (r - l + 1); 
            
            // Se não for folha, propaga para os filhos
            if (l != r) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            // Reseta a lazy do nó atual
            lazy[node] = 0;
        }
    }
    
    void update(int node, int l, int r, int ql, int qr, ll val) {
        push(node, l, r); // Limpa as pendências antes de prosseguir
        
        if (l > qr || r < ql) return; // Fora do intervalo
        
        if (l >= ql && r <= qr) { // Totalmente dentro do intervalo
            lazy[node] += val;
            push(node, l, r);
            return;
        }
        
        // Interseção parcial
        int mid = (l + r) / 2;
        update(2 * node, l, mid, ql, qr, val);
        update(2 * node + 1, mid + 1, r, ql, qr, val);
        
        // Atualiza o pai
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
    
    ll query(int node, int l, int r, int ql, int qr) {
        push(node, l, r); // Limpa pendências ao descer
        
        if (l > qr || r < ql) return 0; // Neutro da operação (0 para soma)
        if (l >= ql && r <= qr) return tree[node];
        
        int mid = (l + r) / 2;
        ll p1 = query(2 * node, l, mid, ql, qr);
        ll p2 = query(2 * node + 1, mid + 1, r, ql, qr);
        return p1 + p2;
    }
    
    // Funções Wrapper (Para chamar na main passando apenas o intervalo e valor)
    void update(int l, int r, ll val) { update(1, 0, n - 1, l, r, val); }
    ll query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

// ============================================================================
// EXEMPLO DE USO NA MAIN
// ============================================================================
int main() {
    fastIO();
    
    // Exemplo: Problema com N elementos e M queries
    int n, m;
    if (cin >> n >> m) {
        // Inicializa as estruturas (escolha a necessária para o problema)
        // DSU dsu(n);
        // BIT bit(n); // Lembre-se, BIT de 1 a n
        // SegTreeLazy st(n); // Lembre-se, SegTree de 0 a n-1
        
        // Loop das queries
        while(m--) {

        }
    }
    
    return 0;
}
