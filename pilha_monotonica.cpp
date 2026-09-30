#include <bits/stdc++.h>


using namespace std;

vector<int> monotonic_stack_template(const vector<int>& arr) {
    int n = arr.size();
    
    vector<int> next_greater(n, -1); 
    
    // A pilha guarda sempre os ÍNDICES, nunca os valores diretamente.
    stack<int> st;
        // alterar aqui muda a direção
    for (int i = 0; i < n; i++) {
                                    // alterar aqui muda o parametro. resto tá certo
        while (!st.empty() && arr[i] > arr[st.top()]) {
            int prev_index = st.top();
            st.pop();
            
            // O elemento no índice 'i' é o próximo maior para o 'prev_index'
            next_greater[prev_index] = i; 
        }
        
        // Coloca o índice atual na stack como uma nova "pendência"
        st.push(i);
    }

    return next_greater;
}
