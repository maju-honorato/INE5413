#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

class Grafo {
  private:
    int numVertices;
    int numArestas;
    std::vector<std::vector<int>> adj;
    std::vector<std::string> rotulos;

  public:
    Grafo() {
      numVertices = 0;
      numArestas = 0;
    }

    int qtdVertices() {
      return numVertices;
    }

    int qtdArestas() {
      return numArestas;
    }

    int grau(int v) {
      if (v > 0 && v <= numVertices) {
        return adj[v].size();
      } else {
        return 0;
      }
    }

    std::string rotulo(int v) {
      if (v > 0 && v <= numVertices) {
        return rotulos[v];
      } else {
        return "vertice invalido";
      }
    }

    std::vector<int> vizinhos(int v) {
      std::vector<int> listaVizinhos;
      if (v > 0 && v <= numVertices) {
        return adj[v];
      }
      return std::vector<int>();
    }

    bool haAresta(int u, int v) {
      if (u > 0 && u <= numVertices) {
        for (int i = 0; i < adj[u].size(); i++) {
          if (adj[u][i] == v) {
            return true;
          }
        }
      }
      return false;
    }

    void ler(std::string fileName);

    Grafo transposta() {
        Grafo GT;
        GT.numVertices = this->numVertices;
        GT.numArestas = this->numArestas;
        GT.rotulos = this->rotulos;
        GT.adj.assign(this->numVertices + 1, std::vector<int>());

        for (int u = 1; u <= this->numVertices; u++) {
            for (size_t i = 0; i < this->adj[u].size(); i++) {
                int v = this->adj[u][i];
                GT.adj[v].push_back(u);
            }
        }
        return GT;
    }
};

void Grafo::ler(std::string fileName) {
  std::ifstream file(fileName);
  if (!file.is_open()) return;

  std::string texto((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  size_t pos = 0;

  auto pulaEspaco = [&]() {
    while (pos < texto.size() && (texto[pos] == ' ' || texto[pos] == '\n' || texto[pos] == '\r' || texto[pos] == '\t')) {
      pos++;
    }
  };

  auto proximaPalavra = [&]() {
    pulaEspaco();
    std::string palavra = "";
    while (pos < texto.length() && texto[pos] != ' ' && texto[pos] != '\n' && texto[pos] != '\r' && texto[pos] != '\t') {
      palavra += texto[pos];
      pos++;
    }
    return palavra;
  };

  while (pos < texto.length()) {
    std::string p = proximaPalavra();
    if (p == "*vertices") break;
  }

  this->numVertices = std::stoi(proximaPalavra());
  this->adj.assign(numVertices + 1, std::vector<int>());
  this->rotulos.assign(numVertices + 1, "");

  for (int i = 0; i < this->numVertices; i++) {
    int id = std::stoi(proximaPalavra());

    pulaEspaco();
    std::string nome = "";

    if (texto[pos] == '\"') {
      pos++;
      while (pos < texto.length() && texto[pos] != '\"') {
        nome += texto[pos];
        pos++;
      }
      pos++;
    } else {
        while (pos < texto.length() && texto[pos] != ' ' && texto[pos] != '\n' && texto[pos] != '\r') {
          nome += texto[pos];
          pos++;
        }
    }
    this->rotulos[id] = nome;
  }

  while (pos < texto.length()) {
    std::string p = proximaPalavra();
    if (p == "*arcs") break;
  }

  while (pos < texto.length()) {
    pulaEspaco();
    if (pos >= texto.length()) {
      break;
    }

    std::string pu = proximaPalavra();
    if (pu.empty()) {
        break;
    }

    std::string pv = proximaPalavra();
    if (pv.empty()) {
        break;
    }
    
    proximaPalavra();

    int u = std::stoi(pu);
    int v = std::stoi(pv);

    this->adj[u].push_back(v);
    this->numArestas++;
  }

  file.close();
}