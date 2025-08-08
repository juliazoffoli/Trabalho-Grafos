#include "Guloso.h"
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;

Guloso::Guloso() {   
}

Guloso::~Guloso() {
}

vector<pair<char, char>> Guloso::algoritmo_guloso(Grafo* grafo) {
    this->arquivo = ofstream ("[DEBUG]guloso.txt");
    this->arquivo << grafo->instancia << endl << endl;

    vector<pair<char, char>> solucao;
    obter_arestas_nao_cobertas(grafo);

    int exec = 0;
    while (!arestas_nao_cobertas.empty()) {

        // DEBUG
        exec++;
        this->arquivo << "\n[DEBUG] Execução " << exec << ":\n";
        this->arquivo << "[DEBUG] Arestas não cobertas: " << endl;
        for (pair<char, char> aresta : arestas_nao_cobertas)
            this->arquivo << "(" << aresta.first << ", " << aresta.second << ") ";
        this->arquivo << endl;

        // Calcula o grau dos vértices das arestas não cobertas
        map<char, int> grau_vertices = obter_grau_vertices();

        // Calcula o grau das arestas (soma dos graus dos vértices da aresta) e ordena
        vector<pair<pair<char, char>, int>> arestas_com_grau = obter_arestas_ordenadas(grau_vertices);
        
        // Obtem a aresta com maior grau
        pair<char, char> aresta_maior_grau = arestas_com_grau.begin()->first;
        int max_grau = arestas_com_grau.begin()->second;
        this->arquivo << "[DEBUG] Aresta selecionada: (" << aresta_maior_grau.first << ", " << aresta_maior_grau.second << ") com grau " << max_grau << endl;

        solucao.push_back(aresta_maior_grau);
        this->arquivo << "[DEBUG] Solução: ";
        for (pair<char, char> aresta: solucao)
            this->arquivo << " (" << aresta.first << ", " << aresta.second << ") ";
        this->arquivo << endl;

        // Remove as arestas_incidentes incidentes aos vértices da aresta selecionada
        remove_arestas_incidentes(aresta_maior_grau);
    }
 
    this->arquivo << "[DEBUG] Solução final: ";
    for (pair<char, char> aresta : solucao)
        this->arquivo << "(" << aresta.first << ", " << aresta.second << ") ";
    this->arquivo << endl;

    return solucao;
}

void Guloso::obter_arestas_nao_cobertas(Grafo* grafo) {
    this->arestas_nao_cobertas = vector<pair<char, char>>();
    
    for (No* no : grafo->lista_nos) {
        for (Aresta* aresta : no->get_arestas()) {
            char id_origem = aresta->no_origem->get_id();
            char id_destino = aresta->no_destino->get_id();

            if (find(this->arestas_nao_cobertas.begin(), this->arestas_nao_cobertas.end(), make_pair(id_origem, id_destino)) == this->arestas_nao_cobertas.end() &&
                find(this->arestas_nao_cobertas.begin(), this->arestas_nao_cobertas.end(), make_pair(id_destino, id_origem)) == this->arestas_nao_cobertas.end()) {
               
                this->arestas_nao_cobertas.push_back(make_pair(id_origem, id_destino));
            }
        }
    }

    // DEBUG
    this->arquivo << "[DEBUG] Arestas não cobertas (antes de iniciar a execução): " << endl;
    for (pair<char, char> aresta : arestas_nao_cobertas)
        this->arquivo << "(" << aresta.first << ", " << aresta.second << ") ";
    this->arquivo << endl;
}

map<char, int> Guloso::obter_grau_vertices() {
    
    this->arquivo << "\n[DEBUG] Cálculo o grau dos vertices das arestas não cobertas: \n";
    
    // Calcula o grau dos vértices u e v que ainda nao foram cobertos
    map<char, int> grau_vertices;
    for (pair<char, char> aresta : this->arestas_nao_cobertas) {
        grau_vertices[aresta.first]++;
        grau_vertices[aresta.second]++;

        // DEBUG
        this->arquivo << "[DEBUG] Aresta: (" << aresta.first << ", " << aresta.second << ")\n";
        this->arquivo << "[DEBUG] Nó: " << aresta.first << ", Grau: " << grau_vertices[aresta.first] << endl;
        this->arquivo << "[DEBUG] Nó: " << aresta.second << ", Grau: " << grau_vertices[aresta.second] << endl;
    }

    this->arquivo << "\n[DEBUG] Grau dos vertices das arestas não cobertas: \n";
    for (pair<char, int> grau : grau_vertices)
        this->arquivo << "[DEBUG] Nó: " << grau.first << ", Grau: " << grau.second << endl;
    
    return grau_vertices;
}

vector<pair<pair<char, char>, int>> Guloso::obter_arestas_ordenadas(map<char, int> grau_vertices) {
    this->arquivo << "\n[DEBUG] Selecionando a aresta com maior grau...\n";

    // Calcula o grau das arestas (soma dos graus dos vértices da aresta)
    vector<pair<pair<char, char>, int>> arestas_com_grau;

    for (pair<char, char> aresta : this->arestas_nao_cobertas) {
        int grau = grau_vertices[aresta.first] + grau_vertices[aresta.second];
        arestas_com_grau.push_back(make_pair(aresta, grau));
        this->arquivo << "[DEBUG] Aresta: (" << aresta.first << ", " << aresta.second << "), Grau: " << grau << endl;
    }

    sort(arestas_com_grau.begin(), arestas_com_grau.end(),
         [](pair<pair<char, char>, int>& a, pair<pair<char, char>, int>& b) {
             return a.second > b.second; // Ordena em ordem decrescente pelo grau
         });
    
    return arestas_com_grau;
}

void Guloso::remove_arestas_incidentes(pair<char, char> aresta_selecionada) {
    char u = aresta_selecionada.first;
    char v = aresta_selecionada.second;

    this->arquivo << "\n[DEBUG] Removendo arestas incidentes aos vértices da aresta selecionada: (" << u << ", " << v << ")\n";
    for (int i = this->arestas_nao_cobertas.size()-1; i >= 0; i--) {
        pair<char, char> aresta = this->arestas_nao_cobertas[i];

        this->arquivo << "\n[DEBUG] Verificando aresta: (" << aresta.first << ", " << aresta.second << ")\n";
        if (aresta.first == u || aresta.second == u || aresta.first == v || aresta.second == v) {
            this->arquivo << "[DEBUG] Removendo aresta: (" << aresta.first << ", " << aresta.second << ")\n";
            this->arestas_nao_cobertas.erase(this->arestas_nao_cobertas.begin() + i);
        }
    }

    this->arquivo << "\n[DEBUG] Arestas não cobertas após remoção: " << endl;
    for (pair<char, char> aresta : this->arestas_nao_cobertas)
        this->arquivo << "(" << aresta.first << ", " << aresta.second << ") ";
    this->arquivo << endl;
}