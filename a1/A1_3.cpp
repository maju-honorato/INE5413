#include <iostream>
#include <vector>
#include <list>
#include <string>
#include "A1_1.hpp"

std::pair<bool, std::list<int>> buscarSubciclo(Grafo& g, int v, std::vector<std::vector<int>>& C){
  std::list<int> Ciclo;
  Ciclo.push_back(v);
  int t = v;

  do {
    int u = -1;
    std::vector<int> vizinhos = g.vizinhos(v);

    for (int i = 0; i < vizinhos.size(); i++) {
        int viz = vizinhos[i];
        if (C[v][viz] > 0) {
            u = viz;
            break;
        }
    }

    if (u == -1) {
      return {false, {}};
    }

    C[v][u]--;
    C[u][v]--;
    v = u;
    Ciclo.push_back(v);

  } while (v != t);

  for (auto it = Ciclo.begin(); it != Ciclo.end(); it++) {
    int x = *it;
    bool arestaSobrando = false;

    std::vector<int> vizinhos_x = g.vizinhos(x);
    for (int i = 0; i < vizinhos_x.size(); i++) {
      int viz = vizinhos_x[i];
      if (C[x][viz] > 0) {
        arestaSobrando = true;
        break;
      }
    }

    if (arestaSobrando) {
      auto r = buscarSubciclo(g, x, C);
      if (!r.first) {
        return {false, {}};
      }

        std::list<int> ciclo_linha = r.second;
        ciclo_linha.pop_front();
        auto prox_it = std::next(it);
        Ciclo.splice(prox_it, ciclo_linha);
    }
  }
  return {true, Ciclo};
}

void hierholzer(Grafo&g) {
  int n = g.qtdVertices();
  int m = g.qtdArestas();

  if (m == 0) {
    std::cout << "1" << std::endl;
    return;
  }

  for (int i = 1; i <= n; i++) {
    if (g.grau(i) % 2 != 0) {
      std::cout << "0" << std::endl;
      return;
    }
  }

  std::vector<std::vector<int>> C(n + 1, std::vector<int>(n + 1, 0));
  for (int u = 1; u <= n; u++) {
    std::vector<int> adj = g.vizinhos(u);
    for (int j = 0; j < adj.size(); j++) {
      int v = adj[j];

      if (u < v) {
        C[u][v] = 1;
        C[v][u] = 1;
      }
    }
  }

  int v_inicial = -1;
  for (int i = 1; i <= n; i++) {
    if (g.grau(i) > 0) {
      v_inicial = i;
      break;
    }
  }

  if (v_inicial == -1) {
    std::cout << "1" << std::endl;
    return;
  }

  auto final_res = buscarSubciclo(g, v_inicial, C);
  bool r = final_res.first;
  bool arestaSobrou = false;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (C[i][j] > 0) {
        arestaSobrou = true;
      }
    }
  }

  if (!r || arestaSobrou) {
    std::cout << "0" << std::endl;
  } else {
    std::cout << "1" << std::endl;
    std::list<int> res_ciclo = final_res.second;
    std::vector<int> resultado_final(res_ciclo.begin(), res_ciclo.end());

    for (int j = 0; j < resultado_final.size(); j++) {
      std::cout << resultado_final[j];
      if (j < resultado_final.size() - 1) {
        std::cout << ",";
      }
    }
    std::cout << std::endl;
  }
}

int main(int argc, char * argv[]) {
  if (argc < 2) {
    return 1;
  }

  Grafo g;
  g.ler(argv[1]);
  hierholzer(g);
  return 0;
}