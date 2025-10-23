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
        float taxaElit;
        int tamanhoTorneio; //necessidade de selação no algoritmo genético

        std::vector<std::vector<int>> populacao;        // Lista de rotas
        std::vector<float> aptidoes;                    // Distância das rotas

    public:
        GA(const Mapa& mapa, int tamPop, int numGen, float taxaMut, float taxaElit = 0.1f, int tamanhoTorneio = 5);

        void startPop();
        float calcDist(const std::vector<int>& rota);
        void avaliarPop();
        void printPop() const;
        float calcApt(const std::vector<int>& rota);   //inverso do distancia

        std::vector<int> selecaoTorneio();
        std::vector<int> cruzamentoOX(const std::vector<int>& pai1, const std::vector<int>& pai2);
        void muta(std::vector<int>& rota);
        void evoluir();                               //loop de geracoes com rastreaamento
};

#endif