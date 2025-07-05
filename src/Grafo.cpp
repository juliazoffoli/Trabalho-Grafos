#include "Grafo.h"
#include <stack>
#include <queue>
#include <iostream>

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
    for (No* no : this->lista_adj) {
        cout << "No " << no->id << ": ";
        vector<No*> vizinhos = no->get_vizinhos();
        for (No* vizinho : vizinhos) {
            cout << vizinho->id << " ";
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

vector<char> Grafo::fecho_transitivo_indireto(char id_no) {
    vector<char> ids;
    vector<No*> nos_visitados;
    
    return ids;
}

/*
vector<char> Grafo::fecho_transitivo_indireto(char id_no) {
    vector<char> ids;
    vector<No*> nos_visitados;

    for (No* no : this->lista_adj) {
        for (Aresta* aresta : no->arestas) {
            if (aresta->id_no_alvo == id_no){
                // Adicionar o nó de origem da aresta ao vetor de ids
                bool ja_adicionado = false;
                for (No* visitado : nos_visitados) {
                    if (visitado->id == no->id || visitado->id == id_no) {
                        ja_adicionado = true;
                        break;
                    }
                }
                if(!ja_adicionado) {
                    ids.push_back(no->id);
                    nos_visitados.push_back(no);
                }
            }
        }
    }

    for (char id : ids) {
        for (No* no : this->lista_adj) {
            for (Aresta* aresta : no->arestas) {
                if (aresta->id_no_alvo == id_no){
                    // Adicionar o nó de origem da aresta ao vetor de ids
                    bool ja_adicionado = false;
                    for (No* visitado : nos_visitados) {
                        if (visitado->id || visitado->id == id_no) {
                            ja_adicionado = true;
                            break;
                        }
                    }
                    if(!ja_adicionado) {
                        ids.push_back(no->id);
                        nos_visitados.push_back(no);
                    }
                }
            }
        }
    }

    cout << "Fecho transitivo indireto: " << endl;;
    for (char id : ids) {
            cout << id << ", ";
    }

    return {};
}
*/

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
