#ifndef NO_H
#define NO_H

#include <string>
#include <vector>
#include "Aresta.h"


using namespace std;
class No {
public:
    No(char id, int peso = 0) : id(id), peso(peso) {};
    ~No();

    char id;
    int peso;
    vector<Aresta*> arestas_incidentes;
    bool visitado;
    int grau = 0;

    vector<No*> get_vizinhos();
    vector<Aresta*> get_arestas() { return arestas_incidentes; }
    char get_id() { return id; }
    void adicionar_aresta(No* destino, int peso);
};



#endif //NO_H
