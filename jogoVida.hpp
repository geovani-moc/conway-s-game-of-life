#ifndef jogoVida_H
#define jogoVida_H

#include <stdio.h>
#include <stdlib.h>

#include <chrono>
#include <thread>

#define TEMPO 1000

class JogoVida
{
private:
    size_t tamanhoTabuleiro, quantidadeInicialIndividuos;
    bool** tabuleiro;
    bool** tabuleiroAuxiliar;
public:
    JogoVida();
    ~JogoVida();
    void iniciar();

    void jogo();
    void verTabuleiro();
    bool atualizaPosicao(size_t x, size_t y);
    bool existeIndividuos();

    bool** alocarMatriz(size_t tamanho);
    void destruirMatriz();
    void inserirIndividuo();
    void zerarMatriz();
    bool campoValido(size_t x, size_t y);
    size_t contarVizinhos(size_t x, size_t y);

    void copiarTabuleiro(bool** original, bool** copia);
    bool semModificacaoTabuleiro();
};



#endif