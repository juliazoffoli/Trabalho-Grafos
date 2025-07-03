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
    vector<Aresta*> arestas;

    vector<No*> get_vizinhos();
};



#endif //NO_H
