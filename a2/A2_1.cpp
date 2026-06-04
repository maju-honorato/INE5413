#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include "grafo_dir.hpp"

void DFSVisit(Grafo &G, int v, std::vector<bool> &C, std::vector<double> &T, std::vector<int> &A, std::vector<double> &F,
              int &tempo, std::vector<int> *componenteAtual = nullptr) {
    C[v] = true;
    tempo++;
    T[v] = tempo;

    if (componenteAtual != nullptr) {
      componenteAtual->push_back(v);
    }

    std::vector<int> vizinhos = G.vizinhos(v);
    for (int i = 0; i < vizinhos.size(); i++) {
      int u = vizinhos[i];
      if (C[u] == false) {
        A[u] = v;
        DFSVisit(G, u, C, T, A, F, tempo, componenteAtual);
      }
    }

    tempo++;
    F[v] = tempo;
}

void DFS(Grafo &G, std::vector<bool> &C, std::vector<double> &T, std::vector<int> &A, std::vector<double> &F) {
  int n = G.qtdVertices();

  for (int v = 1; v <= n; v++) {
    C[v] = false;
    T[v] = std::numeric_limits<double>::infinity();
    F[v] = std::numeric_limits<double>::infinity();
    A[v] = -1;
  }

  int tempo = 0;

  for (int u = 1; u <= n; u++) {
    if (C[u] == false) {
      DFSVisit(G, u, C, T, A, F, tempo);
    }
  }
}

void KosarajuSharir(Grafo &G) {
  int n = G.qtdVertices();

  std::vector<bool> C(n + 1);
  std::vector<double> T(n + 1);
  std::vector<double> F(n + 1);
  std::vector<int> A(n + 1);

  DFS(G, C, T, A, F);

  Grafo GT = G.transposta();

  std::vector<int> ordemVertices(n);
  for (int i = 0; i < n; i++) {
    ordemVertices[i] = i + 1;
  }
  std::sort(ordemVertices.begin(), ordemVertices.end(), [&](int a, int b) {
    return F[a] > F[b];
  });

  std::vector<bool> C_GT(n + 1, false);
  std::vector<double> T_GT(n + 1, std::numeric_limits<double>::infinity());
  std::vector<double> F_GT(n + 1, std::numeric_limits<double>::infinity());
  std::vector<int> A_GT(n + 1, -1);
  int tempo_GT = 0;

  for (int i = 0; i < ordemVertices.size(); i++) {
    int u = ordemVertices[i];

    if (C_GT[u] == false) {
      std::vector<int> componente;

      DFSVisit(GT, u, C_GT, T_GT, A_GT, F_GT, tempo_GT, &componente);

      for (int j = 0; j < componente.size(); j++) {
        std::cout << componente[j];
        if (j < componente.size() - 1) {
          std::cout << ",";
        }
      }
      std::cout << std::endl;
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    return 1;
  }

  std::string filename = argv[1];

  Grafo g;
  g.ler(filename);

  KosarajuSharir(g);

  return 0;
}