#include "Grafo.h"
#include <stack>
#include <queue>
#include <iostream>
#include <unordered_set>

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
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

vector<char> Grafo::caminho_minimo_floyd(char id_no, char id_no_b) {
    cout<<"Metodo nao implementado"<<endl;
    return {};
}

Grafo * Grafo::arvore_geradora_minima_prim(vector<char> ids_nos) {
    // cria um novo grafo para a arvore geradora mínima 
    Grafo* agm = new Grafo();
    agm->in_direcionado = false;
    agm->in_ponderado_aresta = true;
    int n = ids_nos.size();

    vector<No*> novos_nos;
    vector<Aresta*> arestas_agm; // vetor para armazenar a ordem de inserção 

    for (char id : ids_nos) {
        No* novo = new No(id);
        novos_nos.push_back(novo);
        agm->lista_adj.push_back(novo);
    }

    vector<char> prox(n, '\0'); // vetor para armazenar o próximo nó a ser adicionado à árvore geradora mínima

    // encontra aresta de menor peso (u,v)
    int menor = 999999;
    char u = '\0';
    char v = '\0';
    for (No* no : lista_adj) {
        for (Aresta* a : no->arestas) {
            char id1 = a->no_origem->id;
            char id2 = a->no_destino->id;

            bool no_conjunto1 = false, no_conjunto2 = false;
            for (char id : ids_nos) { // verifica se os nós id1 e id2 estão no conjunto de nós fornecido
                if (id == id1) no_conjunto1 = true;
                if (id == id2) no_conjunto2 = true;
            }

            if (no_conjunto1 && no_conjunto2 && a->peso < menor) { // verifica se a aresta conecta dois nós do conjunto e se o peso é menor que o atual menor
                menor = a->peso;
                u = id1;
                v = id2;
            }
        }
    }

    // se não houver aresta de menor peso, retorna o grafo vazio
    if (u == '\0' || v == '\0') return agm;

    // aresta inicial (u,v)
    No* nu = nullptr;
    No* nv = nullptr;
    for (No* no : novos_nos) { 
        if (no->id == u) nu = no;
        if (no->id == v) nv = no;
    }

    Aresta* a_ini = new Aresta(nu, nv, menor); // cria a aresta inicial com o menor peso encontrado
    nu->arestas.push_back(a_ini);
    nv->arestas.push_back(a_ini);
    arestas_agm.push_back(a_ini); 

    // inicializa o vetor prox inicialmente com \0 e depois com os nós adjacentes a u e v
    for (int i = 0; i < n; i++) {
        if (ids_nos[i] == u || ids_nos[i] == v) {
            prox[i] = '\0';
            continue;
        }

        int peso_u = 999999; // inicializa com um valor alto
        int peso_v = 999999;

        // busca o peso das arestas adjacentes a u e v
        No* ni = buscarNo(ids_nos[i]);
         for (Aresta* a : ni->arestas) {
            if ((a->no_destino->id == u || a->no_origem->id == u) && a->peso < peso_u)
                peso_u = a->peso;
            if ((a->no_destino->id == v || a->no_origem->id == v) && a->peso < peso_v)
                peso_v = a->peso;
        }

        prox[i] = (peso_u < peso_v) ? u : v;
    }

    int contador = 0;
    while (contador < n - 2) {
        int menor = 999999; // inicializa com um valor alto
        int j = -1;
        for (int i = 0; i < n; i++) {
            if (prox[i] == '\0') 
                continue; // ignora os nós já adicionados à AGM 

            char vi = ids_nos[i];
            char pi = prox[i];

            // procura a aresta de menor peso entre vi e pi
            No* ni = buscarNo(vi);
            for (Aresta* a : ni->arestas) {
                char u = a->no_origem->id;
                char v = a->no_destino->id;
                if ((u == vi && v == pi) || (u == pi && v == vi)) {
                    if (a->peso < menor) {
                        menor = a->peso;
                        j = i;
                    }
                }
            }
        }

        // se j for -1, significa que não há mais arestas a serem adicionadas
        if (j == -1) break;

        char no_j = ids_nos[j]; 
        char pai = prox[j];

        No* nj = nullptr;
        No* np = nullptr;
        for (No* no : novos_nos) { // encontra os nós correspondentes
            if (no->id == no_j) nj = no;
            if (no->id == pai) np = no;
        }

        // adiciona a aresta (nj, np) com o peso menor encontrado
        Aresta* a = new Aresta(nj, np, menor);
        nj->arestas.push_back(a);
        np->arestas.push_back(a);
        arestas_agm.push_back(a);

        prox[j] = '\0';

        // atualiza o vetor prox com os nós adjacentes a no_j
        for (int i = 0; i < n; i++) {
            if (prox[i] != '\0') {
                char vi = ids_nos[i];
                No* ni = buscarNo(vi);

                for (Aresta* a : ni->arestas) { // verifica se a aresta é adjacente a no_j
                    if ((a->no_origem->id == vi && a->no_destino->id == no_j) ||
                        (a->no_destino->id == vi && a->no_origem->id == no_j)) {

                        // encontra o peso atual da aresta entre vi e prox[i]
                        int peso_atual = 999999;
                        for (Aresta* a2 : ni->arestas) {
                            if ((a2->no_origem->id == vi && a2->no_destino->id == prox[i]) ||
                                (a2->no_destino->id == vi && a2->no_origem->id == prox[i])) {
                                peso_atual = a2->peso;
                                break;
                            }
                        }

                        // se a nova aresta for de menor peso, atualiza o vetor prox
                        if (a->peso < peso_atual) {
                            prox[i] = no_j;
                        }
                    }
                }
            }
        }

        contador++; // incrementa o contador de arestas adicionadas
    }



    cout << "\nArestas da Arvore Geradora Minima (Prim):\n";
    for (Aresta* a : arestas_agm) {
        cout << a->no_origem->id << " - " << a->no_destino->id << " (peso " << a->peso << ")\n";
    }

    return agm;
}

Grafo * Grafo::arvore_geradora_minima_kruskal(vector<char> ids_nos) {
   Grafo* agm = new Grafo(); // cria um novo grafo para a árvore geradora mínima (agm)
    agm->set_ordem(ids_nos.size());
    agm->in_direcionado = false;
    agm->in_ponderado_aresta = true;

 // cria novos nós para a árvore geradora mínima (agm) com os ids fornecidos e adiciona esses nós à lista de adjacência do grafo agm
    vector<No*> novos_nos;
    vector<Aresta*> arestas_agm; // vetor para armazenar a ordem de inserção das arestas

    for (char id : ids_nos) {
        No* novo_no = new No(id);
        novos_nos.push_back(novo_no);
        agm->lista_adj.push_back(novo_no);
    }

// coletar os nós novos no grafo agm
    vector<Aresta*> arestas;
    for(int i = 0; i < lista_adj.size(); i++) {
        No* no = lista_adj[i];
        bool contem_i = false;
        for (char id : ids_nos) { // verifica se o nó atual contém algum dos ids fornecidos, se sim, adiciona as arestas desse nó à lista de arestas que serão consideradas para a árvore geradora mínima
            if (no->id == id) {
                contem_i = true;
                break;
             }
            }
        
        if(!contem_i)  // se o nó não contém nenhum dos ids fornecidos, pula para o próximo nó
            continue;
        
 // adiciona as arestas do nó atual à lista de arestas que serão consideradas para a árvore geradora mínima
        for(int j = 0; j < no->arestas.size(); j++){
            Aresta* aresta = no->arestas[j];
            char u = aresta->no_origem->id;
            char v = aresta->no_destino->id;

            bool contem_u = false;
            bool contem_v = false;

            for (char id : ids_nos) { // verifica se a aresta contém os nós u e v
                if (u == id) {
                    contem_u = true;
                }
                if (v == id) {
                    contem_v = true;
                }
            }
// verifica se a aresta contém ambos os nós u e v, se sim, adiciona a aresta à lista de arestas que serão consideradas para a árvore geradora mínima
            if (contem_u && contem_v) { 
                bool ja_adicionada = false;
                for(Aresta* a : arestas){ // verifica se a aresta já foi adicionada
                    char a_u = a->no_origem->id;
                    char a_v = a->no_destino->id;
                    if ((a_u == u && a_v == v) || (a_u == v && a_v == u)) {
                        ja_adicionada = true;
                    }

                }
                if (!ja_adicionada) // se a aresta ainda não foi adicionada, adiciona a aresta à lista
                    arestas.push_back(aresta);
            }   
        }
    }
// ordena as arestas por peso utilizando o bubble sort
    for (int i = 0; i < arestas.size() - 1; i++) {
        for (int j = 0; j < arestas.size() - i - 1; j++) {
            if (arestas[j]->peso > arestas[j + 1]->peso) {
                Aresta* temp = arestas[j];
                arestas[j] = arestas[j + 1];
                arestas[j + 1] = temp;
            }
        }
    }

// inicializa a arvore geradora mínima (agm) 
    vector <char> subarvore;
    for(int i = 0; i < ids_nos.size(); i++) {
        subarvore.push_back(ids_nos[i]);
    }

    int cont = 0;   
// percorre as arestas ordenadas e adiciona as arestas à árvore geradora mínima (agm) se os nós de origem e destino não estiverem no mesmo grupo
// se estiverem no mesmo grupo, a aresta não é adicionada, porque configura como um ciclo
    for (int i = 0; i < arestas.size() && cont < ids_nos.size()-1; i++){
        Aresta* a = arestas[i];
        char u = a->no_origem->id;
        char v = a->no_destino->id;

        char grupo_u = '\0'; // inicializa o grupo do nó u e v
        char grupo_v = '\0';

        for(int j = 0; j < subarvore.size(); j++) {
            if (ids_nos[j] == u) 
                grupo_u = subarvore[j];
            
            if (ids_nos[j] == v) 
                grupo_v = subarvore[j];
        }
 // verifica se os grupos dos nós u e v são diferentes, se sim, adiciona a aresta à árvore geradora mínima
        if(grupo_u != grupo_v){
            for(int j = 0; j < subarvore.size(); j++) {
                if (subarvore[j] == grupo_v) {
                    subarvore[j] = grupo_u; // unindo os grupos
                }
            }
            No* no_u = nullptr; 
            No* no_v = nullptr;

            for(No* no : novos_nos) { // encontra os nós correspondentes aos ids u e v
                if (no->id == u) {
                    no_u = no;
                }
                if (no->id == v) {
                    no_v = no;
                }
            }
// se os nós correspondentes forem encontrados, cria uma nova aresta e adiciona aos nós u e v
            Aresta* nova_aresta = new Aresta(no_u, no_v, a->peso);
            no_u->arestas.push_back(nova_aresta);
            no_v->arestas.push_back(nova_aresta); 
            arestas_agm.push_back(nova_aresta);

            cont ++;
        }
    }


     cout << "\nArestas da Arvore Geradora Minima (Kruskal):\n";
    for (Aresta* a : arestas_agm) {
        cout << a->no_origem->id << " - " << a->no_destino->id << " (peso " << a->peso << ")\n";
    }

    return agm;
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
