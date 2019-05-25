#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "estado.h"
#include "game.h"

/**
 * começa o jogo com um novo bot
 * @param e é o estado do jogo
 * @param s é onde estão armazenados os estados
 * @param niv é o nível do bot
 * @param val é qual é a peça
 */
void novobot(ESTADO *e, STACK *s, char niv, VALOR val)
{
    int i, j;

    for(i = 0; i <= 8; i++)
    {
        for(j = 0; j <= 8; j++)
        {
            e -> grelha[i][j] = VAZIA;
        }
    }

    e->grelha[3][4] = VALOR_X;
    e->grelha[4][3] = VALOR_X;
    e->grelha[3][3] = VALOR_O;
    e->grelha[4][4] = VALOR_O;

    e->modo = '1';
    e->nivel = niv;
    e->pecabot = val;
    e->start = '1';

    if(val==VALOR_X) e->peca=VALOR_O;
    else e->peca=VALOR_X;

    s->sp = 0;
    s->valores[s->sp] = *e;

    printa(e);
}

// FACIL
/**
 * gera uma posiçao aleatória
 * @param e é o estado do jogo
 * @param x é um número aleatório
 * @return
 */
PONTO randomposicao(ESTADO *e, int x)
{
    int i, j;
    PONTO p;

    for(i=0; i<8 && x!=0; i++)
    {
        for(j=0; j<8 && x!=0; j++)
        {
            if (jogada_valida(i, j, e))
            {
                p.mp = i;
                p.np = j;
                return p;
            }
        }
    }
}

/**
 * é o primeiro nível do bot. O bot joga numa posição aleatória
 * @param e é o estado do jogo
 * @param s é onde são armazenados os estados do jogo
 * x é o número de jogadas válidas
 * r recebe um número aleatório
 * p recebe uma posição aleatória
 */
void easy (ESTADO *e, STACK *s)
{
    int x, r;
    PONTO p;

    x = contavalidas(e);

    r = rand() % x;

    p = randomposicao(e, r);

    printf("\nO bot jogou em %d %d \n", (p.mp + 1), (p.np + 1));

    jogada(p.mp, p.np, e, s);
}

// MEDIUM

/**
 * segundo nível do bot. O bot joga na segunda posição que altera mais peças
 * @param e é o estado do jogo
 * @param s é onde são armazenados os estados do jogo
 * aux estado usado para comparar com o estado original
 * comp é o número de paças que altera na jogada
 * max é a jogada que altera mais peças
 * max2 é a segunda jogada que altera mais peças
 */
void medium (ESTADO *e, STACK *s)
{
    int i, j;
    int l = 0;
    int c = 0;
    ESTADO aux;
    int comp = 0;
    int max = 0;
    int max2 = 0;
    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 8; j++)
        {
            aux = *e;

            if(jogada_valida(i, j, e))
            {
                jogadabot(i, j, &aux);
                comp = (contap(&aux) - contap(e));
            }

            if(comp > max && comp > max2)
            {
                max = comp;
                max2 = max;
                l = i;
                c = j;
            }

            else if(comp > max2 && comp < max)
            {
                max2 = comp;
                l = i;
                c = j;
            }
        }

    }

    jogada(l, c, e, s);

    printf("O bot jogou em %d %d\n", (l+1), (c+1));

}

// HARDCORE

/**
 * é o terceiro nível do bot. O bot joga na posição que altera mais peças
 * @param e é o estado do jogo
 * @param s é onde estão armazenados os estados
 * aux estado usado para comparar com o estado original
 * comp é o número de paças que altera na jogada
 * max é a jogada que altera mais peças
 */
void hardcore (ESTADO *e, STACK *s)
{
    int i, j;
    int l = 0;
    int c = 0;
    ESTADO aux;
    int comp = 0;
    int max = 0;
    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 8; j++)
        {
            aux = *e;

            if(jogada_valida(i, j, e))
            {
                jogadabot(i, j, &aux);
                comp = (contap(&aux) - contap(e));
            }

            if(comp > max)
            {
                max = comp;
                l = i;
                c = j;
            }
        }
    }
    jogada(l, c, e, s);

    printf("O bot jogou em %d %d\n", (l+1), (c+1));
}

