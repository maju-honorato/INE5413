#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "A1_1.hpp"

void bfs(Grafo& g, int s) {
    int n = g.qtdVertices();

    std::vector<bool> C(n + 1, false);
    std::vector<double> D(n + 1, std::numeric_limits<double>::infinity());
    std::vector<int> A(n + 1, -1);
    std::vector<std::vector<int>> niveis_encontrados;

    C[s] = true;
    D[s] = 0;

    std::queue<int> Q;
    Q.push(s);

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        if (D[u] >= niveis_encontrados.size()) {
            niveis_encontrados.resize(D[u] + 1);
        }
        niveis_encontrados[D[u]].push_back(u);

        std::vector<int> vizinhos = g.vizinhos(u);
        std::sort(vizinhos.begin(), vizinhos.end());

        for (int i = 0; i < vizinhos.size(); i++) {
            int v = vizinhos[i];
            if (C[v] == false) {
                C[v] = true;
                D[v] = D[u] + 1;
                A[v] = u;
                Q.push(v);
            }
        }
    }

    for (int i = 0; i < niveis_encontrados.size(); i++) {
        std::sort(niveis_encontrados[i].begin(), niveis_encontrados[i].end());
        std::cout << i << ": ";

        for (int j = 0; j < niveis_encontrados[i].size(); j++) {
            std::cout << niveis_encontrados[i][j];
            if (j < niveis_encontrados[i].size() - 1) {
                std::cout << ",";
            }
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        return 1;
    }

    std::string fileName = argv[1];
    int s = std::stoi(argv[2]);

    Grafo g;
    g.ler(fileName);

    bfs(g, s);

    return 0;
}