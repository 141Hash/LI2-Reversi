#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "structs.h"
#include "estado.h"

/**
 * lê o ficheiro do jogo
 * @param nome é o nome do ficheiro
 * @param e é o estado do jogo
 * @param s é onde são armazenados os estados
 * gm é o modo de jogo
 * gp é a peça do jogador
 * line é onde está cada linha do ficheiro
 */
void ler(char *nome, ESTADO *e, STACK *s)
{
    char gm, gp;
    char line[100];
    int i, j, k;

    strcat(nome, ".txt");

    FILE *ficheiro;
    ficheiro = fopen(nome ,"r+");

    fscanf(ficheiro, "%c %c", &gm, &gp);

    if (toupper(gm) == 'M') e->modo = '0';
    else if (toupper(gm) == 'A') e->modo ='1';

    if (toupper(gp) == 'X') e->peca = VALOR_X;
    else if (toupper(gp) == 'O') e->peca = VALOR_O;

    for (i = 1; fgets(line, 100, ficheiro); i++)
    {
        k=0;

        for (j=0; line[j]; j++)
        {
            if (toupper(line[j])=='X')
            {
                e->grelha[i-2][k]=VALOR_X;
                k++;
            }

            else if (toupper(line[j])=='O')
            {
                e->grelha[i-2][k]=VALOR_O;
                k++;
            }

            else if (line[j]=='-')
            {
                e->grelha[i-2][k]=VAZIA;
                k++;
            }
        }
    }

    fclose(ficheiro);

    e->start = '1';

    s->sp = 0;
    s->valores[s->sp] = *e;

    printa(e);
}

/**
 * imprime o tabuleiro no ecrã o tabuleiro no ecrã e guarda o tabuleiro num ficheiro
 * @param nome é o nome do ficheiro
 * @param e é o estado do jogo
 */
void escrever(char *nome, ESTADO *e)
{
    int i, j;

    strcat(nome, ".txt");

    FILE *ficheiro;
    ficheiro = fopen(nome ,"w");

    if (e->modo == '0') fprintf(ficheiro, "%s", "M ");
    else if (e->modo == '1') fprintf(ficheiro, "%s", "A ");

    if (e->peca == VALOR_X) fprintf(ficheiro, "%s", "X\n");
    else if (e->peca == VALOR_O) fprintf(ficheiro, "%s", "O\n");

    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            if (j==7)
            {
                if (e->grelha[i][j]==VALOR_O) fprintf(ficheiro, "%s", "O\n");

                else if (e->grelha[i][j]==VALOR_X) fprintf(ficheiro, "%s", "X\n");

                else if (e->grelha[i][j]==VAZIA) fprintf(ficheiro, "%s", "-\n");
            }

            else
            {
                if (e->grelha[i][j]==VALOR_O) fprintf(ficheiro, "%s", "O ");

                else if (e->grelha[i][j]==VALOR_X) fprintf(ficheiro, "%s", "X ");

                else if (e->grelha[i][j]==VAZIA) fprintf(ficheiro, "%s", "- ");

            }
        }
    }

    fclose(ficheiro);

    printa(e);
}