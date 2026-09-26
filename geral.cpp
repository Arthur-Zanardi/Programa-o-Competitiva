#include <bits/stdc++.h>
using namespace std;

int main() {
    // 1. PRIORITY QUEUE (Fila de Prioridade) - Essencial para Greedy
    // Max-Heap (Padrão: o maior sai primeiro)
    priority_queue<int> max_pq; 
    
    // Min-Heap (O menor sai primeiro - o mais usado em Dijkstra e Greedy)
    priority_queue<int, vector<int>, greater<int>> min_pq;

    // 2. SET e MAP (Árvores de Busca Binária Red-Black)
    // Mantém os elementos ordenados. Inserção, busca e remoção em O(log N).
    set<int> s;
    map<string, int> m;
    
    // UNORDERED (Hash Tables) - Mais rápidos O(1), mas não mantêm ordem.
    unordered_set<int> us;
    unordered_map<string, int> um;

    // 3. BUSCA BINÁRIA EM VETORES ORDENADOS (Extremamente útil em DP e Greedy)
    vector<int> v = {10, 20, 30, 30, 40, 50};
    
    // lower_bound: Retorna iterador para o PRIMEIRO elemento >= X
    auto it_low = lower_bound(v.begin(), v.end(), 30); // Aponta para o primeiro 30
    
    // upper_bound: Retorna iterador para o PRIMEIRO elemento > X
    auto it_up = upper_bound(v.begin(), v.end(), 30); // Aponta para o 40
    
    // Pegando o índice inteiro:
    int idx = distance(v.begin(), it_low); // ou simplesmente: it_low - v.begin()
}

//////////////

struct Evento {
    int inicio, fim, id;
    
    // Método 1: Sobrecarga do operador < direto na struct
    // Retorna true se 'este' evento deve vir ANTES do 'outro'
    bool operator<(const Evento& outro) const {
        if (fim != outro.fim) return fim < outro.fim;
        return inicio < outro.inicio; // Desempate
    }
};

// Método 2: Função de comparação externa (útil para pairs ou vetores comuns)
bool comp_customizada(pair<int, int> a, pair<int, int> b) {
    // Ordena pelo segundo elemento em ordem decrescente
    return a.second > b.second;
}

void solve_greedy() {
    vector<Evento> eventos = {{1, 4, 1}, {3, 5, 2}, {0, 6, 3}, {5, 7, 4}};
    
    // Ordena usando o operator< da struct
    sort(eventos.begin(), eventos.end());
    
    int eventos_escolhidos = 0;
    int ultimo_fim = -1;
    
    for (Evento e : eventos) {
        if (e.inicio >= ultimo_fim) { // Não sobrepõe
            eventos_escolhidos++;
            ultimo_fim = e.fim;
        }
    }
}

const int MAXN = 1005;
const int MAXW = 1005;
int memo[MAXN][MAXW];
int pesos[MAXN], valores[MAXN];
int n; // Quantidade de itens

// Exemplo: Knapsack 0/1 (Mochila)
int dp(int idx, int cap_restante) {
    // 1. Casos Base (Fim da recursão)
    if (idx == n || cap_restante == 0) return 0;
    
    // 2. Estado já calculado?
    if (memo[idx][cap_restante] != -1) return memo[idx][cap_restante];
    
    // 3. Transições
    int nao_pega = dp(idx + 1, cap_restante);
    int pega = 0;
    
    if (pesos[idx] <= cap_restante) {
        pega = valores[idx] + dp(idx + 1, cap_restante - pesos[idx]);
    }
    
    // 4. Salva e retorna o melhor resultado (DP de maximização)
    return memo[idx][cap_restante] = max(pega, nao_pega);
}

void solve_dp_topdown() {
    // Seta todos os bytes para -1. Só funciona com -1 ou 0 para inteiros!
    memset(memo, -1, sizeof(memo)); 
    // int ans = dp(0, capacidade_total);
}


// Exemplo: Longest Common Subsequence (LCS)
int lcs_bottom_up(string s1, string s2) {
    int n1 = s1.size(), n2 = s2.size();
    
    // Matriz (n1+1) x (n2+1) inicializada com 0
    vector<vector<int>> dp_table(n1 + 1, vector<int>(n2 + 1, 0));
    
    for (int i = 1; i <= n1; i++) {
        for (int j = 1; j <= n2; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                // Match: Pega o valor da diagonal + 1
                dp_table[i][j] = dp_table[i - 1][j - 1] + 1;
            } else {
                // No match: Pega o melhor do vizinho de cima ou da esquerda
                dp_table[i][j] = max(dp_table[i - 1][j], dp_table[i][j - 1]);
            }
        }
    }
    return dp_table[n1][n2];
}
