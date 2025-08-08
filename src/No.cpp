#include "No.h"
#include <iostream>

vector<No*> No::get_vizinhos() {
    vector<No*> vizinhos;
    for (Aresta* aresta : arestas_incidentes) {
        No* vizinho = nullptr;
        vizinho = aresta->no_destino; 
        vizinhos.push_back(vizinho);
    }

    return vizinhos;
}

void No::adicionar_aresta(No* destino, int peso) {
    Aresta* a = new Aresta(this, destino, peso);
    this->arestas_incidentes.push_back(a);
}
