#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <queue>
#include <algorithm>
#include "dir_pon.hpp"

std::vector<int> bfs(int n, const std::vector<std::vector<double>> &cf, int s, int t) {
    std::vector<bool> C(n + 1, false);
    std::vector<int> A(n + 1, -1);

    C[s] = true;
    std::queue<int> Q;
    Q.push(s);

    while (!Q.empty()) {
      int u = Q.front();
      Q.pop();

      for (int v = 1; v <= n; v++) {
        if (C[v] == false && cf[u][v] > 0) {
          C[v] = true;
          A[v] = u;

          if (v == t) {
            std::vector<int> p;
            p.push_back(t);
            int w = t;

            while (w != s) {
              w = A[w];
              p.insert(p.begin(), w);
            }
        
            return p;
          }

          Q.push(v);
        }
      }
    }
    
    return std::vector<int>();
}
 
double edmondsKarp(Grafo &G, int s, int t) {
  int n = G.qtdVertices();

  std::vector<std::vector<double>> cf(n + 1, std::vector<double>(n + 1, 0.0));
  
  for (int u = 1; u <= n; u++) {
    std::vector<int> vizinhos = G.vizinhos(u);
    
    for (size_t i = 0; i < vizinhos.size(); i++) {
      int v = vizinhos[i];
      
      double pesoOriginal = G.peso(u, v);
      if (pesoOriginal != std::numeric_limits<double>::infinity()) {
            cf[u][v] = pesoOriginal;
      }
    }
  }
  
  double F = 0;

  while (true) {
    std::vector<int> p = bfs(n, cf, s, t);

    if (p.empty()) {
      break;
    }

    double fp = std::numeric_limits<double>::infinity();
    for (size_t i = 0; i < p.size() - 1; i++) {
      int u = p[i];
      int v = p[i + 1];
      fp = std::min(fp, cf[u][v]);
    }
    
    F = F + fp;

    for (size_t i = 0; i < p.size() - 1; i++) {
      int u = p[i];
      int v = p[i + 1];

      cf[u][v] = cf[u][v] - fp;
      cf[v][u] = cf[v][u] + fp;
    }
  }
  
  return F;
}

int main(int argc, char* argv[]) {
  if (argc < 4) {
    return 1;
  }

  std::string filename = argv[1];
  int s = std::stoi(argv[2]);
  int t = std::stoi(argv[3]);

  Grafo g;
  g.ler(filename);

  double resultado = edmondsKarp(g, s, t);

  std::cout << resultado << std::endl;

  return 0;
}