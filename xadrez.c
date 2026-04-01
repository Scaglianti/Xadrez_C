#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

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

enum bool
{
    false,
    true
};
enum pecas
{
    //Enumerar as peças
    quadradoB,
    quadradoP,
    peaoB,
    cavaloB,
    bispoB,
    torreB,
    rainhaB,
    reiB,
    peaoP,
    cavaloP,
    bispoP,
    torreP,
    rainhaP,
    reiP
};
int cores(int col,int lin)
{
    //Função criada para identificar cada cor do tabuleiro (Preto e Branco) e repor (caso necessário) após o movimento
    int *cores=malloc(sizeof(int)*64);
    int cor;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            cores[i*8+j] = (i+j) % 2;
        }
    }
    cor=cores[lin*8+col];
    free(cores);
    return cor;
}
void imprimirtabuleiro(int *pecas)
{
    //Ler o tabuleiro e substituir pelo caractere correspondente
    for(int i=0;i<8;i++)
    {
        printf("%d ", 8-i);
        for(int j=0;j<8;j++)
        {
            switch(pecas[i*8+j])
            {
                case quadradoB:
                printf("◻ ");
                break;
                case quadradoP:
                printf("◼ ");
                break;
                case peaoB:
                printf("♙ ");
                break;
                case peaoP:
                printf("♟ ");
                break;
                case cavaloB:
                printf("♘ ");
                break;
                case cavaloP:
                printf("♞ ");
                break;
                case bispoB:
                printf("♗ ");
                break;
                case bispoP:
                printf("♝ ");
                break;
                case torreB:
                printf("♖ ");
                break;
                case torreP:
                printf("♜ ");
                break;
                case rainhaB:
                printf("♕ ");
                break;
                case rainhaP:
                printf("♛ ");
                break;
                case reiB:
                printf("♔ ");
                break;
                case reiP:
                printf("♚ ");
                break;
                default:
                printf("? ");
            }
        }
        printf("\n");
    }
    printf("  a b c d e f g h \n");
}
int *criartabuleiro()
{
    //Criar o tabuleiro inicial
    int * pecas_numericas = malloc(sizeof(int)*64);
    
    //Colocar o tabuleiro puro em preto e branco
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            pecas_numericas[i*8+j] = (i+j) % 2;
        }
    }

    //Colocar as linhas de índice 1 e 6 somente com peões
    for(int i=0;i<8;i++)
    {
    
        pecas_numericas[1*8+i]=peaoP;
        pecas_numericas[6*8+i]=peaoB;
        
    }

    //Alocação manual do restante das peças
    pecas_numericas[0]     = pecas_numericas[7] = torreP; 
    pecas_numericas[2]     = pecas_numericas[5] = cavaloP;
    pecas_numericas[6]     = pecas_numericas[1] = bispoP;
    pecas_numericas[3]     = rainhaP;
    pecas_numericas[4]     = reiP;

    pecas_numericas[7*8]   = pecas_numericas[7*8+7] = torreB;
    pecas_numericas[7*8+1] = pecas_numericas[7*8+6] = cavaloB;
    pecas_numericas[7*8+2] = pecas_numericas[7*8+5] = bispoB;
    pecas_numericas[7*8+3] = rainhaB;
    pecas_numericas[7*8+4] = reiB;

    return pecas_numericas;
    free(pecas_numericas);
    
}
int vertical(int lin_ori, int col_ori, int lin_des, int col_des, int *tab)
{
    //Leitura das verticais para ver se há alguma peça impedindo de chegar ao destino
    int bool;

    //Leitura da vertical para baixo
    if(lin_ori<lin_des)
    {
        for(int i=lin_ori+1;i<lin_des+1;i++)
        {
            if(tab[i*8+col_ori]>1)
            {
                bool = false;
            }
            else
            bool = true;
        }
    }

    //Leitura da vertical para cima
    else
    {
        for(int i=lin_ori-1;i>lin_des+1;i--)
        {
            if(tab[i*8+col_ori]>1)
            {
                bool = false;
            }
            else
                bool = true;
        }
    }

    return bool;
}
int horizontal(int lin_ori, int col_ori, int lin_des, int col_des, int *tab)
{
    //Leitura das horizontais para ver se há alguma peça impedindo de chegar ao destino
    int bool;

    //Leitura da horizontal para direita
    if(col_ori<col_des)
    {
        for(int i=col_ori+1;i<col_des-1;i++)
        {
            if(tab[lin_ori*8+i]>1)
            {
                bool = false;
            }
            else
            bool = true;
        }
    }

    //Leitura da horizontal para esquerda
    else
    {
        for(int i=col_ori-1;i>col_des+1;i--)
        {
            if(tab[lin_ori*8+i]>1)
            {
                bool = false;
            }
            else
                bool = true;
        }
    }

    return bool;
}
int diagonal(int lin_ori, int col_ori, int lin_des, int col_des, int *tab)
{
    //Ler as diagonais para ver se até o destino não há alguma peça impedindo a passagem
    int bool;

    //ler as diagonais para baixo
    if(lin_ori < lin_des)
    {
        for(int i=lin_ori+1;i<lin_des;i++)
        {
            //ler as diagonais da direita
            if(col_ori < col_des)
            {
                for(int j=col_ori;j<col_des;j++)
                {
                    if(tab[i*8+(j+1)]>1)
                    {
                        bool = false;
                    }
                    else
                    bool = true;
                }
            }

            //ler as diagonais da esquerda
            else
            {
                for(int j=col_ori;j<col_des;j--)
                {
                    if(tab[i*8+(j-1)]>1)
                    {
                        bool = false;
                    }
                    else
                    bool = true;
                }
            }
        }
    }

    //Ler as diagonais para cima
    else
    {
        for(int i=lin_ori-1;i<lin_des;i++)
        {
            //Ler as diagonais da direita
            if(col_ori < col_des)
            {
                for(int j=col_ori;j<col_des;j++)
                {
                    if(tab[i*8+(j+1)]>1)
                    {
                        bool = false;
                    }
                    else
                    bool = true;
                }
            }

            //Ler as diagonais da esquerda
            else
            {
                for(int j=col_ori;j<col_des;j--)
                {
                    if(tab[i*8+(j-1)]>1)
                    {
                        bool = false;
                    }
                    else
                    bool = true;
                }
            }
        }
        
    }

    return bool;
}
void lermovimento(int *val_col,int *val_lin)
{
    //Ler a notação escrita e transformar na posição correspondente no tabuleiro
    int bool = true;
    char notacao[3];

    while(bool)
    {
    scanf(" %c%c",&notacao[0],&notacao[1]);
    if(notacao[0] < 'a' || notacao[0] > 'h' || notacao[1] < '1' || notacao[1] > '8')
    {
        printf("Erro!! Posição invalida, tente novamente.\n");
    }
    else
    {
    *val_col = notacao[0]-'a';
    *val_lin = '8' - notacao[1];
    bool = false;
    }
    };
}
int sistema(int peca, int col_ori, int lin_ori, int lin_des, int col_des, int *tabuleiro)
{
    int bool=true;

    switch(peca)
    {
        case peaoP:
        
        break;
        case peaoB:
        if(lin_des == (lin_ori-1) && (col_des == col_ori-1 || col_des == col_ori+1) && tabuleiro[lin_des*8+col_des]>=8)
        {
            bool = true;
        }
        else if(lin_ori == 6)
        {
            if((lin_des == 5 || lin_des == 4) && col_ori == col_des)
            {
                bool = true;
            }
            else
                bool = false;
        }
        else if(lin_des == lin_ori - 1)
            {
                bool = true;
            }
            else
                bool = false;
        
            
        
        break;
        case cavaloB:

        break;
        case cavaloP:

        break;
        case bispoB:

        break;
        case bispoP:

        break;
        case torreB:

        break;
        case torreP:

        break;
        case rainhaB:

        break;
        case rainhaP:

        break;
        case reiB:

        break;
        case reiP:

        break;
    }
    return bool;
}
void movimento(int *tab)
{
    //Realizar o movimento proposto pelo jogador
    int lin_ori,col_ori,lin_des,col_des;
    int cor, bool=true;
    
    while(bool)
    {
        printf("Informe a casa que você quer andar: ");
        lermovimento(&col_ori,&lin_ori);
        int peca = tab[lin_ori*8 + col_ori];
        
        
        if(peca == quadradoB || peca == quadradoP)
        {
            printf("Você não pode movimentar uma casa vazia! Tente novamente.\n");
        }
        else
        bool = false;
    }

    bool=true;
    while(bool)
    {
        printf("Informe a casa para onde você quer andar: ");
        lermovimento(&col_des,&lin_des);
        int peca = tab[lin_ori*8 + col_ori];
        
        if(!sistema(peca, col_ori, lin_ori, lin_des, col_des, tab))
        {
            printf("Ação inválida!! Tente novamente.\n");
        }
        else
        
        bool = false;
    }
    
    cor = cores(col_ori,lin_ori);
    tab[lin_des*8+col_des] = tab[lin_ori*8+col_ori];
    tab[lin_ori*8+col_ori] = cor;

    imprimirtabuleiro(tab);
}
 
int main()
{
    SetConsoleOutputCP(65001);
    int bool = true;
    int rodada = 0;
    int *tab; 
    
    //Fazer as jogadas em loop até ter algum resultado
    while(bool)
    {
        //Se for a primeira rodada (== 0), ele vai iniciar um novo tabuleiro 
        if(rodada == 0)
        {    
            tab = criartabuleiro(); 
        }

        imprimirtabuleiro(tab);
        printf("\n\n");
        printf("Vez do jogador %d fazer seu movimento:\n", (rodada%2)+1);
        movimento(tab);
        printf("\n\n");
        rodada++;
    }
    
    return 0;
}