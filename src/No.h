#ifndef NO_H
#define NO_H

#include <string>
#include <vector>
#include "Aresta.h"


using namespace std;
class No {
public:
    No(char id, int peso = 0) : id(id), peso(peso), visitado(0) {};
    ~No();

    char id;
    int peso;
    vector<Aresta*> arestas;

    bool visitado;
    void adicionar_aresta(No* destino, int peso);
    vector<No*> get_vizinhos();
    vector<No*> get_anteriores_direcionado();
    vector<Aresta*> get_arestas() { return arestas; }
    char get_id() { return id; }
};



#endif //NO_H
