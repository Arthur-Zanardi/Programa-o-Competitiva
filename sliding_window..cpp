
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;

// Macro para Policy-Based Data Structure (útil para Mediana e Custo em O(log N))
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

// 1. Sliding Window Sum (Prefix Sum / Acumulador) - O(1)
vector<long long> slidingWindowSum(const vector<int>& a, int k) {
    vector<long long> ans;
    long long sum = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        sum += a[i];
        if (i >= k - 1) {
            ans.push_back(sum);
            sum -= a[i - k + 1];
        }
    }
    return ans;
}

// 2. Sliding Window Minimum (Monotonic Queue) - O(1) amortizado
vector<int> slidingWindowMinimum(const vector<int>& a, int k) {
    vector<int> ans;
    deque<int> dq; // Guarda os índices dos elementos
    for (int i = 0; i < (int)a.size(); i++) {
        // Remove elementos que saíram da janela
        if (!dq.empty() && dq.front() == i - k) dq.pop_front();
        
        // Mantém a fila estritamente crescente
        while (!dq.empty() && a[dq.back()] >= a[i]) dq.pop_back();
        
        dq.push_back(i);
        if (i >= k - 1) ans.push_back(a[dq.front()]);
    }
    return ans;
}

// 3. Sliding Window Distinct Values - O(1)
vector<int> slidingWindowDistinct(const vector<int>& a, int k) {
    vector<int> ans;
    unordered_map<int, int> freq; // Pode ser array puro se max(A[i]) for pequeno
    int distinct_cnt = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        if (freq[a[i]] == 0) distinct_cnt++;
        freq[a[i]]++;
        
        if (i >= k - 1) {
            ans.push_back(distinct_cnt);
            freq[a[i - k + 1]]--;
            if (freq[a[i - k + 1]] == 0) distinct_cnt--;
        }
    }
    return ans;
}

// 4. Sliding Window Median (PBDS) - O(log N)
vector<int> slidingWindowMedian(const vector<int>& a, int k) {
    vector<int> ans;
    ordered_set os;
    for (int i = 0; i < (int)a.size(); i++) {
        os.insert({a[i], i});
        if (i >= k - 1) {
            // Pega a mediana (k/2 se for 0-indexed, adaptável para par/ímpar)
            ans.push_back(os.find_by_order((k - 1) / 2)->first);
            os.erase({a[i - k + 1], i - k + 1});
        }
    }
    return ans;
}

// 5. Estrutura de Apoio: Fenwick Tree (BIT) para Sliding Window Inversions - O(log N)
struct FenwickTree {
    int n; 
    vector<int> bit;
    FenwickTree(int n) : n(n), bit(n + 1, 0) {}
    
    void add(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) bit[idx] += val;
    }
    
    int query(int idx) {
        int sum = 0;
        for (; idx > 0; idx -= idx & -idx) sum += bit[idx];
        return sum;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> arr = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;

    cout << "Array Original: ";
    for(int x : arr) cout << x << " ";
    cout << "\nTamanho da Janela (K): " << k << "\n\n";

    vector<long long> sums = slidingWindowSum(arr, k);
    cout << "1. Somas (O(1)):\n";
    for(auto x : sums) cout << x << " ";
    cout << "\n\n";

    vector<int> mins = slidingWindowMinimum(arr, k);
    cout << "2. Minimos via Monotonic Queue (O(1)):\n";
    for(int x : mins) cout << x << " ";
    cout << "\n\n";

    vector<int> meds = slidingWindowMedian(arr, k);
    cout << "3. Medianas via PBDS (O(log N)):\n";
    for(int x : meds) cout << x << " ";
    cout << "\n\n";


    return 0;
}
