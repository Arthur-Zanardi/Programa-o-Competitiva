#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// ============================================================================
// 1. ESTRUTURA BÁSICA DE PONTO / VETOR
// ============================================================================
struct PT {
    ll x, y;
    
    PT() : x(0), y(0) {}
    PT(ll x, ll y) : x(x), y(y) {}

    // Sobrecarga de operadores matemáticos
    PT operator+(const PT& p) const { return PT(x + p.x, y + p.y); }
    PT operator-(const PT& p) const { return PT(x - p.x, y - p.y); }
    PT operator*(ll c) const { return PT(x * c, y * c); }
    PT operator/(ll c) const { return PT(x / c, y / c); }

    // Ordenação lexicográfica (necessária para o Convex Hull)
    // Ordena primeiro pelo X, e em caso de empate, pelo Y
    bool operator<(const PT& p) const {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
    
    bool operator==(const PT& p) const {
        return x == p.x && y == p.y;
    }
};

// ============================================================================
// 2. PRODUTOS VETORIAL E ESCALAR (O Coração da Geometria)
// ============================================================================

// Produto Escalar (Dot Product): a.x*b.x + a.y*b.y
// Utilidade: Acha o ângulo entre vetores, projeções e testa perpendicularidade (dot == 0).
ll dot(PT a, PT b) {
    return a.x * b.x + a.y * b.y;
}

// Produto Vetorial (Cross Product) magnitude 2D: a.x*b.y - a.y*b.x
// Utilidade: Retorna a área (com sinal) do paralelogramo formado por a e b.
// Se > 0: 'b' está à esquerda de 'a' (sentido anti-horário)
// Se < 0: 'b' está à direita de 'a' (sentido horário)
// Se == 0: os vetores são colineares
ll cross(PT a, PT b) {
    return a.x * b.y - a.y * b.x;
}

// Verifica a orientação do turno de 'A' para 'B' indo em direção a 'C'.
// Retorna a área com sinal do triângulo formado por A, B e C (multiplicada por 2)
ll orientation(PT a, PT b, PT c) {
    return cross(b - a, c - a);
}

// Retorna verdadeiro se o ponto C está à esquerda do segmento AB (virada anti-horária)
bool is_left(PT a, PT b, PT c) {
    return orientation(a, b, c) > 0;
}

// ============================================================================
// 3. DISTÂNCIAS (Quando o ponto flutuante é inevitável)
// ============================================================================
double dist(PT a, PT b) {
    return hypot(a.x - b.x, a.y - b.y);
}

ll dist_sq(PT a, PT b) {
    return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

// ============================================================================
// 4. CONVEX HULL (Andrew's Monotone Chain)
// Encontra o polígono convexo de menor área que engloba todos os pontos.
// Complexidade: O(N log N) para ordenar + O(N) para construir.
// ============================================================================
vector<PT> convex_hull(vector<PT>& pts) {
    int n = pts.size(), k = 0;
    if (n <= 2) return pts;

    vector<PT> hull(2 * n); // Tamanho máximo suportado com segurança

    // 1. Ordena os pontos lexicograficamente
    sort(pts.begin(), pts.end());

    // 2. Constrói o Lower Hull (Parte inferior)
    for (int i = 0; i < n; ++i) {
        // Enquanto os últimos 2 pontos da casca e o ponto atual NÃO fizerem uma curva à esquerda...
        // Mude para <= 0 se quiser incluir pontos colineares na borda do Convex Hull
        while (k >= 2 && orientation(hull[k - 2], hull[k - 1], pts[i]) <= 0) {
            k--; // Remove o ponto ruim
        }
        hull[k++] = pts[i];
    }

    // 3. Constrói o Upper Hull (Parte superior)
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && orientation(hull[k - 2], hull[k - 1], pts[i]) <= 0) {
            k--;
        }
        hull[k++] = pts[i];
    }

    // O último ponto do Upper Hull é igual ao primeiro do Lower Hull, então redimensionamos removendo-o
    hull.resize(k - 1);
    return hull;
}#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// ============================================================================
// 1. ESTRUTURA BÁSICA DE PONTO / VETOR
// ============================================================================
struct PT {
    ll x, y;
    
    PT() : x(0), y(0) {}
    PT(ll x, ll y) : x(x), y(y) {}

    // Sobrecarga de operadores matemáticos
    PT operator+(const PT& p) const { return PT(x + p.x, y + p.y); }
    PT operator-(const PT& p) const { return PT(x - p.x, y - p.y); }
    PT operator*(ll c) const { return PT(x * c, y * c); }
    PT operator/(ll c) const { return PT(x / c, y / c); }

    // Ordenação lexicográfica (necessária para o Convex Hull)
    // Ordena primeiro pelo X, e em caso de empate, pelo Y
    bool operator<(const PT& p) const {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
    
    bool operator==(const PT& p) const {
        return x == p.x && y == p.y;
    }
};

// ============================================================================
// 2. PRODUTOS VETORIAL E ESCALAR (O Coração da Geometria)
// ============================================================================

// Produto Escalar (Dot Product): a.x*b.x + a.y*b.y
// Utilidade: Acha o ângulo entre vetores, projeções e testa perpendicularidade (dot == 0).
ll dot(PT a, PT b) {
    return a.x * b.x + a.y * b.y;
}

// Produto Vetorial (Cross Product) magnitude 2D: a.x*b.y - a.y*b.x
// Utilidade: Retorna a área (com sinal) do paralelogramo formado por a e b.
// Se > 0: 'b' está à esquerda de 'a' (sentido anti-horário)
// Se < 0: 'b' está à direita de 'a' (sentido horário)
// Se == 0: os vetores são colineares
ll cross(PT a, PT b) {
    return a.x * b.y - a.y * b.x;
}

// Verifica a orientação do turno de 'A' para 'B' indo em direção a 'C'.
// Retorna a área com sinal do triângulo formado por A, B e C (multiplicada por 2)
ll orientation(PT a, PT b, PT c) {
    return cross(b - a, c - a);
}

// Retorna verdadeiro se o ponto C está à esquerda do segmento AB (virada anti-horária)
bool is_left(PT a, PT b, PT c) {
    return orientation(a, b, c) > 0;
}

// ============================================================================
// 3. DISTÂNCIAS (Quando o ponto flutuante é inevitável)
// ============================================================================
double dist(PT a, PT b) {
    return hypot(a.x - b.x, a.y - b.y);
}

ll dist_sq(PT a, PT b) {
    return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

// ============================================================================
// 4. CONVEX HULL (Andrew's Monotone Chain)
// Encontra o polígono convexo de menor área que engloba todos os pontos.
// Complexidade: O(N log N) para ordenar + O(N) para construir.
// ============================================================================
vector<PT> convex_hull(vector<PT>& pts) {
    int n = pts.size(), k = 0;
    if (n <= 2) return pts;

    vector<PT> hull(2 * n); // Tamanho máximo suportado com segurança

    // 1. Ordena os pontos lexicograficamente
    sort(pts.begin(), pts.end());

    // 2. Constrói o Lower Hull (Parte inferior)
    for (int i = 0; i < n; ++i) {
        // Enquanto os últimos 2 pontos da casca e o ponto atual NÃO fizerem uma curva à esquerda...
        // Mude para <= 0 se quiser incluir pontos colineares na borda do Convex Hull
        while (k >= 2 && orientation(hull[k - 2], hull[k - 1], pts[i]) <= 0) {
            k--; // Remove o ponto ruim
        }
        hull[k++] = pts[i];
    }

    // 3. Constrói o Upper Hull (Parte superior)
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && orientation(hull[k - 2], hull[k - 1], pts[i]) <= 0) {
            k--;
        }
        hull[k++] = pts[i];
    }

    // O último ponto do Upper Hull é igual ao primeiro do Lower Hull, então redimensionamos removendo-o
    hull.resize(k - 1);
    return hull;
}
