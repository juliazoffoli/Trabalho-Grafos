#include "Grafo.h"


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

vector<char> Grafo::fecho_transitivo_direto(char id_no) {
    cout<<"Não sei se a implementação ta certa!!!"<<endl;
    cout <<"Arrumar pra não adicionar ids repetidos "<<endl;

    vector<char> ids;
    for (No* no : this->lista_adj) {
        if (no->id == id_no) {
            vector<No*> vizinhos = no->get_vizinhos();
            for (No* vizinho : vizinhos) {
                ids.push_back(vizinho->id);
            }
            break;
        }
    }
    for (char id : ids) {
        for (No* no : this->lista_adj) {
            if (no->id == id) {
                vector<No*> vizinhos = no->get_vizinhos();
                for (No* vizinho : vizinhos) 
                    ids.push_back(vizinho->id);
            }
        }
    }

    for (char id : ids) {
        cout << id << " ";
    }

    return {};
}

vector<char> Grafo::fecho_transitivo_indireto(char id_no) {
    cout<<"Metodo nao implementado"<<endl;
    return {};
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
