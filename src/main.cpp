#include <iostream>
#include <fstream>
#include "Gerenciador.h"
#include "Grafo.h"

using namespace std;

int main(int argc, char *argv[]) {
    Grafo* grafo = new Grafo();
    
    string nomeArquivo;

    if(argc > 1) {                      // arg[0] é o nome do programa. se tiver um segundo arg, é o nome do arquivo
        nomeArquivo = argv[1];
    } 
    else {
        // Se não foi passado, pede ao usuário
        cout << "Digite o nome do arquivo de entrada: ";
        cin >> nomeArquivo;
    }

    // Tenta abrir o arquivo
    ifstream arquivo(nomeArquivo);
    if(!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo " << nomeArquivo << endl;
        return 1;
    }

    if(!Gerenciador::lerArquivoConstruirGrafo(arquivo, grafo)) {
        cerr << "Erro ao processar o arquivo" << endl;
        return 1;
    }

    Gerenciador::imprimirGrafo(grafo);
    arquivo.close();

    Gerenciador::comandos(grafo);

    delete grafo;

    return 0;
}