#include "jogoVida.hpp"

JogoVida::JogoVida()
{
    quantidadeInicialIndividuos = 0;
    tamanhoTabuleiro = 0;
}

JogoVida::~JogoVida()
{
    destruirMatriz();
}

void JogoVida::iniciar()
{
    printf("Informe o tamanho do tabuleiro (valor entre 3 ou 12): ");
    while (tamanhoTabuleiro < 3 || tamanhoTabuleiro > 12)
    {
        scanf("%zu", &tamanhoTabuleiro);
    }

    size_t quantidadeMaximaIndividuos = (tamanhoTabuleiro * tamanhoTabuleiro) >> 1;
    printf("\nInforme a quantidade de individuos (valor entre 1 e %zu): ", quantidadeMaximaIndividuos);
    while (quantidadeInicialIndividuos < 1 || quantidadeInicialIndividuos > quantidadeMaximaIndividuos)
    {
        scanf("%zu", &quantidadeInicialIndividuos);
    }

    tabuleiro = alocarMatriz(tamanhoTabuleiro);
    tabuleiroAuxiliar = alocarMatriz(tamanhoTabuleiro);

    for (size_t i = 0; i < quantidadeInicialIndividuos; i++)
    {
        inserirIndividuo();
    }

    system("cls || clear");
    verTabuleiro();

    while (existeIndividuos())
    {
        copiarTabuleiro(tabuleiro, tabuleiroAuxiliar);
        jogo();
        if (semModificacaoTabuleiro())
        {
            break;
        }
        copiarTabuleiro(tabuleiroAuxiliar, tabuleiro);

        std::this_thread::sleep_for(std::chrono::milliseconds(TEMPO));
        system("cls || clear");
        verTabuleiro();
    }
}

bool **JogoVida::alocarMatriz(size_t tamanho)
{
    bool **matriz = (bool **)malloc(sizeof(bool *) * tamanho);

    for (size_t i = 0; i < tamanho; i++)
    {
        matriz[i] = (bool *)malloc(sizeof(bool) * tamanho);
    }

    return matriz;
}

void JogoVida::destruirMatriz()
{
    for (size_t i = 0; i < tamanhoTabuleiro; i++)
    {
        free(tabuleiro[i]);
    }

    free(tabuleiro);
}

void JogoVida::jogo()
{

    for (size_t i = 0; i < tamanhoTabuleiro; i++)
    {
        for (size_t j = 0; j < tamanhoTabuleiro; j++)
        {
            tabuleiroAuxiliar[i][j] = atualizaPosicao(i, j);
        }
    }
}

void JogoVida::zerarMatriz()
{
    for (size_t i = 0; i < tamanhoTabuleiro; i++)
    {
        for (size_t j = 0; j < tamanhoTabuleiro; j++)
        {
            tabuleiro[i][j] = false;
        }
    }
}

void JogoVida::inserirIndividuo()
{
    size_t x, y;

    printf("Diga a posicao do individuo(valor entre 0 e %zu): ", tamanhoTabuleiro - 1);
    scanf("%zu %zu", &x, &y);

    while (campoValido(x, y))
    {
        printf("Informe um valor valido(valor entre 0 e %zu): ", tamanhoTabuleiro - 1);
        scanf("%zu %zu", &x, &y);
    }

    tabuleiro[x][y] = true;
}

void JogoVida::verTabuleiro()
{
    printf("\n╔");
    for (size_t i = 0; i < tamanhoTabuleiro - 1; i++)
    {
        {
            printf("═══╦");
        }
    }
    printf("═══╗\n");

    for (size_t i = 0; i < (tamanhoTabuleiro - 1); ++i)
    {
        for (size_t j = 0; j < tamanhoTabuleiro; ++j)
        {
            if (tabuleiro[i][j])
            {
                printf("║ ■ ");
            }
            else
            {
                printf("║   ");
            }
        }
        printf("║\n╠");

        for (size_t a = 0; a < tamanhoTabuleiro - 1; a++)
        {
            printf("═══╬");
        }
        printf("═══╣\n");
    }

    for (size_t j = 0; j < tamanhoTabuleiro; ++j)
    {
        if (tabuleiro[tamanhoTabuleiro - 1][j])
        {
            printf("║ ■ ");
        }
        else
        {
            printf("║   ");
        }
    }

    printf("║\n╚");

    for (size_t i = 0; i < tamanhoTabuleiro - 1; i++)
    {
        printf("═══╩");
    }
    printf("═══╝\n");
}

bool JogoVida::atualizaPosicao(size_t x, size_t y)
{
    size_t vizinho = contarVizinhos(x, y);

    if (tabuleiro[x][y] == true)
    {
        if (vizinho < 2)
            return false;
        else if (vizinho > 3)
            return false;
        else
            return true;
    }
    else
    {
        if (vizinho == 3)
            return true;
        else
            return false;
    }
}

bool JogoVida::existeIndividuos()
{
    for (size_t i = 0; i < tamanhoTabuleiro; i++)
    {
        for (size_t j = 0; j < tamanhoTabuleiro; j++)
        {
            if (tabuleiro[i][j])
            {
                return true;
            }
        }
    }

    return false;
}

bool JogoVida::campoValido(size_t x, size_t y)
{
    if (x >= tamanhoTabuleiro)
    {
        return true;
    }

    if (y >= tamanhoTabuleiro)
    {
        return true;
    }

    return tabuleiro[x][y];
}

size_t JogoVida::contarVizinhos(size_t x, size_t y)
{
    size_t quantidadeVizinhos = 0;

    if (x > 0 && y > 0)
    {
        if (tabuleiro[x - 1][y - 1])
        {
            quantidadeVizinhos++;
        }
    }
    if (x > 0)
    {
        if (tabuleiro[x - 1][y])
        {
            quantidadeVizinhos++;
        }
    }
    if (x > 0 && y < tamanhoTabuleiro - 1)
    {
        if (tabuleiro[x - 1][y + 1])
        {
            quantidadeVizinhos++;
        }
    }
    if (y < tamanhoTabuleiro - 1)
    {
        if (tabuleiro[x][y + 1])
        {
            quantidadeVizinhos++;
        }
    }
    if (x < tamanhoTabuleiro - 1 && y < tamanhoTabuleiro - 1)
    {
        if (tabuleiro[x + 1][y + 1])
        {
            quantidadeVizinhos++;
        }
    }
    if (x < tamanhoTabuleiro - 1)
    {
        if (tabuleiro[x + 1][y])
        {
            quantidadeVizinhos++;
        }
    }
    if (x < tamanhoTabuleiro - 1 && y > 0)
    {
        if (tabuleiro[x + 1][y - 1])
        {
            quantidadeVizinhos++;
        }
    }
    if (y > 0)
    {
        if (tabuleiro[x][y - 1])
        {
            quantidadeVizinhos++;
        }
    }

    return quantidadeVizinhos;
}

void JogoVida::copiarTabuleiro(bool **original, bool **copia)
{
    for (size_t i = 0; i < tamanhoTabuleiro; i++)
    {
        for (size_t j = 0; j < tamanhoTabuleiro; j++)
        {
            copia[i][j] = original[i][j];
        }
    }
}

bool JogoVida::semModificacaoTabuleiro()
{
    for (size_t i = 0; i < tamanhoTabuleiro; i++)
    {
        for (size_t j = 0; j < tamanhoTabuleiro; j++)
        {
            if (tabuleiroAuxiliar[i][j] != tabuleiro[i][j])
            {
                return false;
            }
        }
    }
    return true;
}