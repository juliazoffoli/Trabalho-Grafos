#include "Guloso.h"

#include <algorithm>
#include <map>

using namespace std;

Guloso::Guloso() {
}

Guloso::~Guloso() {
}

vector<pair<char, char>> Guloso::algoritmo_guloso(Grafo* grafo) {
    vector<pair<char, char>> solucao;

    vector<pair<char, char>> arestas_nao_cobertas = obter_arestas_nao_cobertas(grafo);

    while (!arestas_nao_cobertas.empty()) {

        // Calcula o numero de arestas incidentes a u e v que ainda nao foram cobertas
        map<char, int> grau_arestas;
        for (pair<char, char> aresta : arestas_nao_cobertas) {
            grau_arestas[aresta.first]++;
            grau_arestas[aresta.second]++;
        }

        // Encontra o par de arestas com o maior grau
        pair<char, char> aresta_max;
        int max_grau = -1;
        for (pair<char, char> aresta : arestas_nao_cobertas) {
            int grau = grau_arestas[aresta.first] + grau_arestas[aresta.second];
            if (grau > max_grau) {
                max_grau = grau;
                aresta_max = aresta;
            }
        }

        solucao.push_back(aresta_max);

        // Remove as arestas incidentes aos vértices da aresta selecionada
        char u = aresta_max.first;
        char v = aresta_max.second;
        
        for (int i = arestas_nao_cobertas.size() - 1; i >= 0; i--) {
            if (arestas_nao_cobertas[i].first == u || arestas_nao_cobertas[i].first == v ||
                arestas_nao_cobertas[i].second == u || arestas_nao_cobertas[i].second == v) {
                arestas_nao_cobertas.erase(arestas_nao_cobertas.begin() + i);
            }
        }
    }

    return solucao;
}

vector<pair<char, char>> Guloso::obter_arestas_nao_cobertas(Grafo* grafo) {
    vector<pair<char, char>> arestas_nao_cobertas;
    
    for (No* no : grafo->lista_adj) {
        for (Aresta* aresta : no->get_arestas()) {
            char id_origem = aresta->no_origem->get_id();
            char id_destino = aresta->no_destino->get_id();
            if (find(arestas_nao_cobertas.begin(), arestas_nao_cobertas.end(), make_pair(id_origem, id_destino)) == arestas_nao_cobertas.end() &&
                find(arestas_nao_cobertas.begin(), arestas_nao_cobertas.end(), make_pair(id_destino, id_origem)) == arestas_nao_cobertas.end()) {
                arestas_nao_cobertas.push_back(make_pair(id_origem, id_destino));
            }
        }
    }

    return arestas_nao_cobertas;
}