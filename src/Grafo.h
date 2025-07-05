//
// Created by Rafael on 28/05/2025.
//

#ifndef GRAFO_H
#define GRAFO_H

#include "No.h"
#include <iostream>
#include <vector>


using namespace std;
class Grafo {
public:
    Grafo();
    ~Grafo();

    void set_ordem(int ordem) { this->ordem = ordem; }
    int get_ordem() { return this->ordem; }
    void set_direcionado(bool direcionado) { this->in_direcionado = direcionado; }
    bool get_direcionado() { return this->in_direcionado; }
    void set_ponderado_aresta(bool ponderado) { this->in_ponderado_aresta = ponderado; }
    bool get_ponderado_aresta() { return this->in_ponderado_aresta; }
    void set_ponderado_vertice(bool ponderado) { this->in_ponderado_vertice = ponderado; }
    bool get_ponderado_vertice() { return this->in_ponderado_vertice; }

    No* buscarNo(char id_no);
    vector<char> fecho_transitivo_direto(char id_no); // a
    vector<char> fecho_transitivo_indireto(char id_no); // b
    vector<char> caminho_minimo_dijkstra(char id_no_a, char id_no_b); // c
    vector<char> caminho_minimo_floyd(char id_no, char id_no_b); // d
    Grafo* arvore_geradora_minima_prim(vector<char> ids_nos); // e
    Grafo* arvore_geradora_minima_kruskal(vector<char> ids_nos); // f
    Grafo* arvore_caminhamento_profundidade(char id_no); // g
    int raio(); // h 1
    int diametro(); // h 2
    vector<char> centro(); // h 3
    vector<char> periferia(); // h 4
    vector<char> vertices_de_articulacao(); // i
    void imprime_ListaAdj(); 


    int ordem;
    bool in_direcionado;
    bool in_ponderado_aresta;
    bool in_ponderado_vertice;
    vector<No*> lista_adj;
};



#endif //GRAFO_H
