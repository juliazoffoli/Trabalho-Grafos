#ifndef GULOSO_H
#define GULOSO_H

#include "Grafo.h"
#include "Aresta.h"

using namespace std;

class Guloso {
public:
    Guloso();
    ~Guloso();

    vector<pair<char, char>> algoritmo_guloso(Grafo* grafo);
    vector<pair<char, char>> algoritmo_guloso_randomizado_adaptativo(Grafo* grafo);
    vector<pair<char, char>> algoritmo_guloso_randomizado_adaptativo_reativo(Grafo* grafo);
private:
    vector<pair<char, char>> obter_arestas_nao_cobertas(Grafo* grafo);

};

#endif // GULOSO_H