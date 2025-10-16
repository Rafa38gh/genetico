#ifndef GA_H
#define GA_H

#include <vector>
#include <mapa.h>

class GA
{
    private:
        const Mapa& mapa;
        int tamPop;
        int numGen;
        float taxaMut;

        std::vector<std::vector<int>> populacao;        // Lista de rotas
        std::vector<float> aptidoes;                    // Distância das rotas

    public:
        GA(const Mapa& mapa, int tamPop, int numGen, float taxaMut);

        void startPop();
        float calcDist(const std::vector<int>& rota);
        void avaliarPop();
        void printPop() const;
};

#endif