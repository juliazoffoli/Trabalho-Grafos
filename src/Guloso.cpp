#include "Guloso.h"
#include <fstream>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <ctime>
#include <limits.h>
#include <cmath>


using namespace std;

Guloso::Guloso() {   
}

Guloso::~Guloso() {
}

vector<pair<char, char>> Guloso::algoritmo_guloso(Grafo* grafo) {

    this->arquivo = ofstream ("[DEBUG]guloso.txt");
    this->arquivo << grafo->instancia << endl << endl;

    vector<pair<char, char>> solucao;
    obter_arestas_nao_cobertas(grafo);
    int quant_arestas = this->arestas_nao_cobertas.size();

    int exec = 0;
    while (!arestas_nao_cobertas.empty()) {

        // DEBUG
        exec++;
        this->arquivo << "\n[DEBUG] Execução " << exec << ":\n";
        this->arquivo << "[DEBUG] Arestas não cobertas: " << endl;
        for (pair<char, char> aresta : arestas_nao_cobertas)
            this->arquivo << "(" << aresta.first << ", " << aresta.second << ") ";
        this->arquivo << endl;

        // Calcula o grau dos vértices das arestas não cobertas
        map<char, int> grau_vertices = obter_grau_vertices();

        // Calcula o grau das arestas (soma dos graus dos vértices da aresta) e ordena
        vector<pair<pair<char, char>, int>> arestas_com_grau = obter_arestas_ordenadas(grau_vertices);
        
        // Obtem a aresta com maior grau
        pair<char, char> aresta_escolhida = arestas_com_grau.begin()->first;
        int max_grau = arestas_com_grau.begin()->second;
        this->arquivo << "[DEBUG] Aresta selecionada: (" << aresta_escolhida.first << ", " << aresta_escolhida.second << ") com grau " << max_grau << endl;

        solucao.push_back(aresta_escolhida);
        this->arquivo << "[DEBUG] Solução: ";
        for (pair<char, char> aresta: solucao)
            this->arquivo << " (" << aresta.first << ", " << aresta.second << ") ";
        this->arquivo << endl;

        // Remove as arestas_incidentes incidentes aos vértices da aresta selecionada
        remove_arestas_incidentes(aresta_escolhida);
    }
 
    this->arquivo << "[DEBUG] Solução final: ";
    for (pair<char, char> aresta : solucao)
        this->arquivo << "(" << aresta.first << ", " << aresta.second << ") ";
    this->arquivo << endl;

    this->arquivo << "[DEBUG] Tamanho do Conjunto de Arestas do Grafo: " << quant_arestas << endl;
    this->arquivo << "[DEBUG] Tamanho do Conjunto Dominante: " << solucao.size() << endl;
    return solucao;
}

vector<pair<char, char>> Guloso::algoritmo_guloso_randomizado_adaptativo(Grafo* grafo, double alfa) {

    int iteracao = 0;
    this->arquivo = ofstream ("[DEBUG]guloso_randomizado_adaptativo.txt");
    this->arquivo << grafo->instancia << endl << endl;

    vector<pair<char, char>> solucao;
    obter_arestas_nao_cobertas(grafo);
    int quant_arestas = this->arestas_nao_cobertas.size();

    int exec = 0;
    while (!arestas_nao_cobertas.empty()) {

        // DEBUG
        exec++;
        this->arquivo << "\n[DEBUG] Execução " << exec << ":\n";
        this->arquivo << "[DEBUG] Arestas não cobertas: " << endl;
        for (pair<char, char> aresta : arestas_nao_cobertas)
            this->arquivo << "(" << aresta.first << ", " << aresta.second << ") ";
        this->arquivo << endl;

        // Calcula o grau dos vértices das arestas não cobertas
        map<char, int> grau_vertices = obter_grau_vertices();

        // Calcula o grau das arestas (soma dos graus dos vértices da aresta) e ordena
        vector<pair<pair<char, char>, int>> arestas_com_grau = obter_arestas_ordenadas(grau_vertices);
        
        // Obtem a aresta com maior grau
        // Parte randomizada
        //int lim_superior = (alfa * arestas_com_grau.size()); // limite superior do intervalo a ser escolhido aleatoriamente
        // int lim_superior = (alfa * arestas_com_grau.size() - 1) + 1; // limite superior do intervalo a ser escolhido aleatoriamente
        int lim_superior = max(1, (int)ceil(alfa * arestas_com_grau.size())); // garante que o limite superior seja pelo menos 1 (ceil arredonda para cima e evita ignorar uma aresta)
        int K = rand() % lim_superior; // índice do vetor ordenado de arestas, escolhido aleatoriamente entre o intervalo do vetor, determinada por alfa.
        this->arquivo << "[DEBUG] Valor do i entre 0 e " << lim_superior << ". Valor escolhido: " << K << "." << endl;

  
   
        pair<char, char> aresta_escolhida = arestas_com_grau[K].first;
        int grau_aresta_escolhida = arestas_com_grau[K].second;
        this->arquivo << "[DEBUG] Aresta selecionada: (" << aresta_escolhida.first << ", " << aresta_escolhida.second << ") com grau " << arestas_com_grau[K].second << endl;
        
        // Testar viabilidade
        // pair<char, char> aresta_escolhida = arestas_com_grau.begin()->first;
        // int max_grau = arestas_com_grau.begin()->second;
        // if(!(grau_aresta_escolhida == max_grau)) {
        //    this->arquivo << "[DEBUG] Aresta (" << aresta_escolhida.first << "), " << aresta_escolhida.second << ") não viável";
        //    continue;
        // }

        solucao.push_back(aresta_escolhida);
        this->arquivo << "[DEBUG] Solução: ";
        for (pair<char, char> aresta: solucao)
            this->arquivo << " (" << aresta.first << ", " << aresta.second << ") ";
        this->arquivo << endl;

        // Remove as arestas_incidentes incidentes aos vértices da aresta selecionada
        remove_arestas_incidentes(aresta_escolhida);
    }
 

    this->arquivo << "[DEBUG] Solução final: ";
    for (pair<char, char> aresta : solucao)
        this->arquivo << "(" << aresta.first << ", " << aresta.second << ") ";
    this->arquivo << endl;

    this->arquivo << "[DEBUG] Tamanho do Conjunto de Arestas do Grafo: " << quant_arestas << endl;
    this->arquivo << "[DEBUG] Tamanho do Conjunto Dominante: " << solucao.size() << endl;
 return solucao;

}

vector<pair<char, char>> Guloso::algoritmo_guloso_randomizado_adaptativo_reativo(Grafo* grafo, vector<double> alfas, int num_iter, int bloco) {
    
    this->arquivo = ofstream("[DEBUG]guloso_randomizado_adaptativo_reativo.txt");
    this->arquivo << grafo->instancia << endl << endl;

    vector<pair<char, char>> melhor_sol;
    int m = alfas.size();
    vector<double> P(m, 1.0 / m);   // Probabilidades iniciais iguais
    vector<double> M(m, 0.0);       // Soma de qualidade por alfa
    vector<int> cont(m, 0);         // Contagem de usos por alfa, para média

    int melhor_tam = INT_MAX; // tamanho da melhor solução

    for (int iter = 1; iter <= num_iter; iter++) { // Executa num_iter vezes, cada vez construindo uma solução completa

        this->arquivo << "\n[DEBUG] Iteração " << iter << ":\n";

        // Escolha do alfa com base em P
        double r = ((double) rand() / RAND_MAX); // numero aleatorio entre 0 e 1
        double soma = 0.0;
        int idx = 0;
        for (; idx < m; idx++) {
            soma += P[idx];
            if (r <= soma) break;
        }
        double alfa_escolhido = alfas[idx];
        cont[idx]++;

        this->arquivo << "[DEBUG] Alfa escolhido: " << alfa_escolhido << " (índice " << idx << ")\n";

        // Reiniciar arestas nao cobertas para esta iteração
        obter_arestas_nao_cobertas(grafo);

        vector<pair<char, char>> solucao;

        // Executa o guloso randomizado adaptativo com este alfa
        int exec = 0;
        while (!arestas_nao_cobertas.empty()) {
            exec++;
            this->arquivo << "[DEBUG] Execução " << exec << " - Arestas não cobertas: ";
            for (auto &aresta : arestas_nao_cobertas)
                this->arquivo << "(" << aresta.first << ", " << aresta.second << ") ";
            this->arquivo << endl;

            map<char, int> grau_vertices = obter_grau_vertices();
            vector<pair<pair<char, char>, int>> arestas_com_grau = obter_arestas_ordenadas(grau_vertices);

            int lim_superior = (alfa_escolhido * arestas_com_grau.size());
            if (lim_superior < 1) 
                lim_superior = 1;
            int K = rand() % lim_superior;

            this->arquivo << "[DEBUG] lim_superior = " << lim_superior << ", índice sorteado K = " << K << endl;

            pair<char, char> aresta_escolhida = arestas_com_grau[K].first;
            int grau_aresta_escolhida = arestas_com_grau[K].second;

            this->arquivo << "[DEBUG] Aresta selecionada: (" << aresta_escolhida.first << ", " << aresta_escolhida.second 
                          << ") com grau " << grau_aresta_escolhida << endl;

            solucao.push_back(aresta_escolhida);

            this->arquivo << "[DEBUG] Solução parcial: ";
            for (auto &a : solucao)
                this->arquivo << "(" << a.first << ", " << a.second << ") ";
            this->arquivo << endl;

            remove_arestas_incidentes(aresta_escolhida);
        }

        int tam_sol = solucao.size();
        this->arquivo << "[DEBUG] Tamanho da solução atual: " << tam_sol << endl;

        // Atualiza melhor solução
        if (tam_sol < melhor_tam) {
            melhor_tam = tam_sol;
            melhor_sol = solucao;
            this->arquivo << "[DEBUG] Nova melhor solução encontrada com tamanho " << melhor_tam << endl;
        }

        // Atualiza média para alfa escolhido
        M[idx] += tam_sol;

        // Atualiza probabilidades a cada bloco
        if (iter % bloco == 0) {
            this->arquivo << "[DEBUG] Atualizando probabilidades após " << iter << " iterações\n";

            for (int i = 0; i < m; i++) {
                if (cont[i] > 0) // média real e não zero
                    M[i] /= cont[i];
                else // caso não tenha sido usado
                    M[i] = 1e9;
                this->arquivo << "[DEBUG] Alfa " << alfas[i] << ": média M = " << M[i] << ", contagem = " << cont[i] << endl;
            }

            // Calcula q[i] = F(S*) / M[i]
            vector<double> q(m, 0.0);
            double soma_q = 0.0;
            for (int i = 0; i < m; i++) {
                q[i] = (double)melhor_tam / M[i];
                soma_q += q[i];
            }

            this->arquivo << "[DEBUG] Soma dos q[i]: " << soma_q << endl;

            // Atualiza P[i] = q[i] / soma_q
            for (int i = 0; i < m; i++) {
                if (soma_q > 0) P[i] = q[i] / soma_q;
                else P[i] = 1.0 / m;
                this->arquivo << "[DEBUG] Probabilidade P[" << i << "] = " << P[i] << endl;
            }

            // Zera contadores e médias acumuladas
            fill(M.begin(), M.end(), 0.0);
            fill(cont.begin(), cont.end(), 0);
        }
    }

    // Debug final da melhor solução
    this->arquivo << "\n[DEBUG] Melhor solução encontrada (" << melhor_tam << " arestas): ";
    for (auto &a : melhor_sol)
        this->arquivo << "(" << a.first << ", " << a.second << ") ";
    this->arquivo << endl;

    return melhor_sol;
}

void Guloso::obter_arestas_nao_cobertas(Grafo* grafo) {
    this->arestas_nao_cobertas = vector<pair<char, char>>();
    
    for (No* no : grafo->lista_nos) {
        for (Aresta* aresta : no->get_arestas()) {
            char id_origem = aresta->no_origem->get_id();
            char id_destino = aresta->no_destino->get_id();

            if (find(this->arestas_nao_cobertas.begin(), this->arestas_nao_cobertas.end(), make_pair(id_origem, id_destino)) == this->arestas_nao_cobertas.end() &&
                find(this->arestas_nao_cobertas.begin(), this->arestas_nao_cobertas.end(), make_pair(id_destino, id_origem)) == this->arestas_nao_cobertas.end()) {
               
                this->arestas_nao_cobertas.push_back(make_pair(id_origem, id_destino));
            }
        }
    }

    // DEBUG
    this->arquivo << "[DEBUG] Arestas não cobertas (antes de iniciar a execução): " << endl;
    for (pair<char, char> aresta : arestas_nao_cobertas)
        this->arquivo << "(" << aresta.first << ", " << aresta.second << ") ";
    this->arquivo << endl;
}

map<char, int> Guloso::obter_grau_vertices() {
    
    this->arquivo << "\n[DEBUG] Cálculo o grau dos vertices das arestas não cobertas: \n";
    
    // Calcula o grau dos vértices u e v que ainda nao foram cobertos
    map<char, int> grau_vertices;
    for (pair<char, char> aresta : this->arestas_nao_cobertas) {
        grau_vertices[aresta.first]++;
        grau_vertices[aresta.second]++;

        // DEBUG
        this->arquivo << "[DEBUG] Aresta: (" << aresta.first << ", " << aresta.second << ")\n";
        this->arquivo << "[DEBUG] Nó: " << aresta.first << ", Grau: " << grau_vertices[aresta.first] << endl;
        this->arquivo << "[DEBUG] Nó: " << aresta.second << ", Grau: " << grau_vertices[aresta.second] << endl;
    }

    this->arquivo << "\n[DEBUG] Grau dos vertices das arestas não cobertas: \n";
    for (pair<char, int> grau : grau_vertices)
        this->arquivo << "[DEBUG] Nó: " << grau.first << ", Grau: " << grau.second << endl;
    
    return grau_vertices;
}

vector<pair<pair<char, char>, int>> Guloso::obter_arestas_ordenadas(map<char, int> grau_vertices) {
    this->arquivo << "\n[DEBUG] Selecionando a aresta com maior grau...\n";

    // Calcula o grau das arestas (soma dos graus dos vértices da aresta)
    vector<pair<pair<char, char>, int>> arestas_com_grau;

    for (pair<char, char> aresta : this->arestas_nao_cobertas) {
        int grau = grau_vertices[aresta.first] + grau_vertices[aresta.second];
        arestas_com_grau.push_back(make_pair(aresta, grau));
        this->arquivo << "[DEBUG] Aresta: (" << aresta.first << ", " << aresta.second << "), Grau: " << grau << endl;
    }

    sort(arestas_com_grau.begin(), arestas_com_grau.end(),
         [](pair<pair<char, char>, int>& a, pair<pair<char, char>, int>& b) {
             return a.second > b.second; // Ordena em ordem decrescente pelo grau
         });
    
    return arestas_com_grau;
}

void Guloso::remove_arestas_incidentes(pair<char, char> aresta_selecionada) {
    char u = aresta_selecionada.first;
    char v = aresta_selecionada.second;

    this->arquivo << "\n[DEBUG] Removendo arestas incidentes aos vértices da aresta selecionada: (" << u << ", " << v << ")\n";
    for (int i = this->arestas_nao_cobertas.size()-1; i >= 0; i--) {
        pair<char, char> aresta = this->arestas_nao_cobertas[i];

        this->arquivo << "\n[DEBUG] Verificando aresta: (" << aresta.first << ", " << aresta.second << ")\n";
        if (aresta.first == u || aresta.second == u || aresta.first == v || aresta.second == v) {
            this->arquivo << "[DEBUG] Removendo aresta: (" << aresta.first << ", " << aresta.second << ")\n";
            this->arestas_nao_cobertas.erase(this->arestas_nao_cobertas.begin() + i);
        }
    }

    this->arquivo << "\n[DEBUG] Arestas não cobertas após remoção: " << endl;
    for (pair<char, char> aresta : this->arestas_nao_cobertas)
        this->arquivo << "(" << aresta.first << ", " << aresta.second << ") ";
    this->arquivo << endl;
}