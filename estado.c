#include <stdio.h>
#include "structs.h"
#include "game.h"

/**
 * imprime o estado
 * @param e é o estado do jogo
 * contaX e contaO conta o número de peças do estado
 * c é a variável utilizada para imprimir as peças
 */
void printa(ESTADO *e)
{
    int contaX = 0;
    int contaO = 0;
    char c = ' ';

    if (e->peca == VALOR_X) printf("\n     Jogador X\n");
    else printf("\n     Jogador O\n");

    printf("  1 2 3 4 5 6 7 8\n");

    for (int i = 0; i < 8; i++)
    {
        printf ("%d ", i+1);

        for (int j = 0; j < 8; j++)
        {
            switch (e->grelha[i][j])
            {
                case VALOR_O:
                {
                    c = 'O';
                    break;
                }

                case VALOR_X:
                {
                    c = 'X';
                    break;
                }

                case VAZIA:
                {
                    c = '-';
                    break;
                }

                case VALIDA:
                {
                    c = '*';
                    break;
                }

                case SUGESTAO:
                {
                    c = '?';
                    break;
                }
            }
            printf("%c ", c);

        }
        printf("\n");

    }

    for(int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8 ; j++)
        {
            if (e->grelha[i][j] == VALOR_X) contaX++;

            else if (e->grelha[i][j] == VALOR_O) contaO++;
        }
    }

    printf("Jogador X: %d \n", contaX);
    printf("Jogador O: %d \n", contaO);
}

/**
 * cria a grelha inicial do jogo
 * @param e é o estado do jogo
 * @param s é onde estão guardados os estados
 * @param c é a peça que está a jogar
 */
void game_start(ESTADO *e, STACK *s, char c)
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

    e->modo = '0';
    e->nivel = '1';
    e->start = '1';

    if (c == 'X') e->peca = VALOR_X;
    else e->peca = VALOR_O;

    s->sp = 0;
    s->valores[s->sp] = *e;

    printa(e);
}

/**
 * reverte as jogadas até ao estado inicial
 * @param e é o estado do jogo
 * @param s é onde estão armazenados os estados
 */
void undo(ESTADO *e, STACK *s)
{
    if (s->sp != 0)
    {
        s->sp --;
        *e = s->valores[s->sp];
    }
    printa(e);
}

/**
 * se a posiçao for válida coloca lá um asterico
 * @param e é o estado do jogo
 */
void valida(ESTADO *e)
{
    int i, j;

    for(i=0; i<=8; i++)
    {
        for(j=0; j<=8; j++)
        {
            if (jogada_valida(i, j, e)) e->grelha[i][j]=VALIDA;
        }
    }
    printa(e);
}

/**
 * esta função chama a função altera_pecas, muda o jogador e imprime o tabuleiro no ecrã
 * @param m é o número de linhas da grelha
 * @param n é o número de colunas da grelha
 * @param e é o estado do jogo
 */
void jogadabot(int m, int n, ESTADO *e)
{
    e->grelha[m][n]=e->peca;

    alterar_peca(m, n, e);

    if (e->peca == VALOR_O) e->peca = VALOR_X;
    else e->peca = VALOR_O;
}

/**
 * conta as peças que foram mudadas
 * @param e é o estado do jogo
 * @return
 * count é utilizado para contar as peças mudadas
 */
int contap (ESTADO *e)
{
    int i, j;
    int count = 0;
    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 8; j++)
        {
            if(e->grelha[i][j] == e->peca) count++;
        }
    }
    return count;
}

/**
 * sugere uma jogada
 * @param e é o estado do jogo
 */
void sugestao(ESTADO *e)
{
    int i, j, flag=0;

    for(i=0; i<=8 && flag==0; i++)
    {
        for(j=0; j<=8 && flag==0; j++)
        {
            if (jogada_valida(i, j, e))
            {
                flag = 1;
                e->grelha[i][j]=SUGESTAO;
            }
        }
    }
    printa(e);
}

/**
 * remove as sugestões e as jogadas válidas do estado
 * @param e é estado do jogo
 */
void remsugestao(ESTADO *e)
{
    int i, j;

    for(i=0; i<=8; i++)
    {
        for(j=0; j<=8; j++)
        {
            if (e->grelha[i][j]==SUGESTAO) e->grelha[i][j]=VAZIA;

            if (e->grelha[i][j]==VALIDA) e->grelha[i][j]=VAZIA;
        }
    }
}

/**
 * conta as jogadas válidas
 * @param e é o estado do jogo
 * @return
 * k é o número de jogadas válidas
 */
int contavalidas(ESTADO *e)
{
    int i, j, k=0;

    for(i= 0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            if (jogada_valida(i, j, e)) k++;
        }
    }
    return k;
}

/**
 * conta o número de peças
 * @param e é o estado do jogo
 * @return
 * k é o número de peças
 */
int contapecas(ESTADO *e)
{
    int i, j, k=0;

    for(i=0; i<=8; i++)
    {
        for(j=0; j<=8; j++)
        {
            if (e->grelha[i][j]==VALOR_X || e->grelha[i][j]==VALOR_O) k++;
        }
    }

    return k;
}

/**
 * verifica se o jogo acabou
 * @param e é o estado do jogo
 * @return
 * x é o número de peças X
 * o é o número de peças O
 */
int ganhou(ESTADO *e)
{
    int i, j, x=0, o=0;

    for(i=0; i<=8; i++)
    {
        for(j=0; j<=8; j++)
        {
            if (e->grelha[i][j]==VALOR_X) x++;

            else if (e->grelha[i][j]==VALOR_O) o++;
        }
    }

    if (x>o) return 1;
    else if (x<o) return -1;
    else if (x==o) return 0;
}