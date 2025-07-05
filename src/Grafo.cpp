#include "Grafo.h"
#include <stack>
#include <queue>
#include <iostream>
#include <unordered_set>

Grafo::Grafo() {
    this->ordem = 0;
    this->in_direcionado = false;
    this->in_ponderado_aresta = false;
    this->in_ponderado_vertice = false;

    this->lista_adj = vector<No*>();
}

Grafo::~Grafo() {

}


void Grafo::imprime_ListaAdj() {
    for (No* no : lista_adj) {
        cout << no->id << ": ";
        
        // Imprime todas as arestas exceto a última com " -> "
        for (size_t i = 0; i < no->arestas.size(); ++i) {
            cout << no->arestas[i]->no_destino->get_id();
            if (i != no->arestas.size() - 1) { // Se não for o último elemento
                cout << " -> ";
            }
        }
        
        cout << endl;
    }
}

No* Grafo::buscarNo(char id_no) {
    for (No* no : this->lista_adj) {
        if (no->id == id_no) {
            return no;
        }
    }
    return nullptr; // Retorna nullptr se o nó não for encontrado
}

/*
// O método abaixo também funciona, mas é menos eficiente que o novo método (não comentado)

vector<char> Grafo::fecho_transitivo_direto(char id_no) {
    vector<char> ids;
    vector<No*> nos_visitados;

    for (No* no : this->lista_adj) {
        if (no->id == id_no) {
            for (No* vizinho : no->get_vizinhos()) {
                ids.push_back(vizinho->id);
                nos_visitados.push_back(vizinho);
            }
        }
    }

    for (char id : ids) {
        for (No* no : this->lista_adj) {
            if (no->id == id) {
                for (No* vizinho : no->get_vizinhos()) {
                    // Adicionar vizinho apenas se ele não estiver em nos_visitados:
                    bool ja_adicionado = false;
                    for (No* visitado : nos_visitados) {
                        if (visitado->id == vizinho->id) {
                            ja_adicionado = true;
                            break;
                        }
                    }
                    if(!ja_adicionado && vizinho->id != id_no) {
                        ids.push_back(vizinho->id);
                        nos_visitados.push_back(vizinho);
                    }
                }
            }
        }
    }
    
    return ids;
}
*/

vector<char> Grafo::fecho_transitivo_direto(char id_no) {
    vector<char> ids;
    unordered_set<char> visitados;
    queue<char> fila;

    // Encontra o nó inicial
    for (No* no : lista_adj) {
        if (no->id == id_no) {
            // Adiciona vizinhos diretos
            for (No* vizinho : no->get_vizinhos()) {
                if (visitados.insert(vizinho->id).second) { // Se não foi visitado
                    fila.push(vizinho->id);
                    ids.push_back(vizinho->id);
                }
            }
            break;
        }
    }

    // Busca em largura (BFS) para sucessores transitivos
    while (!fila.empty()) {
        char atual = fila.front();
        fila.pop();

        for (No* no : lista_adj) {
            if (no->id == atual) {
                for (No* vizinho : no->get_vizinhos()) {
                    if (visitados.insert(vizinho->id).second) { // Se não foi visitado
                        fila.push(vizinho->id);
                        ids.push_back(vizinho->id);
                    }
                }
                break;
            }
        }
    }

    return ids;
}

vector<char> Grafo::fecho_transitivo_indireto(char id_no) {
    vector<char> ids;
    unordered_set<char> visitados; // Mais eficiente que vector
    queue<char> fila;
    
    // Primeiro encontra todos os predecessores diretos
    for (No* no : lista_adj) {
        for (Aresta* aresta : no->arestas) {
            if (aresta->no_destino->get_id() == id_no) {
                char id_origem = aresta->no_origem->get_id();
                if (visitados.insert(id_origem).second) { // Se não estava visitado
                    fila.push(id_origem);
                    ids.push_back(id_origem);
                }
            }
        }
    }
    
    // Agora busca predecessores dos predecessores (transitivo)
    while (!fila.empty()) {
        char atual = fila.front();
        fila.pop();
        
        for (No* no : lista_adj) {
            for (Aresta* aresta : no->arestas) {
                if (aresta->no_destino->get_id() == atual) {
                    char id_origem = aresta->no_origem->get_id();
                    if (visitados.insert(id_origem).second) { // Se não estava visitado
                        fila.push(id_origem);
                        ids.push_back(id_origem);
                    }
                }
            }
        }
    }
    
    return ids;
}

vector<char> Grafo::caminho_minimo_dijkstra(char id_no_a, char id_no_b) {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

vector<char> Grafo::caminho_minimo_floyd(char id_no, char id_no_b) {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

Grafo * Grafo::arvore_geradora_minima_prim(vector<char> ids_nos) {
    cout<<"Metodo nao implementado"<<endl;
    return nullptr;
}

Grafo * Grafo::arvore_geradora_minima_kruskal(vector<char> ids_nos) {
    cout<<"Metodo nao implementado"<<endl;
    return nullptr;
}

Grafo * Grafo::arvore_caminhamento_profundidade(char id_no) {
    cout<<"Metodo nao implementado"<<endl;
    return nullptr;
}

int Grafo::raio() {
    cout<<"Metodo nao implementado"<<endl;
    return 0;
}

int Grafo::diametro() {
    cout<<"Metodo nao implementado"<<endl;
    return 0;
}

vector<char> Grafo::centro() {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

vector<char> Grafo::periferia() {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

vector<char> Grafo::vertices_de_articulacao() {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}
