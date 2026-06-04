#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include "grafo_dir.hpp"

void DFSVisit_OT(Grafo &G, int v, std::vector<bool> &C, std::vector<double> &T, std::vector<double> &F, int &tempo,
                std::vector<int> &O) {
  C[v] = true;
  tempo++;
  T[v] = tempo;

  std::vector<int> vizinhos = G.vizinhos(v);
  for (int i = 0; i < vizinhos.size(); i++) {
    int u = vizinhos[i];
    if (C[u] == false) {
      DFSVisit_OT(G, u, C, T, F, tempo, O);
    }
  }

  tempo++;
  F[v] = tempo;
  O.insert(O.begin(), v);
}

std::vector<int> DFS_OT(Grafo &G) {
  int n = G.qtdVertices();

  std::vector<bool> C(n + 1);
  std::vector<double> T(n + 1);
  std::vector<double> F(n + 1);

  for (int v = 1; v <= n; v++) {
    C[v] = false;
    T[v] = std::numeric_limits<double>::infinity();
    F[v] = std::numeric_limits<double>::infinity();
  }

  int tempo = 0;
  std::vector<int> O;

  for (int u = 1; u <= n; u++) {
    if (C[u] == false) {
      DFSVisit_OT(G, u, C, T, F, tempo, O);
    }
  }

  for (int i = 0; i < O.size(); i++) {
    int v = O[i];
    std::cout << G.rotulo(v);

    if (i < O.size() - 1) {
      std::cout << " , ";
    }
  }
  std::cout << std::endl;

  return O;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    return 1;
  }

  std::string filename = argv[1];

  Grafo g;
  g.ler(filename);

  DFS_OT(g);

  return 0;
}