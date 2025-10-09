#include "class/mapa.h"
#include <iostream>

int main()
{
    Mapa mapa(3);

    mapa.adicionarPonto(0, 1.0f, 2.0f);
    mapa.adicionarPonto(1, 3.0f, 4.0f);
    mapa.adicionarPonto(2, 5.0f, 6.0f);

    mapa.setDist(0, 1, 3.2f);
    mapa.setDist(0, 2, 4.5f);
    mapa.setDist(1, 2, 2.8f);
    mapa.setDist(1, 0, 3.2f);
    mapa.setDist(2, 0, 4.5f);
    mapa.setDist(2, 1, 2.8f);

    std::cout << "Matriz:\n";
    mapa.printMatriz();

    std::cout << "Coordenadas dos pontos:\n";
    for(int i = 0; i < mapa.getNumPontos(); i++)
    {
        Ponto p = mapa.getPonto(i);
        std::cout << "Ponto" << i << ": (" << p.x << ", " << p.y << ")\n";
    }

    return 0;
}