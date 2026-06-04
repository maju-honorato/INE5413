#include <iostream>
#include <vector>
#include <limits>
#include "A1_1.hpp"

void floydWarshall(Grafo& g) {
    int n = g.qtdVertices();

    std::vector<std::vector<double>> D(n + 1, std::vector<double>(n + 1, std::numeric_limits<double>::infinity()));
    for (int u = 1; u <= n; u++) {
        D[u][u] = 0;

        std::vector<int> vizinhos = g.vizinhos(u);
        for (int i = 0; i < vizinhos.size(); i++) {
            int v = vizinhos[i];
            D[u][v] = g.peso(u, v);
        }
    }

    for (int k = 1; k <= n; k++) {
        std::vector<std::vector<double>> Dk = D;

        for (int u = 1; u <= n; u++) {
            for (int v = 1; v <= n; v++) {
                double soma = std::numeric_limits<double>::infinity();
                if (D[u][k] != std::numeric_limits<double>::infinity() && D[k][v] != std::numeric_limits<double>::infinity()) {
                    soma = D[u][k] + D[k][v];
                }

                if (soma < Dk[u][v]) {
                    Dk[u][v] = soma;
                }
            }
        }

        D = Dk;
    }

    for (int i = 1; i <= n; i++) {
        std::cout << i << ":";
        for (int j = 1; j <= n; j++) {
            std::cout << D[i][j];

            if (j < n) {
                std::cout << ",";
            }
        }

        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }

    Grafo g;
    g.ler(argv[1]);
    floydWarshall(g);
    return 0;
}