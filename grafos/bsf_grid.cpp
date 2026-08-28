#include <bits/stdc++.h>
using namespace std;

int dRow[] = {1, -1, 0, 0};
int dCol[] = {0, 0, 1, -1};

int l, c;

vector<vector<char>> mapa;
vector<vector<int>> visited;

void bfs(int i, int j) {


    queue<pair<int, int>> fila;
    if(mapa[i][j] == '.' && visited[i][j] == 0) {
        fila.push({i,j});
        visited[i][j] = 1;
    } else {
        return; 
    }

    while(!fila.empty()) {

        pair<int,int> frente = fila.front();
        fila.pop();

        for(int x = 0; x < 4; x++) {
            int newRow = frente.first+dRow[x]; 
            int newCol = frente.second+dCol[x]; 
            if(newRow >= 0 && newCol >= 0 && newRow < l && newCol <= c) {
                bfs(i+dRow[x],j+dCol[x]);
            };
        };
    }
};

int main() {
    cin >> l >> c;

    mapa.assign(l, vector<char>(c, ' '));
    visited.assign(l, vector<int>(c, 0));

    for(int i = 0; i < l; i++) {
        for(int j = 0; j < c; j++) {
            cin >> mapa[i][j];
        }   
    }
    
    return 0;
}