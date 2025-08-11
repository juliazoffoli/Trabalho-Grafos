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
    vector<pair<char, char>> algoritmo_guloso_randomizado_adaptativo(Grafo* grafo, double alfa);
    vector<pair<char, char>> algoritmo_guloso_randomizado_adaptativo_reativo(Grafo* grafo, vector<double> alfas, int num_inter, int bloco);
    void executar_multiplas_vezes_guloso(Grafo* grafo, int k);
    void executar_multiplas_vezes_guloso_randomizado(Grafo* grafo, double alfa, int k);
    void executar_multiplas_vezes_guloso_reativo(Grafo* grafo, vector<double> alfas, int num_iter, int bloco, int k);
    void calcular_e_imprimir_estatisticas(const vector<int>& tamanhos, int solucoes_validas, int total_execucoes, const string& nome_algoritmo);

private:
    vector<pair<char, char>> arestas_nao_cobertas;

    void obter_arestas_nao_cobertas(Grafo* grafo);
    map<char, int> obter_grau_vertices();
    vector<pair<pair<char, char>, int>> obter_arestas_ordenadas(map<char, int> grau_vertices);
    void remove_arestas_incidentes(pair<char, char> aresta_selecionada);
    bool verificar_conectividade(Grafo* grafo, const std::vector<std::pair<char, char>>& solucao);
    

};

#endif // GULOSO_H