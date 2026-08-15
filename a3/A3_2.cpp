#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <queue>
#include <algorithm>
#include "ndir_npon.hpp"

bool bfs(Grafo &G, const std::vector<int> & X, std::vector<int> &mate, std::vector<int> &D) {
    std::queue<int> Q;
    int n = G.qtdVertices();
    
    for (int i = 0; i < X.size(); i++) {
        int x = X[i];
        
        if (mate[x] == 0) {
            D[x] = 0;
            Q.push(x);
        } else {
            D[x] = std::numeric_limits<int>::max();
        }
    }
    
    D[0] = std::numeric_limits<int>::max();
    while (!Q.empty()) {
        int x = Q.front();
        Q.pop();
        
        if (D[x] < D[0]) {
            std::vector<int> vizinhos = G.vizinhos(x);
            for (int i = 0; i < vizinhos.size(); i++) {
                int y = vizinhos[i];
                
                if (D[mate[y]] == std::numeric_limits<int>::max()) {
                    D[mate[y]] = D[x] + 1;
                    Q.push(mate[y]);
                }
            }
        }
    }
    
    return D[0] != std::numeric_limits<int>::max();
}

bool dfs(Grafo &G, std::vector<int> &mate, int x, std::vector<int> &D) {
    if (x != 0) {
        int n = G.qtdVertices();
        std::vector<int> vizinhos = G.vizinhos(x);
        for (int i = 0; i < vizinhos.size(); i++) {
            int y = vizinhos[i];
            
            if (D[mate[y]] == D[x] + 1) {
                if (dfs(G, mate, mate[y], D)) {
                    mate[y] = x;
                    mate[x] = y;
                    return true;
                }
            }
        }
        
        D[x] = std::numeric_limits<int>::max();
        return false;
    }
    
    return true;
}

void algoritmoHopcroftKarp(Grafo &G) {
    int n = G.qtdVertices();
    
    std::vector<int> X;
    int limiteX = n / 2;
    for (int i = 1; i <= limiteX; i++) {
        X.push_back(i);
    }
    
    std::vector<int> D(n + 1, std::numeric_limits<int>::max());
    std::vector<int> mate(n + 1, 0);
    
    int m = 0;
    
    while (bfs(G, X, mate, D)) {
        for (int i = 0; i < X.size(); i++) {
            int x = X[i];
            if (mate[x] == 0) {
                if (dfs(G, mate, x, D)) {
                    m = m + 1;
                }
            }
        }
        
        std::fill(D.begin(), D.end(), std::numeric_limits<int>::max());
    }
    
    std::cout << m << std::endl;
    
    bool primeiraAresta = true;
    for (int i = 0; i < X.size(); i++) {
        int x = X[i];
        
        if (mate[x] != 0) {
            if (!primeiraAresta) {
                std::cout << ", ";
            }
            
            std::cout << x << "-" << mate[x];
            primeiraAresta = false;
        }
    }
    
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }
    
    Grafo g;
    g.ler(argv[1]);
    
    algoritmoHopcroftKarp(g);
    
    return 0;
}