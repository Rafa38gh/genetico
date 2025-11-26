#include "class/mapa.h"
#include "class/ga.h"
#include <iostream>
#include <random>
#include <cmath>
#include <fstream>

std::mt19937 rng(std::random_device{}());

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

Mapa gerarMapaCirculo(int numPontos, float raio = 100000.0f) {
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
    int numPontos = 90;
    int tamPop = 200;
    int numGen = 8000;
    float taxaMut = 0.8f;
    
    double dist = 0.0f;
    

    Mapa mapa = gerarMapaCirculo(numPontos);
    std::ofstream pontos_file("pontos_uniforme.csv");
    for (int i = 0; i < numPontos; ++i) {
        auto p = mapa.getPonto(i);
        pontos_file << p.x << "," << p.y << "\n";
    }
    pontos_file.close();
    GA gaUniforme(mapa, tamPop, numGen, taxaMut);
    gaUniforme.evoluir();
    gaUniforme.salvarHistorico("evolucao.csv");
    gaUniforme.salvarMelhorRota("melhor_rota.txt");

    for (int j = 0; j < numPontos; j++){
        dist += mapa.getDist(j, (j + 1) % numPontos);
    }

    std::cout << "Distância total (circular): " << dist << std::endl;

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