#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include "tabuleiro.h"

/*
Quadrado Preto  -> ◻    - 0
Quadrado Branco -> ◼    - 1
Peão            -> ♙ ♟ - 2 8
Cavalo          -> ♘ ♞ - 3 9
Bispo           -> ♗ ♝ - 4 10 
Torre           -> ♖ ♜ - 5 11
Rainha          -> ♕ ♛ - 6 12
Rei             -> ♔ ♚ - 7 13
*/

int main()
{
    SetConsoleOutputCP(65001);
    bool validar = true;
    int rodada = 0;
    int *tab; 
    
    //Fazer as jogadas em loop até ter algum resultado
    while(validar)
    {
        //Se for a primeira rodada (== 0), ele vai iniciar um novo tabuleiro 
        if(rodada == 0)
        {    
            tab = criartabuleiro(); 
        }

        imprimirtabuleiro(tab);
        printf("\n");
        printf("Vez do jogador %d fazer seu movimento:\n", (rodada%2)+1);
        movimento(tab);
        printf("\n\n");
        rodada++;
    }
    
    return 0;
}

//cd "c:\Users\USUÁRIO\Documents\Projetos\Xadrez em Linguagem C\xadrez"
//gcc -g main.c tabuleiro.c -o output\main.exe