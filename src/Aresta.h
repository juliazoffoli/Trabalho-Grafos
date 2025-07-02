#ifndef ARESTA_H
#define ARESTA_H

using namespace std;
class Aresta {
public:
    Aresta(int peso = 0) : peso(peso) {};
    ~Aresta();

    char id_no_alvo = '\0'; // Se direcionada, o id do nó alvo
    int peso;

    char id_1 = '\0';
    char id_2 = '\0';
};



#endif //ARESTA_H
