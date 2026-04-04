#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "tabuleiro.h"
#include <stdbool.h>

/*
Quadrado Preto  -> ◻    - 0
Quadrado Branco -> ◼    - 1
Peão            -> ♙ ♟ - 2 3
Cavalo          -> ♘ ♞ - 4 5
Bispo           -> ♗ ♝ - 6 7 
Torre           -> ♖ ♜ - 8 9
Rainha          -> ♕ ♛ - 10 11
Rei             -> ♔ ♚ - 12 13
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
        printf("DEBUG: início do loop, rodada %d\n", rodada);
        if(rodada == 0)
        {    
            tab = criartabuleiro(); 
        }

        imprimirtabuleiro(tab);
        printf("\n\n");
        printf("Vez do jogador %d fazer seu movimento:\n", (rodada%2)+1);
        movimento(tab);
        printf("DEBUG: movimento concluído, rodada %d\n", rodada);
        printf("\n\n");
        rodada++;
    }
    
    return 0;
}

//cd "c:\Users\USUÁRIO\Documents\Projetos\Xadrez em Linguagem C\xadrez"
//gcc -g main.c tabuleiro.c -o output\main.exe