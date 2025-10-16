#include "class/mapa.h"
#include <iostream>

int main()
{
    Mapa mapa;

    mapa.adicionarPonto(1.0f, 2.0f);
    mapa.adicionarPonto(3.0f, 4.0f);
    mapa.adicionarPonto(5.0f, 6.0f);
    mapa.adicionarPonto(2.0f, 7.0f);

    std::cout << "Pontos: \n";
    for(int i = 0; i < mapa.getNumPontos(); i++)
    {
        Ponto p = mapa.getPonto(i);
        std::cout << "Ponto" << i << ": (" << p.x << ", " << p.y << ")\n";
    }

    std::cout << "Matriz:\n";
    mapa.calcDist();
    mapa.printMatriz();

    return 0;
}