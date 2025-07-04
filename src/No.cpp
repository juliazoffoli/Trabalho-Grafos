#include "No.h"

vector<No*> No::get_vizinhos() {
    vector<No*> vizinhos;
    for (Aresta* aresta : arestas) {
        No* vizinho = nullptr;
        if (aresta->id_1 == id && aresta->id_2 != '\0') {
            vizinho = new No(aresta->id_2, aresta->peso);
        } else {
            vizinho = new No(aresta->id_1, aresta->peso);
        }
        vizinhos.push_back(vizinho);
    }
    return vizinhos;
}

vector<No*> No::get_anteriores_direcionado() {
    vector<No*> anteriores;

    for (Aresta* aresta : arestas) {
        No* anterior = nullptr;
        if (aresta->id_1 == id && aresta->id_2 == '\0') {
            anterior = new No(aresta->id_1, aresta->peso);
        } 
        anteriores.push_back(anterior);
    }
    return anteriores;
}