#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <algorithm>
#include "A1_1.hpp"

void bellmanFord(Grafo &g, int s) {
  int n = g.qtdVertices();

  std::vector<double> D(n + 1, std::numeric_limits<double>::infinity());
  std::vector<int> A(n + 1, -1);
  D[s] = 0;

  for (int i = 1; i <= n; i++) {
    for (int u = 1; u <= n; u++) {
      std::vector<int> vizinhos_u = g.vizinhos(u);

      for (int j = 0; j < vizinhos_u.size(); j++) {
        int v = vizinhos_u[j];
        double peso_uv = g.peso(u, v);

        if (D[u] != std::numeric_limits<double>::infinity() && D[v] > D[u] + peso_uv) {
          D[v] = D[u] + peso_uv;
          A[v] = u;
        }
      }
    }
  }

  for (int u = 1; u <= n; u++) {
    std::vector<int> vizinhos_u = g.vizinhos(u);
    for (int j = 0; j < vizinhos_u.size(); j++) {
      int v = vizinhos_u[j];
      if (D[u] != std::numeric_limits<double>::infinity() && D[v] > D[u] + g.peso(u, v)) {
          return;
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    std::cout << i << ": ";
    if (D[i] == std::numeric_limits<double>::infinity()) {
      continue;
    }

    std::vector<int> caminho;
    for (int c = i; c != -1; c = A[c]) {
      caminho.push_back(c);
    }

    std::reverse(caminho.begin(), caminho.end());
    for (int j = 0; j < caminho.size(); j++) {
      std::cout << caminho[j] << (j == caminho.size() - 1 ? "" : ",");
    }

    std::cout << "; d=" << D[i] << std::endl;
  }
}

int main(int argc, char * argv[]) {
  if (argc < 3) {
    return 1;
  }

  Grafo g;
  g.ler(argv[1]);
  int s = std::stoi(argv[2]);

  if (s <= 0 || s > g.qtdVertices()) {
    return 1;
  }

  bellmanFord(g, s);
  return 0;
}