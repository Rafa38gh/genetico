#include "class/mapa.h"
#include "class/ga.h"
#include <iostream>
#include <random>
#include <cmath>

Mapa gerarMapaUniforme(int numPontos, float tamanho = 10.0f) {
    Mapa mapa;
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_real_distribution<float> dist(0.0f, tamanho);
    for (int i = 0; i < numPontos; ++i) {
        mapa.adicionarPonto(dist(g), dist(g));
    }
    mapa.calcDist();
    //mapa.printMatriz();
    mapa.printPontos();
    return mapa;
}

Mapa gerarMapaCirculo(int numPontos, float raio = 5.0f) {
    Mapa mapa;
    float centroX = 5.0f, centroY = 5.0f;
    for (int i = 0; i < numPontos; ++i) {
        float angulo = 2 * M_PI * i / numPontos;
        float x = centroX + raio * std::cos(angulo);
        float y = centroY + raio * std::sin(angulo);
        mapa.adicionarPonto(x, y);
    }
    mapa.calcDist();
    //  mapa.printMatriz();
    mapa.printPontos();
    return mapa;
}

int main()
{
    int numPontos = 50;
    int tamPop = 1000;
    int numGen = 1000;
    float taxaMut = 0.05f;

    std::cout << "Cenário Uniforme\n";
    Mapa mapaUniforme = gerarMapaUniforme(numPontos);
    GA gaUniforme(mapaUniforme, tamPop, numGen, taxaMut);
    gaUniforme.evoluir();

    /*std::cout << "\nCenário Circular\n";
    Mapa mapaCirculo = gerarMapaCirculo(numPontos);
    GA gaCirculo(mapaCirculo, tamPop, numGen, taxaMut);
    gaCirculo.evoluir();

    std::cout << "\nCircular com 30 pontos\n";
    Mapa mapaBonus = gerarMapaCirculo(30);
    GA gaBonus(mapaBonus, tamPop, numGen * 2, taxaMut);
    gaBonus.evoluir();*/

    return 0;
}