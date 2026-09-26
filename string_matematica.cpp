#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;

// ============================================================================
// 1. MATEMÁTICA E TEORIA DOS NÚMEROS
// ============================================================================

// 1.1 Exponenciação Modular (Fast Pow)
// Calcula (base^exp) % mod em O(log exp). Essencial para combinatória e inversos.
ll fast_pow(ll base, ll exp, ll mod = MOD) {
    ll res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

// 1.2 Inverso Modular
// Funciona apenas se 'a' e 'm' forem coprimos (geralmente 'm' é primo).
// Baseado no Pequeno Teorema de Fermat: a^(m-2) ≡ a^-1 (mod m)
ll mod_inverse(ll a, ll m = MOD) {
    return fast_pow(a, m - 2, m);
}

// 1.3 Crivo de Eratóstenes Clássico + Fatoração em O(log N)
// Pré-processamento O(N log log N).
struct Sieve {
    int n;
    vector<bool> is_prime;
    vector<int> primes;
    vector<int> spf; // Smallest Prime Factor (Fator Primo Mais Jovem)

    Sieve(int n) : n(n) {
        is_prime.assign(n + 1, true);
        spf.assign(n + 1, 0);
        is_prime[0] = is_prime[1] = false;
        
        for (int i = 2; i <= n; i++) spf[i] = i;

        for (int p = 2; p * p <= n; p++) {
            if (is_prime[p]) {
                for (int i = p * p; i <= n; i += p) {
                    is_prime[i] = false;
                    if (spf[i] == i) spf[i] = p; // Guarda o menor divisor primo
                }
            }
        }
        
        for (int p = 2; p <= n; p++) {
            if (is_prime[p]) primes.push_back(p);
        }
    }

    // Fatoração de um número em O(log X) usando o SPF
    vector<int> factorize(int x) {
        vector<int> factors;
        while (x != 1) {
            factors.push_back(spf[x]);
            x /= spf[x];
        }
        return factors;
    }
};

// ============================================================================
// 2. STRINGS
// ============================================================================

// 2.1 KMP (Knuth-Morris-Pratt)
// Encontra ocorrências de uma string (pattern) dentro de outra (text) em O(N + M).
struct KMP {
    // Função de Prefixo (Pi Array)
    // pi[i] = tamanho do maior prefixo próprio que também é sufixo até a posição i
    static vector<int> prefix_function(string s) {
        int n = (int)s.length();
        vector<int> pi(n, 0);
        for (int i = 1; i < n; i++) {
            int j = pi[i - 1];
            while (j > 0 && s[i] != s[j])
                j = pi[j - 1];
            if (s[i] == s[j])
                j++;
            pi[i] = j;
        }
        return pi;
    }

    // Retorna todos os índices (0-based) onde 'pattern' começa em 'text'
    static vector<int> search(string text, string pattern) {
        string s = pattern + "#" + text;
        vector<int> pi = prefix_function(s);
        vector<int> occurrences;
        
        int p_len = pattern.length();
        for (int i = p_len + 1; i < s.length(); i++) {
            if (pi[i] == p_len) {
                // i é o final do match na string concatenada
                occurrences.push_back(i - 2 * p_len);
            }
        }
        return occurrences;
    }
};

// 2.2 Hashing de Strings (Polynomial Rolling Hash)
// Pré-processamento O(N), permite comparar qualquer substring em O(1).
// Usar base 31 (ou 37, 53) e módulo grande ajuda a evitar colisões.
struct StringHash {
    const int p = 31;
    const int m = 1e9 + 9;
    vector<ll> p_pow, h;

    StringHash(string const& s) {
        int n = s.length();
        p_pow.assign(n, 1);
        for (int i = 1; i < n; i++) 
            p_pow[i] = (p_pow[i - 1] * p) % m;

        h.assign(n + 1, 0);
        for (int i = 0; i < n; i++)
            h[i + 1] = (h[i] + (s[i] - 'a' + 1) * p_pow[i]) % m;
    }

    // Retorna o hash da substring s[l...r] (índices 0-based)
    ll query(int l, int r) {
        ll hash_val = (h[r + 1] - h[l] + m) % m;
        // Normalizamos multiplicando pelo inverso modular ou comparamos ajustando as potências
        // O truque comum para evitar o inverso é multiplicar o menor hash pelas potências que faltam
        return hash_val; 
    }
    
    // Verifica se s[l1...r1] é igual a s[l2...r2]
    bool is_equal(int l1, int r1, int l2, int r2) {
        if (r1 - l1 != r2 - l2) return false;
        ll h1 = query(l1, r1);
        ll h2 = query(l2, r2);
        
        // Em vez de dividir, multiplicamos para balancear as potências de p
        if (l1 < l2) 
            h1 = (h1 * p_pow[l2 - l1]) % m;
        else 
            h2 = (h2 * p_pow[l1 - l2]) % m;
            
        return h1 == h2;
    }
};
