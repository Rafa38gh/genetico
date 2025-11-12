#ifndef MAPA_H
#define MAPA_H

#include <vector>
#include <cmath>

struct Ponto
{
    float x;
    float y;
};

class Mapa
{
    private:
        std::vector<Ponto> pontos;
        std::vector<std::vector<float>> distancias;

    public:
        Mapa();

        void adicionarPonto(float x, float y);
        void calcDist();
        void calcDistOtima();
        
        // Setters
        //void setDist(int i, int j, float valor);

        // Getters
        Ponto getPonto(int i) const;
        float getDist(int i, int j) const;
        int getNumPontos() const;
        void printPontos() const;    
        void printMatriz() const;
};

#endif // MAPA_H