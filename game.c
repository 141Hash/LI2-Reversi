#include <stdio.h>
#include "structs.h"
#include "estado.h"

/**
 * verifica se uma jogada é válida
 * @param m é o número de linhas da grelha
 * @param n é o número de colunas da grelha
 * @param e é o estado do jogo
 * res é a variável utilizada para atribuir o valor de verdade à função
 * l e c linha e coluna da posição usada para comparar com m e n
 * cont fica com a peça contrária à da posição
 * @return
 */
int jogada_valida (int m, int n, ESTADO *e)
{
    int l , c, res=0;
    VALOR cont;

    if (e->grelha[m][n]==VAZIA)
    {
        if (e->peca==VALOR_X) cont=VALOR_O;
        else cont=VALOR_X;

        // Direita
        if (e->grelha[m][n+1]==cont && res==0)
        {
            for (l=m, c=n; e->grelha[l][c + 1]==cont && c<8; c++);

            if (e->grelha[l][c+1]==e->peca && c<8) res=1;
        }

        // Esquerda
        if (e->grelha[m][n-1]==cont && res==0)
        {
            for (l=m, c=n; e->grelha[l][c - 1]==cont && c>0; c--);

            if (e->grelha[l][c-1]==e->peca && c>0) res=1;
        }

        // Cima
        if (e->grelha[m-1][n]==cont && res == 0)
        {
            for (l=m, c=n; e->grelha[l-1][c]==cont && l>0; l--);

            if (e->grelha[l-1][c]==e->peca && l>0) res=1;
        }

        // Baixo
        if (e->grelha[m+1][n]==cont && res==0)
        {
            for (l=m, c=n; e->grelha[l+1][c]==cont && l<8; l++);

            if (e->grelha[l+1][c]==e->peca && l<8) res=1;
        }

        // Direita Cima
        if (e->grelha[m-1][n+1]==cont && res==0)
        {
            for (l=m, c=n; e->grelha[l-1][c+1]==cont && l>0 && c<8; l--, c++);

            if (e->grelha[l-1][c+1]==e->peca && l>0 && c<8) res=1;
        }

        // Esquerda Cima
        if (e->grelha[m-1][n-1]==cont && res==0)
        {
            for (l=m, c=n; e->grelha[l-1][c-1]==cont && l>0 && c>0; l--, c--);

            if (e->grelha[l-1][c-1]==e->peca && l>0 && c>0) res=1;
        }

        // Direita Baixo
        if (e->grelha[m+1][n+1]==cont && res==0)
        {
            for (l=m, c=n; e->grelha[l+1][c+1]==cont && l<8 && c<8; l++, c++);

            if (e->grelha[l+1][c+1]==e->peca && l<8 && c<8) res=1;
        }

        // Esquerda Baixo
        if (e->grelha[m+1][n-1]==cont && res==0)
        {
            for (l=m, c=n; e->grelha[l+1][c-1]==cont && l<8 && c>0; l++, c--);

            if (e->grelha[l+1][c-1]==e->peca && l<8 && c>0) res=1;
        }
    }
    return res;
}

/**
 * função utilizada para alterar as peças quando uma jogada for efetuada
 * @param m é o número de linhas da grelha
 * @param n é o número de colunas da grelha
 * @param e é o estado do jogo
 * cont é a variável utilizada para trocar as peças
 * l e c são usadas para comparar com a posição na grelha
 */
void alterar_peca(int m, int n, ESTADO *e)
{
    int l , c;
    VALOR cont;

    if (e->peca == VALOR_X) cont = VALOR_O;
    else cont = VALOR_X;

    // Direita
    for (l=m, c=n; e->grelha[l][c + 1]==cont && c<8; c++);

    if (e->grelha[l][c+1]==e->peca && c!=8)
    {
        for (; c!=n; c--) e->grelha[l][c]=e->peca;
    }

    // Esquerda
    for (l=m, c=n; e->grelha[l][c - 1]==cont && c>0; c--);

    if (e->grelha[l][c-1]==e->peca && c!=0)
    {
        for (;c!=n;c++) e->grelha[l][c] = e->peca;
    }

    // Cima
    for (l=m, c=n; e->grelha[l-1][c]==cont && l>0; l--);

    if (e->grelha[l-1][c]==e->peca && l!=0)
    {
        for (; l!=m; l++) e->grelha[l][c]=e->peca;
    }

    // Baixo
    for (l=m, c=n; e->grelha[l+1][c]==cont && l<8; l++);

    if (e->grelha[l+1][c]==e->peca && l!=8)
    {
        for (; l!=m; l--) e->grelha[l][c]=e->peca;
    }

    // Direita Cima
    for (l=m, c=n; e->grelha[l-1][c+1]==cont && l>0 && c<8; l--, c++);

    if (e->grelha[l-1][c+1]==e->peca && l!=0 && c!=8)
    {
        for (; l!=m; l++,c--) e->grelha[l][c] = e->peca;
    }

    // Esquerda Cima
    for (l=m, c=n; e->grelha[l-1][c-1]==cont && l>0 && c>0; l--, c--);

    if (e->grelha[l-1][c-1]==e->peca && l!=0 && c!=0)
    {
        for (;l!=m ;l++,c++) e->grelha[l][c] = e->peca;
    }

    // Direita Baixo
    for (l=m, c=n; e->grelha[l+1][c+1]==cont && l<8 && c<8; l++, c++);

    if (e->grelha[l+1][c+1]==e->peca && l!=8 && c!=8)
    {
        for (; l!=m ; l--,c--) e->grelha[l][c] = e->peca;
    }

    // Esquerda Baixo
    for (l=m, c=n; e->grelha[l+1][c-1]==cont && l<8 && c>0; l++, c--);

    if (e->grelha[l+1][c-1]==e->peca && l!=8 && c!=0)
    {
        for (;l!=m ;c++,l--) e->grelha[l][c] = e->peca;
    }

}

/**
 * esta função chama a função altera_pecas, coloca o novo estado na stack, muda o jogador e imprime o tabuleiro no ecrã
 * @param m é o número de linhas da grelha
 * @param n é o número de colunas da grelha
 * @param e é o estado do jogo
 * @param s é onde são guardados os estados
 */
void jogada(int m, int n, ESTADO *e, STACK *s)
{
    e->grelha[m][n]=e->peca;

    alterar_peca(m, n, e);

    if (e->peca == VALOR_O) e->peca = VALOR_X;
    else e->peca = VALOR_O;

    s->sp ++;
    s->valores[s->sp] = *e;

    printa(e);
}