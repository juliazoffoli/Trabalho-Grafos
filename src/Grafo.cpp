#include "Grafo.h"
#include <stack>
#include <queue>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include <algorithm>

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
    // π(j): mapa de distâncias mínimas
    unordered_map<char, int> pi;
    unordered_map<char, char> anterior;

    vector<char> S_barra; // Conjunto S̅
    vector<char> todos_ids;

    // Inicializa distâncias e S̅
    for (No* no : lista_adj) {
        char id = no->get_id();
        todos_ids.push_back(id);
        if (id != id_no_a) {
            pi[id] = numeric_limits<int>::max(); // ∞
            S_barra.push_back(id);
        } else {
            pi[id] = 0;
        }
    }

    // Inicializa π(j) com c_1j se j ∈ Γ⁺(1), ∞ caso contrário
    No* origem = buscarNo(id_no_a);
    if (!origem) return {};

    for (Aresta* aresta : origem->get_arestas()) {
        char vizinho = aresta->no_destino->get_id();
        int custo = in_ponderado_aresta ? aresta->peso : 1;
        pi[vizinho] = custo;
        anterior[vizinho] = id_no_a;
    }

    // Enquanto S̅ ≠ ∅ faça
    while (!S_barra.empty()) {
        // Selecionar j ∈ S̅ tal que π(j) é mínimo
        char j_min = 0;
        int menor_pi = numeric_limits<int>::max();
        for (char j : S_barra) {
            if (pi[j] < menor_pi) {
                menor_pi = pi[j];
                j_min = j;
            }
        }

        if (j_min == 0) break; // Todos são ∞, acabou

        // S̅ ← S̅ − {j}
        S_barra.erase(remove(S_barra.begin(), S_barra.end(), j_min), S_barra.end());

        No* no_j = buscarNo(j_min);
        if (!no_j) continue;

        // Para ∀k ∈ S̅ e k ∈ Γ⁺(j) faça
        for (Aresta* aresta : no_j->get_arestas()) {
            char k = aresta->no_destino->get_id();
            if (find(S_barra.begin(), S_barra.end(), k) == S_barra.end())
                continue; // k não está mais em S̅

            int custo_jk = in_ponderado_aresta ? aresta->peso : 1;

            // π(k) ← min(π(k), π(j) + c_jk)
            int novo_valor = pi[j_min] + custo_jk;
            if (novo_valor < pi[k]) {
                pi[k] = novo_valor;
                anterior[k] = j_min;
            }
        }
    }

    // Reconstrução do caminho
    vector<char> caminho;
    if (pi[id_no_b] == numeric_limits<int>::max())
        return caminho; // Sem caminho

    for (char at = id_no_b; at != id_no_a; at = anterior[at]) {
        caminho.push_back(at);
    }
    caminho.push_back(id_no_a);
    reverse(caminho.begin(), caminho.end());

    return caminho;
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
