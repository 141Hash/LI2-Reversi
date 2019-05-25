#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "structs.h"
#include "estado.h"
#include "game.h"
#include "files.h"
#include "bot.h"
/**
 * esta função faz executar a opção escolhida pelo jogador, direcionando para funções secundárias
 * @param linha onde está guardado o comando escolhido pelo jogador
 * @param e estado do jogo
 * @param s contém os estados do jogo
 * fst e snd contêm o conteúdo dos comandos que tenham mais que uma letra, ficando, respetivamente, o fst com a primeira e o snd com a segunda
 */
void executa_opcao(char linha[], ESTADO *e, STACK *s)
{
    char fst[100], snd[100];
    char x, y;

    switch (toupper(linha[0]))
    {
        case 'N':
            if (toupper(linha[2]) == 'X') game_start(e, s, 'X');
            else if (toupper(linha[2]) == 'O') game_start(e, s, 'O');
            else printf("Comando Inválido\n");
            break;

        case 'L':
            sscanf(linha, "%s %s", fst, snd);
            ler(snd, e, s);
            break;

        case 'E':
            sscanf(linha, "%s %s", fst, snd);
            escrever(snd, e);
            break;

        case 'J':
            x=linha[2], y=linha[4];
            if (isdigit(x) && isdigit(y) && jogada_valida(x-49, y-49, e)) {jogada(x-49, y-49, e, s);}
            else printf("Jogada Inválida\n");
            break;

        case 'S':
            valida(e);
            break;

        case 'H':
            sugestao(e);
            break;

        case 'U':
            undo(e, s);
            break;

        case 'A':
            x=linha[2], y=linha[4];
            if (y>='1' && y<='3' && (toupper(x) == 'X' || toupper(x) == 'O'))
            {
                if (toupper(x) == 'X') novobot(e, s, y, VALOR_X);
                else novobot(e, s, y, VALOR_O);
            }
            else printf("Comando Inválido\n");
            break;

        case 'Q':
            printf("A sair do jogo\n");
            break;

        default:
            printf("Comando inválido\n");
            break;
    }

    remsugestao(e); // Remove '*' e '?'

    if(e->modo=='1' && e->nivel=='1' && e->peca==e->pecabot) easy(e, s); // Verifica se é a vez do bot jogar e a dificuldade
    else if(e->modo=='1' && e->nivel=='2' && e->peca==e->pecabot) medium(e,s);
    else if(e->modo=='1' && e->nivel=='3' && e->peca==e->pecabot) hardcore(e, s);

    if (contavalidas(e)==0 && e->modo=='0') // Se um jogador nao tiver jogadas alterna a vez
    {
        if (e->peca==VALOR_X) e->peca = VALOR_O;
        else e->peca = VALOR_X;
    }

    if ((contapecas(e)==64 || contavalidas(e)==0) && e->start=='1') // Verifica se existe condição para acabar o jogo
    {
        if (ganhou(e)==1) printf("\nO Jogador X ganhou\n");
        else if (ganhou(e)==(-1)) printf("\nO Jogador O ganhou\n");
        else if (ganhou(e)==0) printf("\nEmpate\n");
        linha[0] = 'Q';
    }
}

/**
 * mostra o menu
 */
void menu()
{
    printf("\nSelecione a sua opção:\n");
    printf("N | Novo Jogo\n");
    printf("L | Ler Jogo\n");
    printf("E | Guardar Jogo\n");
    printf("J | Jogar Peça\n");
    printf("S | Jogadas Válidas\n");
    printf("H | Sugestão de Jogada\n");
    printf("U | Reverter Jogada\n");
    printf("A | Novo Jogo Contra BOT\n");
    printf("Q | Sair do jogo\n");
}

/**
 * chama a função menu
 * recebe uma string (opção)
 * chama a função executa_opcao
 * @return
 */
int main()
{
    char linha[100];
    ESTADO e;
    STACK s;

    e.start = '0';

    printf("\n>>>>>>>>REVERSI<<<<<<<<\n");

    while(toupper(linha[0])!='Q')
    {
        menu ();
        fgets(linha, 100, stdin);
        executa_opcao(linha, &e, &s);
    }
    return 0;
}