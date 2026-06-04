#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include "grafo_n_dir.hpp"

void Kruskal(Grafo &G) {
  int n = G.qtdVertices();

  std::vector<int> A_u;
  std::vector<int> A_v;
  std::vector<std::vector<int>> S(n + 1);

  for (int v = 1; v <= n; v++) {
    S[v].push_back(v);
  }

  std::vector<int> E_u;
  std::vector<int> E_v;

  for (int u = 1; u <= n; u++) {
    std::vector<int> vizinhos = G.vizinhos(u);
    for (int i = 0; i < vizinhos.size(); i++) {
      int v = vizinhos[i];
      if (u < v) {
        E_u.push_back(u);
        E_v.push_back(v);
      }
    }
  }

  std::vector<int> ordemVertices(E_u.size());
  for (int i = 0; i < ordemVertices.size(); i++) {
    ordemVertices[i] = i;
  }

  std::sort(ordemVertices.begin(), ordemVertices.end(), [&](int a, int b) {
    return G.peso(E_u[a], E_v[a]) < G.peso(E_u[b], E_v[b]);
  });

  double somaPeso = 0.0;

  for (int i = 0; i < ordemVertices.size(); i++) {
    int idx = ordemVertices[i];
    int u = E_u[idx];
    int v = E_v[idx];

    bool mesmoConjunto = false;
    for (int j = 0; j < S[u].size(); j++) {
      if (S[u][j] == v) {
        mesmoConjunto = true;
        break;
      }
    }

    if (!mesmoConjunto) {
      A_u.push_back(u);
      A_v.push_back(v);
      somaPeso += G.peso(u, v);

      std::vector<int> x = S[u];
      for (int j = 0; j < S[v].size(); j++) {
        x.push_back(S[v][j]);
      }

      for (int j = 0; j < x.size(); j++) {
        int y = x[j];
        S[y] = x;
      }
    }
  }

  std::cout << somaPeso << std::endl;
  for (int i = 0; i < A_u.size(); i++) {
    std::cout << A_u[i] << "-" << A_v[i];
    if (i < A_u.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << std::endl;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    return 1;
  }

  std::string filename = argv[1];

  Grafo g;
  g.ler(filename);

  Kruskal(g);

  return 0;
}