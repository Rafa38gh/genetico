#include "../class/ga.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <numeric>
#include <iomanip>
#include <chrono>

GA::GA(const Mapa& mapa, int tamPop, int numGen, float taxaMut, float taxaElit, int tamanhoTorneio)
    : mapa(mapa), tamPop(tamPop), numGen(numGen), taxaMut(taxaMut), taxaElit(taxaElit), tamanhoTorneio(tamanhoTorneio)
{
    if (mapa.getNumPontos() < 2) throw std::runtime_error("Mapa deve ter pelo menos 2 pontos");
    if (tamPop <= 0 || taxaMut < 0 || taxaMut > 1 || taxaElit < 0 || taxaElit > 1 || tamanhoTorneio <= 0)
        throw std::runtime_error("Parâmetros inválidos");
}

void GA::startPop()
{
    int n = mapa.getNumPontos();
    populacao.clear();
    aptidoes.clear();
    std::random_device rd;
    std::mt19937 g(rd());
    for (int i = 0; i < tamPop; i++)
    {
        std::vector<int> rota(n);
        std::iota(rota.begin(), rota.end(), 0);
        std::shuffle(rota.begin(), rota.end(), g);
        populacao.push_back(rota);
    }
}

float GA::calcDist(const std::vector<int>& rota)
{
    float distancia = 0.0f;
    int n = rota.size();
    for (int i = 0; i < n - 1; i++)
    {
        distancia += mapa.getDist(rota[i], rota[i + 1]);
    }
    distancia += mapa.getDist(rota[n - 1], rota[0]);
    return distancia;
}

float GA::calcApt(const std::vector<int>& rota)
{
    float dist = calcDist(rota);            //apitdao e o inverso da dist
    return dist > 0 ? 1.0f / dist : 1e10;   //evita div por 0
}

void GA::avaliarPop()
{
    aptidoes.clear();
    for (auto& rota : populacao)
    {
        aptidoes.push_back(calcApt(rota));
    }
}

void GA::printPop() const
{
    for (size_t i = 0; i < populacao.size(); i++)
    {
        std::cout << "Indivíduo " << i << ": ";
        for (int cidade : populacao[i])
        {
            std::cout << cidade << " ";
        }
        std::cout << "| Distância: " << std::fixed << std::setprecision(2) << (1.0f / aptidoes[i]) << "\n";
    }
}

//func de selecao por torneio, retorna a rota do melhor individuo selecionado
std::vector<int> GA::selecaoTorneio()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<int> candidatos(tamanhoTorneio);                //indices dos individuos selecionados
    std::generate(candidatos.begin(), candidatos.end(), [&]() { return std::uniform_int_distribution<>(0, tamPop - 1)(g); });  //seleciona individuos aleatoriamente
    auto melhor = *std::max_element(candidatos.begin(), candidatos.end(), [&](int a, int b) { return aptidoes[a] < aptidoes[b]; }); //compara aptidoes para encontrar o melhor
    return populacao[melhor];                                   //apos encontrar a melhor rota, retorna ela
}

//func de cruzamento (ordered crossover) retorna a rota do filho gerado
std::vector<int> GA::cruzamentoOX(const std::vector<int>& pai1, const std::vector<int>& pai2)
{
    int n = pai1.size();          //tamanho da rota
    std::random_device rd;
    std::mt19937 g(rd());
    int inicio = std::uniform_int_distribution<int>(0, n - 2)(g);           //gera dois pontos de corte
    int fim = std::uniform_int_distribution<int>(inicio + 1, n - 1)(g);      
    std::vector<int> filho(n, -1);                                          //inicializa rota do filho com -1
    for (int i = inicio; i <= fim; i++)
    {
        filho[i] = pai1[i];                                                 //copia segmento do pai1 para o filho
    }
    int idx = (fim + 1) % n;                                                //indice x para preencher o resto do filho
    for (int i = 0; i < n; i++)                                             
    {
        int val = pai2[i];
        if (std::find(filho.begin(), filho.end(), val) == filho.end())      //se o valor do pai2 nao esta no filho
        {                                                                   //adiciona no filho                
            while (filho[idx] != -1)
            {
                idx = (idx + 1) % n;
            }
            filho[idx] = val;
            idx = (idx + 1) % n;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (filho[i] == -1) throw std::runtime_error("Filho inválido no cruzamentoOX");
    }
    return filho;
}

//func de mutacao por swap, troca duas cidades na rota com probabilidade taxaMut
void GA::muta(std::vector<int>& rota)
{
    std::random_device rd;
    std::mt19937 g(rd());
    if (std::uniform_real_distribution<>(0.0, 1.0)(g) < taxaMut)
    {
        int i = std::uniform_int_distribution<int>(0, rota.size() - 1)(g);
        int j = std::uniform_int_distribution<int>(0, rota.size() - 1)(g);
        std::swap(rota[i], rota[j]);
    }
}

//func principal do alg genetico, realiza o loop de geracoes com rastreamento
void GA::evoluir()
{
    startPop();                     //inicializa populacao
    avaliarPop();                   //avalia populacao inicial
    auto inicio = std::chrono::high_resolution_clock::now();

    for (int gen = 0; gen < numGen; ++gen)
    {
        std::vector<std::vector<int>> novaPop;                  //gera nova populacao
        int numElites = static_cast<int>(taxaElit * tamPop);    //calcula numero de elites
        std::vector<int> elitesIdx(tamPop);                     
        std::iota(elitesIdx.begin(), elitesIdx.end(), 0);           //indices de todos individuos
        std::sort(elitesIdx.begin(), elitesIdx.end(), [&](int a, int b) { return aptidoes[a] > aptidoes[b]; });  //ordena indices por aptidao
        for (int i = 0; i < numElites; ++i)
        {
            novaPop.push_back(populacao[elitesIdx[i]]);
        }

        while (novaPop.size() < tamPop)                     //preenche o resto da nova populacao
        {
            auto pai1 = selecaoTorneio();                   //seleciona pais por torneio
            auto pai2 = selecaoTorneio();
            auto filho = cruzamentoOX(pai1, pai2);          //cruza pais
            muta(filho);                                    //aplica a mutacao no filho
            novaPop.push_back(filho);
        }

        populacao = novaPop;
        avaliarPop();                                       //avalia nova populacao                           

        if (gen % 100 == 0 || gen == numGen - 1)            //depuração a cada 100 gerações
        {
            int melhorIdx = std::distance(aptidoes.begin(), std::max_element(aptidoes.begin(), aptidoes.end()));
            float melhorDist = 1.0f / aptidoes[melhorIdx];
            std::cout << "Geração " << gen << ": Melhor Distância = " << std::fixed << std::setprecision(2) << melhorDist
                      << ", Rota = ";
            for (size_t i = 0; i < populacao[melhorIdx].size(); ++i) {
                std::cout << populacao[melhorIdx][i];
                if (i < populacao[melhorIdx].size() - 1) {
                    std::cout << ", ";
                }
            }
            
            std::cout << "\n";
        }
    }

    auto fim = std::chrono::high_resolution_clock::now();  //calcula tempo total
    std::chrono::duration<double> tempo = fim - inicio;
    std::cout << "Tempo total: " << tempo.count() << " segundos\n";
}