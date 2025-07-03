#include "No.h"

vector<No*> No::get_vizinhos() {
    vector<No*> vizinhos;
    for (Aresta* aresta : arestas) {
        No* vizinho = nullptr;
        if (aresta->id_1 == id) {
            vizinho = new No(aresta->id_2, aresta->peso);
        } else {
            vizinho = new No(aresta->id_1, aresta->peso);
        }
        vizinhos.push_back(vizinho);
    }
    return vizinhos;
}