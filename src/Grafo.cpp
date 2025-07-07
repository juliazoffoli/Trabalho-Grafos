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
    int INF = numeric_limits<int>::max();
    vector<char> vertices;

    // Passo 1: Mapeamento dos IDs para índices
    unordered_map<char, int> id_to_idx;
    unordered_map<int, char> idx_to_id;

    int n = lista_adj.size();
    for (int i = 0; i < n; ++i) {
        char id = lista_adj[i]->get_id();
        id_to_idx[id] = i;
        idx_to_id[i] = id;
        vertices.push_back(id);
    }

    // Passo 2: Inicialização da matriz de distâncias e predecessores
    vector<vector<int>> dist(n, vector<int>(n, INF));
    vector<vector<int>> pred(n, vector<int>(n, -1));

    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
        No* no = lista_adj[i];

        for (Aresta* aresta : no->get_arestas()) {
            int j = id_to_idx[aresta->no_destino->get_id()];
            int peso = in_ponderado_aresta ? aresta->peso : 1;
            dist[i][j] = peso;
            pred[i][j] = i;
        }
    }

    // Passo 3: Algoritmo de Floyd-Warshall
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        pred[i][j] = pred[k][j];
                    }
                }
            }
        }
    }

    // Passo 4: Reconstrução do caminho de id_no até id_no_b
    int origem = id_to_idx[id_no];
    int destino = id_to_idx[id_no_b];

    if (dist[origem][destino] == INF) return {}; // Sem caminho

    vector<char> caminho;
    int atual = destino;

    while (atual != origem) {
        caminho.push_back(idx_to_id[atual]);
        atual = pred[origem][atual];
        if (atual == -1) return {}; // Caminho quebrado
    }

    caminho.push_back(id_no);
    reverse(caminho.begin(), caminho.end());
    return caminho;
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

vector<int> Grafo::calcular_excentricidades() {
    int n = lista_adj.size();
    vector<int> excentricidade(n, 0);

    for (int i = 0; i < n; ++i) {
        char origem_id = lista_adj[i]->get_id();
        int max_dist = 0;

        for (int j = 0; j < n; ++j) {
            if (i == j) continue;

            char destino_id = lista_adj[j]->get_id();
            vector<char> caminho = caminho_minimo_floyd(origem_id, destino_id);

            if (caminho.empty())
                continue; // sem caminho → ignora ou trata como infinito

            int dist = caminho.size() - 1;
            max_dist = max(max_dist, dist);
        }

        excentricidade[i] = max_dist;
    }

    return excentricidade;
}


int Grafo::raio() {
    vector<int> exc = calcular_excentricidades();
    return *min_element(exc.begin(), exc.end());
}

int Grafo::diametro() {
    vector<int> exc = calcular_excentricidades();
    return *max_element(exc.begin(), exc.end());
}

vector<char> Grafo::centro() {
     vector<int> exc = calcular_excentricidades();
    int r = *min_element(exc.begin(), exc.end());

    vector<char> centro;
    for (size_t i = 0; i < exc.size(); ++i)
        if (exc[i] == r)
            centro.push_back(lista_adj[i]->get_id());

    return centro;
}

vector<char> Grafo::periferia() {
    vector<int> exc = calcular_excentricidades();
    int d = *max_element(exc.begin(), exc.end());

    vector<char> periferia;
    for (size_t i = 0; i < exc.size(); ++i)
        if (exc[i] == d)
            periferia.push_back(lista_adj[i]->get_id());

    return periferia;
}

vector<char> Grafo::vertices_de_articulacao() {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}
