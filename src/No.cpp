#include "No.h"
#include "Aresta.h"
#include <iostream>


void No::adicionar_aresta(No* destino, int peso) {
    Aresta* a = new Aresta(this, destino, peso);
    this->arestas.push_back(a);
}


vector<No*> No::get_vizinhos() {
    vector<No*> vizinhos;
    for (Aresta* aresta : arestas) {
        No* vizinho = nullptr;
        vizinho = aresta->no_destino; 
        vizinhos.push_back(vizinho);
    }

    return vizinhos;
}
/*
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
*/