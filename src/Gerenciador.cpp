#include "Gerenciador.h"
#include <fstream>
#include "Guloso.h"

void Gerenciador::comandos(Grafo* grafo) {
    cout<<"Digite uma das opcoes abaixo e pressione enter:"<<endl<<endl;
    cout<<"(a) Fecho transitivo direto de um no;"<<endl;
    cout<<"(b) Fecho transitivo indireto de um no;"<<endl;
    cout<<"(c) Caminho minimo (Djikstra);"<<endl;
    cout<<"(d) Caminho minimo (Floyd);"<<endl;
    cout<<"(e) Arvore Geradora Minima (Algoritmo de Prim);"<<endl;
    cout<<"(f) Arvore Geradora Minima (Algoritmo de Kruskal);"<<endl;
    cout<<"(g) Arvore de caminhamento em profundidade;"<<endl;
    cout<<"(h) Raio, diametro, centro e periferia do grafo;"<< endl;
    cout<<"(i) Vertices de Articulacao" << endl;
    cout<<"(j) Lista de Adjacencia" << endl << endl;

    cout<<"Algoritmos Gulosos para o problema Edge Dominating Set (Conjunto Dominante de Arestas):" << endl;
    cout<<"(k) Algoritmo Guloso" << endl;
    cout<<"(l) Algoritmo Guloso Randomizado Adaptativo" << endl;
    cout<<"(m) Algoritmo Guloso Randomizado Adaptativo Reativo;" << endl << endl;
    
    cout<<"(0) Sair;"<<endl<<endl;

    char resp;
    cin >> resp;
    switch (resp) {
        case 'a': {

            char id_no = get_id_entrada();
            vector<char> fecho_transitivo_direto = grafo->fecho_transitivo_direto(id_no);
           
            cout << "Fecho transitivo direto do no " << id_no << ": ";
            bool primeiro = true;

            for (char id : fecho_transitivo_direto) {
                if (!primeiro) {
                    cout << ", ";
                }
                cout << id;
                primeiro = false;
            }
            cout << endl;

            if(pergunta_imprimir_arquivo("fecho_transitivo_direto.txt")) {
                ofstream arquivo("fecho_transitivo_direto.txt");
                if (!arquivo) {
                    cout << "Erro ao abrir arquivo." << endl;
                } else {
                    bool primeiro = true;  // Inicializa como true para o primeiro elemento
                    for (char id : fecho_transitivo_direto) {
                        if (!primeiro) {
                            arquivo << ", ";
                        }
                        arquivo << id;
                        primeiro = false;
                    }
                    arquivo << endl;
                    arquivo.close();
                    cout << "Fecho salvo em fecho_transitivo_direto.txt" << endl;
                }
            }

            break;
        }

        case 'b':{
            char id_no = get_id_entrada();
            vector<char> fecho_transitivo_indireto = grafo->fecho_transitivo_indireto(id_no);

            
            cout << "Fecho transitivo indireto do no " << id_no << ": ";
            bool primeiro = true;

            for (char id : fecho_transitivo_indireto) {
                if (!primeiro) {
                    cout << ", ";
                }
                cout << id;
                primeiro = false;
            }
            cout << endl;

            if(pergunta_imprimir_arquivo("fecho_transitivo_indireto.txt")) {
                ofstream arquivo("fecho_transitivo_indireto.txt");
                if (!arquivo) {
                    cout << "Erro ao abrir arquivo." << endl;
                } else {
                    bool primeiro = true;  // Inicializa como true para o primeiro elemento
                    for (char id : fecho_transitivo_indireto) {
                        if (!primeiro) {
                            arquivo << ", ";
                        }
                        arquivo << id;
                        primeiro = false;
                    }
                    arquivo << endl;
                    arquivo.close();
                    cout << "Fecho salvo em fecho_transitivo_indireto.txt" << endl;
                }
            }
            break;
        }

        case 'c': {

            char id_no_1 = get_id_entrada();
            char id_no_2 = get_id_entrada();
            vector<char> caminho_minimo_dijkstra = grafo->caminho_minimo_dijkstra(id_no_1,id_no_2);
            bool primeiro = true;

            if(caminho_minimo_dijkstra.empty()) {
                cout << "Nao existe caminho entre os nos informados." << endl;
            } else {
                cout << "Caminho minimo (Dijkstra): ";
                for (char id : caminho_minimo_dijkstra) {
                    if (!primeiro)
                        cout << ", ";
                    cout << id;
                    primeiro = false;
                }
                cout << endl;
            }

            if(pergunta_imprimir_arquivo("caminho_minimo_dijkstra.txt")) {
                ofstream arquivo("caminho_minimo_dijkstra.txt");
                if (!arquivo) {
                    cout << "Erro ao abrir arquivo." << endl;
                } else {
                    for (char id : caminho_minimo_dijkstra) {
                        arquivo << id << " ";
                    }
                    arquivo << endl;
                    arquivo.close();
                    cout << "Caminho salvo em caminho_minimo_dijkstra.txt" << endl;
                }
            }

            break;
        }

        case 'd': {

            char id_no_1 = get_id_entrada();
            char id_no_2 = get_id_entrada();
            vector<char> caminho_minimo_floyd = grafo->caminho_minimo_floyd(id_no_1,id_no_2);
            bool primeiro = true;

            if(caminho_minimo_floyd.empty()) {
                cout << "Nao existe caminho entre os nos informados." << endl;
            } else {
                cout << "Caminho minimo (Floyd): ";
                for (char id : caminho_minimo_floyd) {
                    if (!primeiro)
                        cout << ", ";
                    cout << id;
                    primeiro = false;
                }
                cout << endl;
            }

            if(pergunta_imprimir_arquivo("caminho_minimo_floyd.txt")) {
                ofstream arquivo("caminho_minimo_floyd.txt");
                if (!arquivo) {
                    cout << "Erro ao abrir arquivo." << endl;
                } else {
                    for (char id : caminho_minimo_floyd) {
                        arquivo << id << " ";
                    }
                    arquivo << endl;
                    arquivo.close();
                    cout << "Caminho salvo em caminho_minimo_floyd.txt" << endl;
                }
            }

            break;
        }

        case 'e': {
            // Verifica se o grafo é não direcionado e ponderado nas arestas
            if (grafo->in_direcionado) {
                cout << "Erro: O grafo deve ser nao direcionado para AGM.\n";
                break;
            }
            if (!grafo->in_ponderado_aresta) {
                cout << "Erro: O grafo deve ser ponderado nas arestas para AGM.\n";
                break;
            }
            int tam;
            cout << "Digite o tamanho do subconjunto: ";
            cin >> tam;

            if (tam > 0 && tam <= grafo->ordem) {
                vector<char> ids = get_conjunto_ids(grafo, tam);
                Grafo* agm_prim = grafo->arvore_geradora_minima_prim(ids);

                if (pergunta_imprimir_arquivo("agm_prim.txt")) {
                    ofstream arquivo("agm_prim.txt");
                    for (No* no : agm_prim->lista_adj) {
                        for (Aresta* a : no->arestas) {
                            char u = a->no_origem->id;
                            char v = a->no_destino->id;
                            if (u < v) { // evitar duplicidade
                                arquivo << u << " - " << v << " (peso " << a->peso << ")\n";
                            }
                        }
                    }
                    arquivo.close();
                    cout << "Arquivo agm_prim.txt gerado.\n";
                }

                delete agm_prim;
            } else {
                cout << "Valor invalido\n";
            }
            break;
        }

        case 'f': {
            // Verifica se o grafo é não direcionado e ponderado nas arestas
            if (grafo->in_direcionado) {
                cout << "Erro: O grafo deve ser nao direcionado para AGM.\n";
                break;
            }
            if (!grafo->in_ponderado_aresta) {
                cout << "Erro: O grafo deve ser ponderado nas arestas para AGM.\n";
                break;
            }
            int tam;
            cout << "Digite o tamanho do subconjunto: ";
            cin >> tam;

            if (tam > 0 && tam <= grafo->ordem) {
                vector<char> ids = get_conjunto_ids(grafo, tam);
                Grafo* agm_kruskal = grafo->arvore_geradora_minima_kruskal(ids);

                if (pergunta_imprimir_arquivo("agm_kruskal.txt")) {
                    ofstream arquivo("agm_kruskal.txt");
                    for (No* no : agm_kruskal->lista_adj) {
                        for (Aresta* a : no->arestas) {
                            char u = a->no_origem->id;
                            char v = a->no_destino->id;
                            if (u < v) { // evitar duplicidade
                                arquivo << u << " - " << v << " (peso " << a->peso << ")\n";
                            }
                        }
                    }
                    arquivo.close();
                    cout << "Arquivo agm_kruskal.txt gerado.\n";
                }

                delete agm_kruskal;
            } else {
                cout << "Valor invalido\n";
            }
        
        break;
        }

        case 'g': {

            char id_no = get_id_entrada();
            Grafo* arvore_caminhamento_profundidade = grafo->arvore_caminhamento_profundidade(id_no);
            arvore_caminhamento_profundidade->imprime_ListaAdj();

            if(pergunta_imprimir_arquivo("arvore_caminhamento_profundidade.txt")) {
                ofstream out("arvore_caminhamento_profundidade.txt");
                if (!out) {
                    cout << "Erro ao abrir arquivo." << endl;
                } else {
                    out << "Arvore Caminhamento Profundidade: " << endl;
                    
                    for (No* no : arvore_caminhamento_profundidade->lista_adj) {
                        out << no->id << ": ";
                        for (size_t i = 0; i < no->arestas.size(); ++i) {
                            out << no->arestas[i]->no_destino->get_id();
                            if (i != no->arestas.size() - 1) {
                                out << " -> ";
                            }
                        }
                        out << endl;
                    }

                    out.close();
                    cout << "Salvo em arvore_caminhamento_profundidade.txt." << endl;
                }
            }

            delete arvore_caminhamento_profundidade;
            break;
        }

        case 'h': {
            int raio = grafo->raio();
            int diametro = grafo->diametro();
            vector<char> centro = grafo->centro();
            vector<char> periferia = grafo->periferia();

            cout << "\nRaio: " << raio << endl;
            cout << "Diametro: " << diametro << endl;

            cout << "Centro: ";
            for (char c : centro)
                cout << c << " ";
            cout << endl;

            cout << "Periferia: ";
            for (char p : periferia)
                cout << p << " ";
            cout << endl;

            if (pergunta_imprimir_arquivo("medidas_grafo.txt")) {
                ofstream out("medidas_grafo.txt");
                if (!out) {
                    cout << "Erro ao abrir arquivo." << endl;
                } else {
                    out << "Raio: " << raio << endl;
                    out << "Diametro: " << diametro << endl;

                    out << "Centro: ";
                    for (char c : centro)
                        out << c << " ";
                    out << endl;

                    out << "Periferia: ";
                    for (char p : periferia)
                        out << p << " ";
                    out << endl;

                    out.close();
                    cout << "Medidas salvas em medidas_grafo.txt" << endl;
                }
            }

            break;
        }

        case 'i': {
            vector<char> articulacao = grafo->vertices_de_articulacao();
            cout<<"Metodo de impressao em tela nao implementado"<<endl<<endl;

            if(pergunta_imprimir_arquivo("arvore_caminhamento_profundidade.txt")) {
                cout<<"Metodo de impressao em arquivo nao implementado"<<endl;
            }

            break;
        }

        case 'j': {
            cout << "Lista de Adjacencia:" << endl;
            grafo->imprime_ListaAdj();
            cout << endl;

            break;
        }

        case 'k': {
            cout << "Algoritmo Guloso:" << endl;

            Guloso guloso;
            vector<pair<char, char>> solucao = guloso.algoritmo_guloso(grafo);
            
            
            for (const auto& aresta : solucao) {
                cout << "(" << aresta.first << ", " << aresta.second << ") ";
            }
        

            cout << endl;

            break;
        }

        case 'l': {
            cout << "Algoritmo Randomizado:" << endl;
            grafo->imprime_ListaAdj();
            cout << endl;

            break;
        }

        case 'm': {
            cout << "Algoritmo Randomizado Reativo:" << endl;
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
    int num_arestas = 0;
    char id_1, id_2;
    int peso = 0;
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
        //lendo arestas ate que o arquivo tenha sido lido completamente:
        while (arquivo >> id_1 >> id_2 >> peso) {

            // Encontrar os nós correspondentes
            No* no_1 = nullptr;
            No* no_2 = nullptr;
            for(No* no : grafo->lista_adj) {
                if(no->id == id_1) no_1 = no;
                if(no->id == id_2) no_2 = no;
            }
            
            if(no_1 && no_2) { //Conferindo se os nós existem
                Aresta* aresta = new Aresta(no_1, no_2, peso);
                num_arestas++;
                no_1->arestas.push_back(aresta);
                if(!direcionado) {
                    Aresta* aresta2 = new Aresta(no_2, no_1, peso);
                    no_2->arestas.push_back(aresta2);
                } 
            } else {
                cerr << "Erro: Aresta entre nós inexistentes: " << id_1 << " e " << id_2 << endl;
                return false;
            }
        }
        grafo->set_num_arestas(num_arestas);
    } else {
        while (arquivo >> id_1 >> id_2) {    
            // Encontrar os nós correspondentes
            No* no_1 = nullptr;
            No* no_2 = nullptr;
            for(No* no : grafo->lista_adj) {
                if(no->id == id_1) no_1 = no;
                if(no->id == id_2) no_2 = no;
            }

            if(no_1 && no_2) { //Conferindo se os nós existem
                Aresta* aresta = new Aresta(no_1, no_2);
                num_arestas++;
                no_1->arestas.push_back(aresta);
                if (!direcionado) {
                    Aresta* aresta2 = new Aresta(no_2, no_1);
                    no_2->arestas.push_back(aresta2);
                }
            } else {
                cerr << "Erro: Aresta entre nós inexistentes: " << id_1 << " e " << id_2 << endl;
                return false;
            }
        }
        grafo->set_num_arestas(num_arestas);
    }

    return true;

}

void Gerenciador::imprimirGrafo(Grafo* grafo) {
    
    cout << "Grafo:" << endl;
    cout << "Ordem: " << grafo->get_ordem() << endl;
    cout << "Numero de Arestas: " << grafo->get_num_arestas() << endl;
    cout << "Direcionado: " << (grafo->get_direcionado() ? "Sim" : "Nao") << endl;
    cout << "Ponderado Aresta: " << (grafo->get_ponderado_aresta() ? "Sim" : "Nao") << endl;
    cout << "Ponderado Vertice: " << (grafo->get_ponderado_vertice() ? "Sim" : "Nao") << endl;

    return;
} 