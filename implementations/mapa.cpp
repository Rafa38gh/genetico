#include "../class/mapa.h"
#include <iostream>
#include <iomanip>

Mapa::Mapa() = default;


void Mapa::adicionarPonto(float x, float y)
{
    int n;

    pontos.push_back({x, y});

    n = pontos.size();
    distancias.resize(n);
    for(auto &linha : distancias)
    {
        linha.resize(n, 0.0f);
    }
}

void Mapa::calcDist()
{
    int n = pontos.size();

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i == j)
            {
                distancias[i][j] = 0.0f;
            } else
            {
                float dx = pontos[i].x - pontos[j].x;
                float dy = pontos[i].y - pontos[j].y;
                distancias[i][j] = std::sqrt(dx * dx + dy * dy);
            }
        }
    }
}

void Mapa::calcDistOtima(){


}

Ponto Mapa::getPonto(int i) const
{
    return pontos[i];
}

float Mapa::getDist(int i, int j) const
{
    return distancias[i][j];
}

int Mapa::getNumPontos() const
{
    return pontos.size();
}

void Mapa::printMatriz() const
{
    std::cout << std::fixed << std::setprecision(2);        // Imprimir usando 2 casas decimais

    for(int i = 0; i < distancias.size(); i++)
    {
        for(int j = 0; j < distancias[i].size(); j++)
        {
            std::cout << distancias[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

void Mapa::printPontos() const {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Pontos:\n";
    for (size_t i = 0; i < pontos.size(); ++i) {
        if(i < pontos.size() - 1){
            std::cout << "[" << pontos[i].x << ", " << pontos[i].y << "], \n";
        }
        else{
        std::cout << "[" << pontos[i].x << ", " << pontos[i].y << "]\n";
        }
    }
}