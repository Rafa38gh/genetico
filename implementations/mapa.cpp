#include "../class/mapa.h"
#include <iostream>

Mapa::Mapa(int n)
{
    pontos.resize(n);
    distancias.resize(n, std::vector<float>(n, 0.0f));
}

void Mapa::adicionarPonto(int i, float x, float y)
{
    pontos.push_back({x, y});
}

void Mapa::setDist(int i, int j, float valor)
{
    if(i >= 0 && j >= 0 && i < (int)distancias.size() && j < (int)distancias.size())
    {
        distancias[i][j] = valor;
    }
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
    for(int i = 0; i < distancias.size(); i++)
    {
        for(int j = 0; j < distancias[i].size(); j++)
        {
            std::cout << distancias[i][j] << "\t";
        }
        std::cout << "\n";
    }
}