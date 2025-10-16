#include "../class/ga.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <numeric>
#include <iomanip>      // Formatar print

GA::GA(const Mapa& mapa, int tamPop, int numGen, float taxaMut)
    :   mapa(mapa),
        tamPop(tamPop),
        numGen(numGen),
        taxaMut(taxaMut)
{
    //
}

void GA::startPop()
{
    int n = mapa.getNumPontos();
    populacao.clear();

    // Gerador aleatório
    std::random_device rd;
    std::mt19937 g(rd());

    // Rotas aleatórias
    for(int i = 0; i < tamPop; i++)
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

    for(int i = 0; i < n - 1; i++)
    {
        distancia += mapa.getDist(rota[i], rota[i + 1]);
    }

    distancia += mapa.getDist(rota[n - 1], rota[0]);
    return distancia;
}

void GA::avaliarPop()
{
    aptidoes.clear();

    for(auto& rota : populacao)
    {
        aptidoes.push_back(calcDist(rota));
    }
}

void GA::printPop() const
{
    for(size_t i = 0; i < populacao.size(); i++)
    {
        std::cout << "Indivíduo " << i << ": ";
        for(int cidade : populacao[i])
        {
            std::cout << cidade << " ";
        }
        std::cout << "| Distância: " << std::fixed << std::setprecision(2) << aptidoes[i] << "\n";
    }
}