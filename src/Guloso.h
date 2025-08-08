#ifndef GULOSO_H
#define GULOSO_H

#include <fstream>
#include "Grafo.h"
#include "Aresta.h"

#include <vector>
#include <map>

using namespace std;

class Guloso {
public:
    Guloso();
    ~Guloso();

    ofstream arquivo;
    
    vector<pair<char, char>> algoritmo_guloso(Grafo* grafo);
    vector<pair<char, char>> algoritmo_guloso_randomizado_adaptativo(Grafo* grafo, double alfa) double alfa);
    vector<pair<char, char>> algoritmo_guloso_randomizado_adaptativo_reativo(Grafo* grafo, double alfa) string instancia = "NULL");

private:
    vector<pair<char, char>> arestas_nao_cobertas;

    void obter_arestas_nao_cobertas(Grafo* grafo);
    map<char, int> obter_grau_vertices();
    vector<pair<pair<char, char>, int>> obter_arestas_ordenadas(map<char, int> grau_vertices);
    void remove_arestas_incidentes(pair<char, char> aresta_selecionada);

};

#endif // GULOSO_H