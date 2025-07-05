#include "Gerenciador.h"
#include <fstream>


void Gerenciador::comandos(Grafo* grafo) {
    cout<<"Digite uma das opcoes abaixo e pressione enter:"<<endl<<endl;
    cout<<"(a) Fecho transitivo direto de um no;"<<endl;
    cout<<"(b) Fecho transitivo indireto de um no;"<<endl;
    cout<<"(c) Caminho minimo (Djikstra);"<<endl;
    cout<<"(d) Caminho minimo (Floyd);"<<endl;
    cout<<"(e) Arvore Geradora Minima (Algoritmo de Prim);"<<endl;
    cout<<"(f) Arvore Geradora Minima (Algoritmo de Kruskal);"<<endl;
    cout<<"(g) Arvore de caminhamento em profundidade;"<<endl;
    cout<<"(h) Raio, diametro, centro e periferia do grafo;"<<endl;
    cout<<"(i) Lista de Adjacencia" << endl;
    cout<<"(0) Sair;"<<endl<<endl;

    char resp;
    cin >> resp;
    switch (resp) {
        case 'a': {

            char id_no = get_id_entrada();
            vector<char> fecho_transitivo_direto = grafo->fecho_transitivo_direto(id_no);

            cout<<"Fecho transitivo direto do no "<<id_no<<": ";
            for (char id : fecho_transitivo_direto) {
                cout << id << ", ";
            }


            
            cout<<"\nMetodo de impressao em tela nao implementado"<<endl<<endl;

            if(pergunta_imprimir_arquivo("fecho_trans_dir.txt")) {
                cout<<"\nMetodo de impressao em arquivo nao implementado"<<endl<<endl;
            }


            break;
        }

        case 'b':{
            char id_no = get_id_entrada();
            vector<char> fecho_transitivo_indireto = grafo->fecho_transitivo_indireto(id_no);

            cout<<"Fecho transitivo indireto do no "<<id_no<<": ";
            for (char id : fecho_transitivo_indireto) {
                cout << id << ", ";
            }

            cout<<"Metodo de impressao em tela nao implementado"<<endl<<endl;

            if(pergunta_imprimir_arquivo("fecho_trans_indir.txt")) {
                cout<<"Metodo de impressao em arquivo nao implementado"<<endl;
            }
            break;
        }

        case 'c': {

            char id_no_1 = get_id_entrada();
            char id_no_2 = get_id_entrada();
            vector<char> caminho_minimo_dijkstra = grafo->caminho_minimo_dijkstra(id_no_1,id_no_2);
            cout<<"Metodo de impressao em tela nao implementado"<<endl<<endl;

            if(pergunta_imprimir_arquivo("caminho_minimo_dijkstra.txt")) {
                cout<<"Metodo de impressao em arquivo nao implementado"<<endl;
            }


            break;
        }

        case 'd': {

            char id_no_1 = get_id_entrada();
            char id_no_2 = get_id_entrada();
            vector<char> caminho_minimo_floyd = grafo->caminho_minimo_floyd(id_no_1,id_no_2);
            cout<<"Metodo de impressao em tela nao implementado"<<endl<<endl;

            if(pergunta_imprimir_arquivo("caminho_minimo_floyd.txt")) {
                cout<<"Metodo de impressao em arquivo nao implementado"<<endl;
            }


            break;
        }
        case 'e': {

            int tam;
            cout<<"Digite o tamanho do subconjunto: ";
            cin>>tam;

            if(tam > 0 && tam <= grafo->ordem) {

                vector<char> ids = get_conjunto_ids(grafo,tam);
                Grafo* arvore_geradora_minima_prim = grafo->arvore_geradora_minima_prim(ids);
                cout<<"Metodo de impressao em tela nao implementado"<<endl<<endl;

                if(pergunta_imprimir_arquivo("agm_prim.txt")) {
                    cout<<"Metodo de impressao em arquivo nao implementado"<<endl;
                }

                delete arvore_geradora_minima_prim;

            }else {
                cout<<"Valor invalido"<<endl;
            }

            break;
        }

        case 'f': {

            int tam;
            cout<<"Digite o tamanho do subconjunto: ";
            cin>>tam;

            if(tam > 0 && tam <= grafo->ordem) {

                vector<char> ids = get_conjunto_ids(grafo,tam);
                Grafo* arvore_geradora_minima_kruskal = grafo->arvore_geradora_minima_kruskal(ids);
                cout<<"Metodo de impressao em tela nao implementado"<<endl<<endl;

                if(pergunta_imprimir_arquivo("agm_kruskal.txt")) {
                    cout<<"Metodo de impressao em arquivo nao implementado"<<endl;
                }

                delete arvore_geradora_minima_kruskal;

            }else {
                cout<<"Valor invalido"<<endl;
            }

            break;
        }

        case 'g': {

            char id_no = get_id_entrada();
            Grafo* arvore_caminhamento_profundidade = grafo->arvore_caminhamento_profundidade(id_no);
            cout<<"Metodo de impressao em tela nao implementado"<<endl<<endl;

            if(pergunta_imprimir_arquivo("arvore_caminhamento_profundidade.txt")) {
                cout<<"Metodo de impressao em arquivo nao implementado"<<endl;
            }

            delete arvore_caminhamento_profundidade;
            break;
        }

        case 'h': {
            vector<char> articulacao = grafo->vertices_de_articulacao();
            cout<<"Metodo de impressao em tela nao implementado"<<endl<<endl;

            if(pergunta_imprimir_arquivo("arvore_caminhamento_profundidade.txt")) {
                cout<<"Metodo de impressao em arquivo nao implementado"<<endl;
            }

            break;
        }
        case 'i': {
            cout << "Lista de Adjacencia:" << endl;
            grafo->imprime_ListaAdj();
            cout << endl;

            break;
        }

        case '0': {
            exit(0);
        }
        default: {
            cout<<"Opção inválida"<<endl;
        }
    }

    comandos(grafo);

}

char Gerenciador::get_id_entrada() {
    cout<<"Digite o id de um no: ";
    char id;
    cin>>id;
    cout<<endl;
    return id;
}

vector<char> Gerenciador::get_conjunto_ids(Grafo *grafo, int tam) {
    vector<char> ids = {};
    while((int)ids.size() < tam) {
        char id_no =get_id_entrada();
        bool existe = false;
        for(No* no: grafo->lista_adj){
            if(no->id == id_no){
                existe = true;
                break;
            }
        }

        if(!existe){
            cout<<"Vertice nao existe"<<endl;
        }else{
            bool repetido = find(ids.begin(), ids.end(),id_no) != ids.end();
            if(repetido) {
                    cout<<"Valor repetido"<<endl;
            }else {
                ids.push_back(id_no);
            }
        }

    }

    return ids;
}


bool Gerenciador::pergunta_imprimir_arquivo(string nome_arquivo) {

    cout<<"Imprimir em arquivo externo? ("<<nome_arquivo<<")"<<endl;
    cout<<"(1) Sim;"<<endl;
    cout<<"(2) Nao."<<endl;
    int resp;
    cin>>resp;
    cout<<endl;

    switch (resp) {
        case 1:
            return true;
        case 2:
            return false;
        default:
            cout<<"Resposta invalida"<<endl;
            return pergunta_imprimir_arquivo(nome_arquivo);
    }
}

bool Gerenciador::lerArquivoConstruirGrafo(ifstream& arquivo, Grafo* grafo) {
    
    int ordem;
    bool direcionado, ponderado_aresta, ponderado_vertice;

    arquivo >> direcionado >> ponderado_aresta >> ponderado_vertice;
    arquivo >> ordem;

    grafo->set_ordem(ordem);
    grafo->set_direcionado(direcionado);
    grafo->set_ponderado_aresta(ponderado_aresta);
    grafo->set_ponderado_vertice(ponderado_vertice);

    // Ler os vértices
    if(ponderado_vertice) {
        for(int i = 0; i < ordem; i++) {
            char id;
            int peso;
            
            arquivo >> id >> peso;
            
            No* no = new No(id, peso);
            grafo->lista_adj.push_back(no);
        }
    } else {
        for(int i = 0; i < ordem; i++) {
            char id;
            arquivo >> id;
            
            No* no = new No(id);
            grafo->lista_adj.push_back(no);
        }
    }

    // Ler as arestas
    if(ponderado_aresta) {
        for(int i = 0; i < ordem-1; i++) {
            char id_1, id_2;
            int peso;
            
            arquivo >> id_1 >> id_2 >> peso;

            // Encontrar os nós correspondentes
            No* no_1 = nullptr;
            No* no_2 = nullptr;
            for(No* no : grafo->lista_adj) {
                if(no->id == id_1) no_1 = no;
                if(no->id == id_2) no_2 = no;
            }

            if(no_1 && no_2) { //Conferindo se os nós existem
                Aresta* aresta = new Aresta(no_1, no_2, peso);
                no_1->arestas.push_back(aresta);
                if(!direcionado) {
                    no_2->arestas.push_back(aresta); // Se não direcionado, adiciona a aresta também ao nó b
                } 
            } else {
                cerr << "Erro: Aresta entre nós inexistentes: " << id_1 << " e " << id_2 << endl;
                return false;
            }
        }
    } else {
        for(int i = 0; i < ordem-1; i++) {
            char id_1, id_2;
            
            arquivo >> id_1 >> id_2;

            // Encontrar os nós correspondentes
            No* no_1 = nullptr;
            No* no_2 = nullptr;
            for(No* no : grafo->lista_adj) {
                if(no->id == id_1) no_1 = no;
                if(no->id == id_2) no_2 = no;
            }

            if(no_1 && no_2) { //Conferindo se os nós existem
                Aresta* aresta = new Aresta(no_1, no_2);
                no_1->arestas.push_back(aresta);
                if(!direcionado) {
                    no_2->arestas.push_back(aresta); // Se não direcionado, adiciona a aresta também ao nó b
                } 
            } else {
                cerr << "Erro: Aresta entre nós inexistentes: " << id_1 << " e " << id_2 << endl;
                return false;
            }
        }
    }

    return true;

}

void Gerenciador::imprimirGrafo(Grafo* grafo) {
    
    cout << "Grafo:" << endl;
    cout << "Ordem: " << grafo->get_ordem() << endl;
    cout << "Direcionado: " << (grafo->get_direcionado() ? "Sim" : "Não") << endl;
    cout << "Ponderado Aresta: " << (grafo->get_ponderado_aresta() ? "Sim" : "Não") << endl;
    cout << "Ponderado Vertice: " << (grafo->get_ponderado_vertice() ? "Sim" : "Não") << endl;
    return;
} 