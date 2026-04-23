#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tabuleiro.h"

const char* nomes[] =
{
    "",
    "",
    "o Peão Branco",
    "o Cavalo Branco",
    "o Bispo Branco",
    "a Torre Branca",
    "a Rainha Branca",
    "o Rei Branco",
    "o Peão Preto",
    "o Cavalo Preto",
    "o Bispo Preto",
    "a Torre Preta",
    "a Rainha Preta",
    "o Rei Preto"
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
}

int verificadirecao(int lin_ori, int col_ori, int lin_des, int col_des)
{
    if(lin_ori == lin_des)
    {
        if(col_ori < col_des)
        {
            return true;
        }
        else if(col_ori > col_des)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if(col_ori == col_des)
    {
        if(lin_ori < lin_des)
        {
            return true;
        }
        else if(lin_ori > lin_des)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}
int verificadiagonal(int lin_ori, int col_ori, int lin_des, int col_des)
{
    //Movimento para baixo e esquerda
    if(lin_ori < lin_des && col_ori < col_des)
    {
        for(int i = lin_des, j = col_des;i>=lin_ori && j>=col_ori;i--,j--)
        {
            if(i == lin_ori && j == col_ori)
            {
                return true;
            }
        }
    }
    //Movimento para baixo e direita
    else if(lin_ori < lin_des && col_ori > col_des)
    {
        for(int i = lin_des, j = col_des;i>=lin_ori && j<=col_ori;i--,j++)
        {
            if(i == lin_ori && j == col_ori)
            {
                return true;
            }
        }
    }   
    //Movimento para cima e direita
    else if(lin_ori > lin_des && col_ori < col_des)
    {
        for(int i = lin_des, j = col_des;i<=lin_ori && j>=col_ori;i++,j--)
        {
            if(i == lin_ori && j == col_ori)
            {
                return true;
            }
        }
    }
    //Movimento para cima e esquerda
    else if(lin_ori > lin_des && col_ori > col_des)
    {
        for(int i = lin_des, j = col_des;i<=lin_ori && j<=col_ori;i++,j++)
        {
            if(i == lin_ori && j == col_ori)
            {
                return true;
            }
        }
    }
    else
    {
        return false;
    }
    return false; 
}

int* peca_horizontal(int lin, int col, int *tab, int rei)
{
    int* pecas = malloc(sizeof(int) * 2);

    //Leitura das horizontais para ver se há alguma peça impedindo de chegar ao destino
       
    //Leitura da horizontal para direita ⮕
    for(int i=col+1;i<8;i++)
    {
        if(tab[lin*8+i]>1 && tab[lin*8+i] != rei)
        {
            pecas[0] = tab[lin*8+i];
            break;
        }
        else
        pecas[0] = false;
    }

    //Leitura da horizontal para esquerda ⬅
    for(int i=col-1;i>=0;i--)
    {
        if(tab[lin*8+i]>1 && tab[lin*8+i] != rei)
        {
            pecas[1] = tab[lin*8+i];
            break;
        }
        else
        pecas[1] = false;
    }

    return pecas;
}
int* peca_diagonal(int lin, int col, int *tab, int rei)
{
    int* pecas = malloc(sizeof(int) * 4);
    
    //Ler as diagonais para ver se até o destino não há alguma peça impedindo a passagem
    
    //Movimento para baixo e esquerda ⬋
    for(int i = lin-1, j = col+1;i>=0 && j<8;i--,j++)
    {
        if(tab[i*8+j]>1 && tab[i*8+j] != rei)
        {
            pecas[0] = tab[i*8+j];
        }
        else
        {
            pecas[0] = false;
        }
    }
    
    //Movimento para baixo e direita ⬊
    for(int i = lin-1, j = col-1;i>=0 && j>=0;i--,j--)
    {
        if(tab[i*8+j]>1 && tab[i*8+j] != rei)
        {
            pecas[1] = tab[i*8+j];
        }
        else
        {
            pecas[1] = false;
        }
    }

    //Movimento para cima e direita ⬈
    for(int i = lin+1, j = col-1;i<8 && j>=0;i++,j--)
    {
        if(tab[i*8+j]>1 && tab[i*8+j] != rei)
        {
            pecas[2] = tab[i*8+j];
        }
        else
        {
            pecas[2] = false;
        }
    }

    //Movimento para cima e esquerda ⬉
    for(int i = lin+1, j = col+1;i<8 && j<8;i++,j++)
    {
        if(tab[i*8+j]>1 && tab[i*8+j] != rei)
        {
            pecas[3] = tab[i*8+j];
        }
        else
        {
            pecas[3] = false;
        }
    }

    return pecas;
}
int* peca_vertical(int lin, int col, int *tab, int rei)
{
    int* pecas = malloc(sizeof(int) * 2);

    //Leitura das verticais para ver se há alguma peça impedindo de chegar ao destino

    //Leitura da vertical para baixo ⬇
    for(int i=lin+1;i<8;i++)
    {
        if(tab[i*8+col]>1 && tab[i*8+col] != rei)
        {
            pecas[0] = tab[i*8+col];
        }
        else
        pecas[0] = false;
    }
    
    //Leitura da vertical para cima ⬆
    for(int i=lin-1;i>=0;i--)
    {
        if(tab[i*8+col]>1 && tab[i*8+col] != rei)
        {
            pecas[1] = tab[i*8+col];
        }
        else
            pecas[1] = false;
    }

    return pecas;
}
int* peca_cavalo(int lin, int col, int* tab)
{
    int* pecas = malloc(sizeof(int) * 8);

    //Movimento para baixo e esquerda
    if(tab[(lin-1)*8+(col+2)] == 3 || tab[(lin-1)*8+(col+2)] == 9)
    {
        pecas[0] = tab[(lin-1)*8+(col+2)];
    }
    //Movimento para baixo e direita
    else if(tab[(lin-1)*8+(col-2)] == 3 || tab[(lin-1)*8+(col-2)] == 9)
    {
        pecas[1] = tab[(lin-1)*8+(col-2)];
    }
    //Movimento para cima e esquerda
    else if(tab[(lin+1)*8+(col+2)] == 3 || tab[(lin+1)*8+(col+2)] == 9)
    {
        pecas[2] = tab[(lin+1)*8+(col+2)];
    }
    //Movimento para cima e direita
    else if(tab[(lin+1)*8+(col-2)] == 3 || tab[(lin+1)*8+(col-2)] == 9)
    {
        pecas[3] = tab[(lin+1)*8+(col-2)];
    }
    //Movimento para baixo e esquerda
    else if(tab[(lin-2)*8+(col+1)] == 3 || tab[(lin-2)*8+(col+1)] == 9)
    {
        pecas[4] = tab[(lin-2)*8+(col+1)];
    }
    //Movimento para baixo e direita
    else if(tab[(lin-2)*8+(col-1)] == 3 || tab[(lin-2)*8+(col-1)] == 9)
    {
        pecas[5] = tab[(lin-2)*8+(col-1)];
    }
    //Movimento para cima e esquerda
    else if(tab[(lin+2)*8+(col+1)] == 3 || tab[(lin+2)*8+(col+1)] == 9)
    {
        pecas[6] = tab[(lin+2)*8+(col+1)];
    }
    //Movimento para cima e direita
    else if(tab[(lin+2)*8+(col-1)] == 3 || tab[(lin+2)*8+(col-1)] == 9)
    {
        pecas[7] = tab[(lin+2)*8+(col-1)];
    }
    else
    {
        return false;
    }

    return pecas;
}

int verifica_ameaca_rei(int* horizontal, int* diagonal, int*vertical, int* cavalo, int rei)
{
    if(rei == reiB)
    {
        if(vertical[0]        ==  torreP || vertical[0]   == rainhaP)
        {
            return false;
        }
        else if(vertical[1]   ==  torreP || vertical[1]   == rainhaP)
        {
            return false;
        }
        else if(horizontal[0] ==  torreP || horizontal[0] == rainhaP)
        {
            return false;
        }
        else if(horizontal[1] ==  torreP || horizontal[1] == rainhaP)
        {
            return false;
        }
        else if(diagonal[0]   ==  bispoP || diagonal[0]   == rainhaP)
        {
            return false;
        }
        else if(diagonal[1]   ==  bispoP || diagonal[1]   == rainhaP)
        {
            return false;
        }
        else if(diagonal[2]   ==  bispoP || diagonal[2]   == rainhaP)
        {
            return false;
        }
        else if(diagonal[3]   ==  bispoP || diagonal[3]   == rainhaP)
        {
            return false;
        }
        else if(cavalo[0]     ==  cavaloP)
        {
            return false;
        }
        else if(cavalo[1]     ==  cavaloP)
        {
            return false;
        }
        else if(cavalo[2]     ==  cavaloP)
        {
            return false;
        }
        else if(cavalo[3]     ==  cavaloP)
        {
            return false;
        }
        else if(cavalo[4]     ==  cavaloP)
        {
            return false;
        }
        else if(cavalo[5]     ==  cavaloP)
        {
            return false;
        }
        else if(cavalo[6]     ==  cavaloP)
        {
            return false;
        }
        else if(cavalo[7]     ==  cavaloP)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    if(rei == reiP)
    {
        if(vertical[0]        ==  torreB || vertical[0]   == rainhaB)
        {
            return false;
        }
        else if(vertical[1]   ==  torreB || vertical[1]   == rainhaB)
        {
            return false;
        }
        else if(horizontal[0] ==  torreB || horizontal[0] == rainhaB)
        {
            return false;
        }
        else if(horizontal[1] ==  torreB || horizontal[1] == rainhaB)
        {
            return false;
        }
        else if(diagonal[0]   ==  bispoB || diagonal[0]   == rainhaB)
        {
            return false;
        }
        else if(diagonal[1]   ==  bispoB || diagonal[1]   == rainhaB)
        {
            return false;
        }
        else if(diagonal[2]   ==  bispoB || diagonal[2]   == rainhaB)
        {
            return false;
        }
        else if(diagonal[3]   ==  bispoB || diagonal[3]   == rainhaB)
        {
            return false;
        }
        else if(cavalo[0]     ==  cavaloB)
        {
            return false;
        }
        else if(cavalo[1]     ==  cavaloB)
        {
            return false;
        }
        else if(cavalo[2]     ==  cavaloB)
        {
            return false;
        }
        else if(cavalo[3]     ==  cavaloB)
        {
            return false;
        }
        else if(cavalo[4]     ==  cavaloB)
        {
            return false;
        }
        else if(cavalo[5]     ==  cavaloB)
        {
            return false;
        }
        else if(cavalo[6]     ==  cavaloB)
        {
            return false;
        }
        else if(cavalo[7]     ==  cavaloB)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}
int peao_protege(int lin,int col, int* tab, int peao)
{
    if(peao == peaoB)
    {
        if(tab[(lin-1)*8+(col-1)]>=8 && tab[(lin+1)*8+(col+1) == reiB])
        {
            return true;
        }
        else if(tab[(lin-1)*8+(col+1)]>=8 && tab[(lin+1)*8+(col-1)] == reiB)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if(peao == peaoP)
    {
        if(tab[(lin-1)*8+(col-1)]>=8 && tab[(lin+1)*8+(col+1) == reiP])
        {
            return true;
        }
        else if(tab[(lin-1)*8+(col+1)]>=8 && tab[(lin+1)*8+(col-1)] == reiP)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
int verifica_ameaca_servo(int lin, int col, int* tab, int peca)
{
    int rei;
    if(peca > 1 && peca < 8)
    {
        rei = reiB;
    }
    else
    {
        rei = reiP;
    }

    int* diagonal = peca_diagonal(lin,col,tab,rei);
    int* horizontal = peca_horizontal(lin,col,tab,rei);
    int* vertical = peca_vertical(lin,col,tab,rei);

    if(rei == reiB)
    {
        if(peca == torreB)
        {
            if((vertical[0]        ==  torreP || vertical[0]   == rainhaP) && vertical[1]   == reiB)
            {
                return Cima;
            }
            else if((vertical[1]   ==  torreP || vertical[1]   == rainhaP) && vertical[0]   == reiB)
            {
                return Baixo;
            }
            else if((horizontal[0] ==  torreP || horizontal[0] == rainhaP) && horizontal[1] == reiB)
            {
                return Direita;
            }
            else if((horizontal[1] ==  torreP || horizontal[1] == rainhaP) && horizontal[0] == reiB)
            {
                return Esquerda;
            }
            else if((diagonal[0]   ==  bispoP || diagonal[0]   == rainhaP) && diagonal[2]   == reiB)
            {
                return false;
            }
            else if((diagonal[1]   ==  bispoP || diagonal[1]   == rainhaP) && diagonal[3]   == reiB)
            {
                return false;
            }
            else if((diagonal[2]   ==  bispoP || diagonal[2]   == rainhaP) && diagonal[0]   == reiB)
            {
                return false;
            }
            else if((diagonal[3]   ==  bispoP || diagonal[3]   == rainhaP) && diagonal[1]   == reiB)
            {
                return false;
            }
            else
        {
            return true;
        }
        }
        else if(peca == peaoB)
        {
            if((vertical[0]        ==  torreP || vertical[0]   == rainhaP) && vertical[1]   == reiB)
            {
                return false;
            }
            else if((vertical[1]   ==  torreP || vertical[1]   == rainhaP) && vertical[0]   == reiB)
            {
                return false;
            }
            else if((horizontal[0] ==  torreP || horizontal[0] == rainhaP) && horizontal[1] == reiB)
            {
                return false;
            }
            else if((horizontal[1] ==  torreP || horizontal[1] == rainhaP) && horizontal[0] == reiB)
            {
                return false;
            }
            else if((diagonal[0]   ==  bispoP || diagonal[0]   == rainhaP) && diagonal[2]   == reiB)
            {
                return false;
            }
            else if((diagonal[1]   ==  bispoP || diagonal[1]   == rainhaP) && diagonal[3]   == reiB)
            {
                return false;
            }
            else if((diagonal[2]   ==  bispoP || diagonal[2]   == rainhaP) && diagonal[0]   == reiB)
            {
                if(peao_protege(lin,col, tab, peca))
                {
                    return DC_Direita;
                }
                else
                {
                    return false;
                }
            }
            else if((diagonal[3]   ==  bispoP || diagonal[3]   == rainhaP) && diagonal[1]   == reiB)
            {
                if(peao_protege(lin,col, tab, peca))
                {
                    return DC_Direita;
                }
                else
                {
                    return false;
                }
            }
            else
        {
            return true;
        }
        } 
        else if(peca == bispoB)
        {
            if((vertical[0]        ==  torreP || vertical[0]   == rainhaP) && vertical[1]   == reiB)
            {
                return false;
            }
            else if((vertical[1]   ==  torreP || vertical[1]   == rainhaP) && vertical[0]   == reiB)
            {
                return false;
            }
            else if((horizontal[0] ==  torreP || horizontal[0] == rainhaP) && horizontal[1] == reiB)
            {
                return false;
            }
            else if((horizontal[1] ==  torreP || horizontal[1] == rainhaP) && horizontal[0] == reiB)
            {
                return false;
            }
            else if((diagonal[0]   ==  bispoP || diagonal[0]   == rainhaP) && diagonal[2]   == reiB)
            {
                return DB_Esquerda;
            }
            else if((diagonal[1]   ==  bispoP || diagonal[1]   == rainhaP) && diagonal[3]   == reiB)
            {
                return DB_Direita;
            }
            else if((diagonal[2]   ==  bispoP || diagonal[2]   == rainhaP) && diagonal[0]   == reiB)
            {
                return DC_Direita;
            }
            else if((diagonal[3]   ==  bispoP || diagonal[3]   == rainhaP) && diagonal[1]   == reiB)
            {
                return DC_Esquerda;
            }
            else
        {
            return true;
        }
        }
        else if(peca == rainhaB)
        {
            if((vertical[0]        ==  torreP || vertical[0]   == rainhaP) && vertical[1]   == reiB)
            {
                return Cima;
            }
            else if((vertical[1]   ==  torreP || vertical[1]   == rainhaP) && vertical[0]   == reiB)
            {
                return Baixo;
            }
            else if((horizontal[0] ==  torreP || horizontal[0] == rainhaP) && horizontal[1] == reiB)
            {
                return Direita;
            }
            else if((horizontal[1] ==  torreP || horizontal[1] == rainhaP) && horizontal[0] == reiB)
            {
                return Esquerda;
            }
            else if((diagonal[0]   ==  bispoP || diagonal[0]   == rainhaP) && diagonal[2]   == reiB)
            {
                return DB_Esquerda;
            }
            else if((diagonal[1]   ==  bispoP || diagonal[1]   == rainhaP) && diagonal[3]   == reiB)
            {
                return DB_Direita;
            }
            else if((diagonal[2]   ==  bispoP || diagonal[2]   == rainhaP) && diagonal[0]   == reiB)
            {
                return DC_Direita;
            }
            else if((diagonal[3]   ==  bispoP || diagonal[3]   == rainhaP) && diagonal[1]   == reiB)
            {
                return DC_Esquerda;
            }
            else
            {
                return true;
            }
        }
        else
        {
            if((vertical[0]        ==  torreP || vertical[0]   == rainhaP) && vertical[1]   == reiB)
            {
                return false;
            }
            else if((vertical[1]   ==  torreP || vertical[1]   == rainhaP) && vertical[0]   == reiB)
            {
                return false;
            }
            else if((horizontal[0] ==  torreP || horizontal[0] == rainhaP) && horizontal[1] == reiB)
            {
                return false;
            }
            else if((horizontal[1] ==  torreP || horizontal[1] == rainhaP) && horizontal[0] == reiB)
            {
                return false;
            }
            else if((diagonal[0]   ==  bispoP || diagonal[0]   == rainhaP) && diagonal[2]   == reiB)
            {
                return false;
            }
            else if((diagonal[1]   ==  bispoP || diagonal[1]   == rainhaP) && diagonal[3]   == reiB)
            {
                return false;
            }
            else if((diagonal[2]   ==  bispoP || diagonal[2]   == rainhaP) && diagonal[0]   == reiB)
            {
                return false;
            }
            else if((diagonal[3]   ==  bispoP || diagonal[3]   == rainhaP) && diagonal[1]   == reiB)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
    if(rei == reiP)
    {
        if(peca == torreP)
        {
            if((vertical[0]        ==  torreB || vertical[0]   == rainhaB) && vertical[1]   == reiP)
            {
                return Cima;
            }
            else if((vertical[1]   ==  torreB || vertical[1]   == rainhaB) && vertical[0]   == reiP)
            {
                return Baixo;
            }
            else if((horizontal[0] ==  torreB || horizontal[0] == rainhaB) && horizontal[1] == reiP)
            {
                return Direita;
            }
            else if((horizontal[1] ==  torreB || horizontal[1] == rainhaB) && horizontal[0] == reiP)
            {
                return Esquerda;
            }
            else if((diagonal[0]   ==  bispoB || diagonal[0]   == rainhaB) && diagonal[2]   == reiP)
            {
                return false;
            }
            else if((diagonal[1]   ==  bispoB || diagonal[1]   == rainhaB) && diagonal[3]   == reiP)
            {
                return false;
            }
            else if((diagonal[2]   ==  bispoB || diagonal[2]   == rainhaB) && diagonal[0]   == reiP)
            {
                return false;
            }
            else if((diagonal[3]   ==  bispoB || diagonal[3]   == rainhaB) && diagonal[1]   == reiP)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else if(peca == peaoP)
        {
            if((vertical[0]        ==  torreB || vertical[0]   == rainhaB) && vertical[1]   == reiP)
            {
                return false;
            }
            else if((vertical[1]   ==  torreB || vertical[1]   == rainhaB) && vertical[0]   == reiP)
            {
                return false;
            }
            else if((horizontal[0] ==  torreB || horizontal[0] == rainhaB) && horizontal[1] == reiP)
            {
                return false;
            }
            else if((horizontal[1] ==  torreB || horizontal[1] == rainhaB) && horizontal[0] == reiP)
            {
                return false;
            }
            else if((diagonal[0]   ==  bispoB || diagonal[0]   == rainhaB) && diagonal[2]   == reiP && peao_protege(lin,col,tab,peca))
            {
                if(peao_protege(lin,col, tab, peca))
                {
                    return DB_Direita;
                }
                else
                {
                    return false;
                }
            }
            else if((diagonal[1]   ==  bispoB || diagonal[1]   == rainhaB) && diagonal[3]   == reiP && peao_protege(lin,col,tab,peca))
            {
                if(peao_protege(lin,col, tab, peca))
                {
                    return DB_Direita;
                }
                else
                {
                    return false;
                }
            }
            else if((diagonal[2]   ==  bispoB || diagonal[2]   == rainhaB) && diagonal[0]   == reiP)
            {
                return false;
            }
            else if((diagonal[3]   ==  bispoB || diagonal[3]   == rainhaB) && diagonal[1]   == reiP)
            {
                return false;
            }
            else
        {
            return true;
        }
        } 
        else if(peca == bispoP)
        {
            if((vertical[0]        ==  torreB || vertical[0]   == rainhaB) && vertical[1]   == reiP)
            {
                return false;
            }
            else if((vertical[1]   ==  torreB || vertical[1]   == rainhaB) && vertical[0]   == reiP)
            {
                return false;
            }
            else if((horizontal[0] ==  torreB || horizontal[0] == rainhaB) && horizontal[1] == reiP)
            {
                return false;
            }
            else if((horizontal[1] ==  torreB || horizontal[1] == rainhaB) && horizontal[0] == reiP)
            {
                return false;
            }
            else if((diagonal[0]   ==  bispoB || diagonal[0]   == rainhaB) && diagonal[2]   == reiP)
            {
                return DB_Esquerda;
            }
            else if((diagonal[1]   ==  bispoB || diagonal[1]   == rainhaB) && diagonal[3]   == reiP)
            {
                return DB_Direita;
            }
            else if((diagonal[2]   ==  bispoB || diagonal[2]   == rainhaB) && diagonal[0]   == reiP)
            {
                return DC_Direita;
            }
            else if((diagonal[3]   ==  bispoB || diagonal[3]   == rainhaB) && diagonal[1]   == reiP)
            {
                return DC_Esquerda;
            }
            else
        {
            return true;
        }
        }
        else if(peca == rainhaP)
        {
            if((vertical[0]        ==  torreB || vertical[0]   == rainhaB) && vertical[1]   == reiP)
            {
                return Cima;
            }
            else if((vertical[1]   ==  torreB || vertical[1]   == rainhaB) && vertical[0]   == reiP)
            {
                return Baixo;
            }
            else if((horizontal[0] ==  torreB || horizontal[0] == rainhaB) && horizontal[1] == reiP)
            {
                return Direita;
            }
            else if((horizontal[1] ==  torreB || horizontal[1] == rainhaB) && horizontal[0] == reiP)
            {
                return Esquerda;
            }
            else if((diagonal[0]   ==  bispoB || diagonal[0]   == rainhaB) && diagonal[2]   == reiP)
            {
                return DB_Esquerda;
            }
            else if((diagonal[1]   ==  bispoB || diagonal[1]   == rainhaB) && diagonal[3]   == reiP)
            {
                return DB_Direita;
            }
            else if((diagonal[2]   ==  bispoB || diagonal[2]   == rainhaB) && diagonal[0]   == reiP)
            {
                return DC_Direita;
            }
            else if((diagonal[3]   ==  bispoB || diagonal[3]   == rainhaB) && diagonal[1]   == reiP)
            {
                return DB_Esquerda;
            }
            else
        {
            return true;
        }
        }
        else
        {
            if((vertical[0]        ==  torreB || vertical[0]   == rainhaB) && vertical[1]   == reiP)
            {
                return false;
            }
            else if((vertical[1]   ==  torreB || vertical[1]   == rainhaB) && vertical[0]   == reiP)
            {
                return false;
            }
            else if((horizontal[0] ==  torreB || horizontal[0] == rainhaB) && horizontal[1] == reiP)
            {
                return false;
            }
            else if((horizontal[1] ==  torreB || horizontal[1] == rainhaB) && horizontal[0] == reiP)
            {
                return false;
            }
            else if((diagonal[0]   ==  bispoB || diagonal[0]   == rainhaB) && diagonal[2]   == reiP)
            {
                return false;
            }
            else if((diagonal[1]   ==  bispoB || diagonal[1]   == rainhaB) && diagonal[3]   == reiP)
            {
                return false;
            }
            else if((diagonal[2]   ==  bispoB || diagonal[2]   == rainhaB) && diagonal[0]   == reiP)
            {
                return false;
            }
            else if((diagonal[3]   ==  bispoB || diagonal[3]   == rainhaB) && diagonal[1]   == reiP)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
}

int horizontal(int lin_ori, int col_ori, int col_des, int *tab)
{
    //Leitura das horizontais para ver se há alguma peça impedindo de chegar ao destino
    bool validar = false;
    
    //Leitura da horizontal para direita
    if(col_ori<col_des)
    {
        for(int i=col_ori+1;i<col_des;i++)
        {
            if(tab[lin_ori*8+i]>1)
            {
                return false;
            }
            else
            validar = false;
        }
    }
    
    //Leitura da horizontal para esquerda
    else
    {
        for(int i=col_ori-1;i>col_des;i--)
        {
            if(tab[lin_ori*8+i]>1)
            {
                return false;
            }
            else
            validar = true;
        }
    }
    
    return validar;
}
int diagonal(int lin_ori, int col_ori, int lin_des, int col_des, int *tab)
{
    //Ler as diagonais para ver se até o destino não há alguma peça impedindo a passagem
    bool validar = false;
    
    //Movimento para baixo e esquerda
    if(lin_ori < lin_des && col_ori > col_des)
    {
        for(int i = lin_des-1, j = col_des+1;i>lin_ori && j<col_ori;i--,j++)
        {
            if(tab[i*8+j]>1)
            {
                return false;
            }
            else
            {
                validar = true;
            }
        }
    }
    //Movimento para baixo e direita
    else if(lin_ori < lin_des && col_ori < col_des)
    {
        for(int i = lin_des-1, j = col_des-1;i>lin_ori && j>col_ori;i--,j--)
        {
            if(tab[i*8+j]>1)
            {
                return false;
            }
            else
            {
                validar = true;
            }
        }
    }   
    //Movimento para cima e direita
    else if(lin_ori > lin_des && col_ori < col_des)
    {
        for(int i = lin_des+1, j = col_des-1;i<lin_ori && j>col_ori;i++,j--)
        {
            if(tab[i*8+j]>1)
            {
                return false;
            }
            else
            {
                validar = true;
            }
        }
    }
    //Movimento para cima e esquerda
    else if(lin_ori > lin_des && col_ori > col_des)
    {
        for(int i = lin_des+1, j = col_des+1;i<lin_ori && j<col_ori;i++,j++)
        {
            if(tab[i*8+j]>1)
            {
                return false;
            }
            else
            {
                validar = true;
            }
        }

    }
    else
    {
        return false;
    }
    return validar;
}
int vertical(int lin_ori, int col_ori, int lin_des, int *tab)
{
    //Leitura das verticais para ver se há alguma peça impedindo de chegar ao destino
    bool validar = false;

    //Leitura da vertical para baixo
    if(lin_ori<lin_des)
    {
        for(int i=lin_ori+1;i<lin_des;i++)
        {
            if(tab[i*8+col_ori]>1)
            {
                return false;
            }
            else
            validar = true;
        }
    }

    //Leitura da vertical para cima
    else
    {
        for(int i=lin_ori-1;i>lin_des;i--)
        {
            if(tab[i*8+col_ori]>1)
            {
                return false;
            }
            else
                validar = true;
        }
    }

    return validar;
}
int sistema(int peca, int col_ori, int lin_ori, int lin_des, int col_des, int *tabuleiro)
{
    bool validar = false;
    int ameaca = verifica_ameaca_servo(lin_ori,col_ori,tabuleiro,peca);
    int* diag = peca_diagonal(lin_des,col_des,tabuleiro,reiB);
    int* horiz = peca_horizontal(lin_des,col_des,tabuleiro,reiB);
    int* vert = peca_vertical(lin_des,col_des,tabuleiro,reiB);
    int* cav = peca_cavalo(lin_des, col_des, tabuleiro);

    switch(peca)
    {
        case peaoP:
        if(ameaca > 1)
        {
            if(ameaca == DB_Direita && lin_des == lin_ori + 1 && col_des == col_ori + 1)
            {
                return true;
            }
            else if(ameaca == DB_Esquerda && lin_des == lin_ori + 1 && col_des == col_ori - 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        
        //Movimento nas Diagonais
        if(lin_des == lin_ori+1 && (col_des == col_ori-1 || col_des == col_ori+1) && tabuleiro[lin_des*8+col_des]<8 && tabuleiro[lin_des*8+col_des]>1)
        {
            validar = true;
        }
        //Movimento de Um Passo Para Frente
        else if(col_ori == col_des && lin_des == lin_ori+1 && tabuleiro[lin_des*8+col_des]<=1)
        {
            validar = true;
        }
        //Movimento de Dois Passos Para Frente
        else if(lin_ori == 1 && col_ori == col_des && lin_des == 3 && tabuleiro[2*8+col_ori] <= 1 && tabuleiro[3*8+col_ori] <= 1)
        {
            validar = true;
        }
        else
        {
            return false;
        }
        break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case peaoB:
        if(ameaca > 1)
        {
            if(ameaca == DC_Direita && lin_des == lin_ori - 1 && col_des == col_ori + 1)
            {
                return true;
            }
            else if(ameaca == DC_Esquerda && lin_des == lin_ori - 1 && col_des == col_ori - 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        //Movimento nas Diagonais
        if(lin_des == lin_ori-1 && (col_des == col_ori-1 || col_des == col_ori+1) && tabuleiro[lin_des*8+col_des]>=8)
        {
            validar = true;
        }
        //Movimento de Um Passo para Frente
        else if(col_ori == col_des && lin_des == lin_ori-1 && tabuleiro[lin_des*8+col_des]<=1)
        {
            validar = true;
        }
        //Movimento de Dois Passos para Frente
        else if(lin_ori == 6 && col_ori == col_des && lin_des == 4 && tabuleiro[5*8+col_ori] <= 1 && tabuleiro[4*8+col_ori] <= 1)
        {
            validar = true;
        }
        else
        {
            return false;
        }
        break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case cavaloB:
        if(tabuleiro[lin_des*8+col_des] <= 1 || tabuleiro[lin_des*8+col_des] >= 8)
        {
            //Movimento para Baixo e Esquerda ⬐
            if(lin_ori == lin_des - 1 && col_ori == col_des + 2)
            {
                validar = true;
            }
            //Movimento para Baixo e Direita ⬎
            else if(lin_ori == lin_des - 1 && col_ori == col_des - 2)
            {
                validar = true;
            }
            //Movimento para Cima e Esquerda ⬑
            else if(lin_ori == lin_des + 1 && col_ori == col_des + 2)
            {
                validar = true;
            }
            //Movimento para Cima e Direita ⬏
            else if(lin_ori == lin_des + 1 && col_ori == col_des - 2)
            {
                validar = true;
            }
            //Movimento para Baixo e Esquerda ↲
            else if(lin_ori == lin_des - 2 && col_ori == col_des + 1)
            {
                validar = true;
            }
            //Movimento para Baixo e Direita ↳
            else if(lin_ori == lin_des - 2 && col_ori == col_des - 1)
            {
                validar = true;
            }
            //Movimento para Cima e Esquerda ↰
            else if(lin_ori == lin_des + 2 && col_ori == col_des + 1)
            {
                validar = true;
            }
            //Movimento para Cima e Direita ↱
            else if(lin_ori == lin_des + 2 && col_ori == col_des - 1)
            {
                validar = true;
            }
            else
        {
            return false;
        }
        }
        else
        {
            return false;
        }
        break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case cavaloP:
        if(tabuleiro[lin_des*8+col_des] < 8)
        {
            //Movimento para Baixo e Esquerda ⬐
            if(lin_ori == lin_des - 1 && col_ori == col_des + 2)
            {
                validar = true;
            }
            //Movimento para Baixo e Direita ⬎
            else if(lin_ori == lin_des - 1 && col_ori == col_des - 2)
            {
                validar = true;
            }
            //Movimento para Cima e Esquerda ⬑
            else if(lin_ori == lin_des + 1 && col_ori == col_des + 2)
            {
                validar = true;
            }
            //Movimento para Cima e Direita ⬏
            else if(lin_ori == lin_des + 1 && col_ori == col_des - 2)
            {
                validar = true;
            }
            //Movimento para Baixo e Esquerda ↲
            else if(lin_ori == lin_des - 2 && col_ori == col_des + 1)
            {
                validar = true;
            }
            //Movimento para Baixo e Direita ↳
            else if(lin_ori == lin_des - 2 && col_ori == col_des - 1)
            {
                validar = true;
            }
            //Movimento para Cima e Esquerda ↰
            else if(lin_ori == lin_des + 2 && col_ori == col_des + 1)
            {
                validar = true;
            }
            //Movimento para Cima e Direita ↱
            else if(lin_ori == lin_des + 2 && col_ori == col_des - 1)
            {
                validar = true;
            }
            else
        {
            return false;
        }
        }
        else
        {
            return false;
        }
        break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case bispoB:
        if(ameaca > 1)
        {
            if(ameaca == DB_Direita && lin_des == lin_ori - 1 && col_des == col_ori + 1)
            {
                return true;
            }
            else if(ameaca == DB_Esquerda && lin_des == lin_ori - 1 && col_des == col_ori - 1)
            {
                return true;
            }
            else if(ameaca == DB_Direita && lin_des == lin_ori + 1 && col_des == col_ori + 1)
            {
                return true;
            }
            else if(ameaca == DB_Esquerda && lin_des == lin_ori + 1 && col_des == col_ori - 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        if(tabuleiro[lin_des*8+col_des] <= 1 || tabuleiro[lin_des*8+col_des] >= 8)
        {
        //Movimento para Diagonal Esquerda Baixo ⬋
        if(lin_ori == lin_des - 1 && col_ori == col_des - 1)
        {
            validar = true;
        }
        //Movimento para Diagonal Direita Baixo ⬊
        else if(lin_ori == lin_des - 1 && col_ori == col_des + 1)
        {
            validar = true;
        }
        //Movimento para Diagonal Esquerda Cima ⬉
        else if(lin_ori == lin_des + 1 && col_ori == col_des - 1)
        {
            validar = true;
        }
        //Movimento para Diagonal Direita Cima ⬈
        else if(lin_ori == lin_des + 1 && col_ori == col_des + 1)
        {
            validar = true;
        }
        else if(diagonal(lin_ori, col_ori, lin_des, col_des, tabuleiro) && verificadiagonal(lin_ori, col_ori, lin_des, col_des))
        {
            validar = true;
        }
        else
        {
            return false;
        }
        }
        else
        {
            return false;
        }
        break;
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case bispoP:
        if(ameaca > 1)
        {
            if(ameaca == DB_Direita && lin_des == lin_ori - 1 && col_des == col_ori + 1)
            {
                return true;
            }
            else if(ameaca == DB_Esquerda && lin_des == lin_ori - 1 && col_des == col_ori - 1)
            {
                return true;
            }
            else if(ameaca == DB_Direita && lin_des == lin_ori + 1 && col_des == col_ori + 1)
            {
                return true;
            }
            else if(ameaca == DB_Esquerda && lin_des == lin_ori + 1 && col_des == col_ori - 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        if(tabuleiro[lin_des*8+col_des] < 8)
        {
        //Movimento para Diagonal Esquerda Baixo ⬋
        if(lin_ori == lin_des - 1 && col_ori == col_des - 1)
        {
            validar = true;
        }
        //Movimento para Diagonal Direita Baixo ⬊
        else if(lin_ori == lin_des - 1 && col_ori == col_des + 1)
        {
            validar = true;
        }
        //Movimento para Diagonal Esquerda Cima ⬉
        else if(lin_ori == lin_des + 1 && col_ori == col_des - 1)
        {
            validar = true;
        }
        //Movimento para Diagonal Direita Cima ⬈
        else if(lin_ori == lin_des + 1 && col_ori == col_des + 1)
        {
            validar = true;
        }
        else if(diagonal(lin_ori, col_ori, lin_des, col_des, tabuleiro) && verificadiagonal(lin_ori, col_ori, lin_des, col_des))
        {
            validar = true;
        }
        else
        {
            return false;
        }
        }
        else
        {
            return false;
        }
        break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case torreB:
        if(ameaca > 1)
        {
            if(ameaca == Direita && lin_ori == lin_des && col_des == col_ori + 1)
            {
                return true;
            }
            else if(ameaca == Esquerda && lin_ori == lin_des && col_des == col_ori - 1)
            {
                return true;
            }
            else if(ameaca == Cima && col_ori == col_des && lin_des == lin_ori - 1)
            {
                return true;
            }
            else if(ameaca == Baixo && col_ori == col_des && lin_des == lin_ori + 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        if(tabuleiro[lin_des*8+col_des] <= 1 || tabuleiro[lin_des*8+col_des] >= 8)
        {
            //Movimento para Cima ⬆
            if(col_ori == col_des && lin_ori == lin_des + 1)
            {
                validar = true;
            }
            //Movimento para Direita ⮕
            else if(col_ori == col_des - 1 && lin_ori == lin_des)
            {
                validar = true;
            }
            //Movimento para Baixo ⬇
            else if(col_ori == col_des && lin_ori == lin_des - 1)
            {
                validar = true;
            }
            //Movimento para Esquerda ⬅
            else if(col_ori == col_des + 1 && lin_ori == lin_des)
            {
                validar = true;
            }
            //Movimento para as Verticais distantes
            else if(col_ori == col_des && (lin_ori < lin_des || lin_ori > lin_des) && vertical(lin_ori, col_ori, lin_des, tabuleiro))
            {
                validar = true;
            }
            //Movimento para as Horizontais distantes
            else if(lin_ori == lin_des && (col_ori < col_des || col_ori > col_des) && horizontal(lin_ori, col_ori, col_des, tabuleiro))
            {
                validar = true;
            }
            else
            {
                return false;
            }
        } 
        else
        {
            return false;
        }
        break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case torreP:
        if(ameaca > 1)
        {
            if(ameaca == Direita && lin_ori == lin_des && col_des == col_ori + 1)
            {
                return true;
            }
            else if(ameaca == Esquerda && lin_ori == lin_des && col_des == col_ori - 1)
            {
                return true;
            }
            else if(ameaca == Cima && col_ori == col_des && lin_des == lin_ori - 1)
            {
                return true;
            }
            else if(ameaca == Baixo && col_ori == col_des && lin_des == lin_ori + 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        if(tabuleiro[lin_des*8+col_des] < 8)
        {
            //Movimento para Cima ⬆
            if(col_ori == col_des && lin_ori == lin_des + 1)
            {
                validar = true;
            }
            //Movimento para Direita ⮕
            else if(col_ori == col_des - 1 && lin_ori == lin_des)
            {
                validar = true;
            }
            //Movimento para Baixo ⬇
            else if(col_ori == col_des && lin_ori == lin_des - 1)
            {
                validar = true;
            }
            //Movimento para Esquerda ⬅
            else if(col_ori == col_des + 1 && lin_ori == lin_des)
            {
                validar = true;
            }
            //Movimento para as Verticais distantes
            else if(col_ori == col_des && (lin_ori < lin_des || lin_ori > lin_des) && vertical(lin_ori, col_ori, lin_des, tabuleiro))
            {
                validar = true;
            }
            //Movimento para as Horizontais distantes
            else if(lin_ori == lin_des && (col_ori < col_des || col_ori > col_des) && horizontal(lin_ori, col_ori, col_des, tabuleiro))
            {
                validar = true;
            }
            else
            {
                return false;
            }
        }  
        break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case rainhaB:
        if(ameaca > 1)
        {
            if(ameaca == DB_Direita && lin_des == lin_ori - 1 && col_des == col_ori + 1)
            {
                return true;
            }
            else if(ameaca == DB_Esquerda && lin_des == lin_ori - 1 && col_des == col_ori - 1)
            {
                return true;
            }
            else if(ameaca == DB_Direita && lin_des == lin_ori + 1 && col_des == col_ori + 1)
            {
                return true;
            }
            else if(ameaca == DB_Esquerda && lin_des == lin_ori + 1 && col_des == col_ori - 1)
            {
                return true;
            }
            else if(ameaca == Direita && lin_ori == lin_des && col_des == col_ori + 1)
            {
                return true;
            }
            else if(ameaca == Esquerda && lin_ori == lin_des && col_des == col_ori - 1)
            {
                return true;
            }
            else if(ameaca == Cima && col_ori == col_des && lin_des == lin_ori - 1)
            {
                return true;
            }
            else if(ameaca == Baixo && col_ori == col_des && lin_des == lin_ori + 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        if(tabuleiro[lin_des*8+col_des] <= 1 || tabuleiro[lin_des*8+col_des] >= 8)
            {
                //Movimento para Cima ⬆
                if(col_ori == col_des && lin_ori == lin_des + 1)
                {
                    validar = true;
                }
                //Movimento para Diagonal Direita Cima ⬈
                else if(col_ori == col_des - 1 && lin_ori == lin_des + 1)
                {
                    validar = true;
                }
                //Movimento para Direita ⮕
                else if(col_ori == col_des - 1 && lin_ori == lin_des)
                {
                    validar = true;
                }
                //Movimento para Diagonal Direita Baixo ⬊
                else if(col_ori == col_des - 1 && lin_ori == lin_des - 1)
                {
                    validar = true;
                }
                //Movimento para Baixo ⬇
                else if(col_ori == col_des && lin_ori == lin_des - 1)
                {
                    validar = true;
                }
                //Movimento para Diagonal Esquerda Baixo ⬋
                else if(col_ori == col_des + 1 && lin_ori == lin_des - 1)
                {
                    validar = true;
                }
                //Movimento para Esquerda ⬅
                else if(col_ori == col_des + 1 && lin_ori == lin_des)
                {
                    validar = true;
                }
                //Movimento para Diagonal Esquerda Cima ⬉
                else if(col_ori == col_des + 1 && lin_ori == lin_des + 1)
                {
                    validar = true;
                }
                //Movimento nas Diagonais mais distantes
                else if(diagonal(lin_ori, col_ori, lin_des, col_des, tabuleiro) && verificadiagonal(lin_ori, col_ori, lin_des, col_des))
                {
                    validar = true;
                }     
                //Movimento para Verticais e Horizontais mais distantes   
                else if(verificadirecao(lin_ori, col_ori, lin_des, col_des))
                {
                    if(col_ori == col_des && vertical(lin_ori, col_ori, lin_des, tabuleiro))
                    {
                        validar = true;
                    }
                    else if(lin_ori == lin_des && horizontal(lin_ori, col_ori, col_des, tabuleiro))
                    {
                        validar = true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
        else
        {
            return false;
        }
        break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case rainhaP:
        if(ameaca > 1)
        {
            if(ameaca == DB_Direita && lin_des == lin_ori - 1 && col_des == col_ori + 1)
            {
                return true;
            }
            else if(ameaca == DB_Esquerda && lin_des == lin_ori - 1 && col_des == col_ori - 1)
            {
                return true;
            }
            else if(ameaca == DB_Direita && lin_des == lin_ori + 1 && col_des == col_ori + 1)
            {
                return true;
            }
            else if(ameaca == DB_Esquerda && lin_des == lin_ori + 1 && col_des == col_ori - 1)
            {
                return true;
            }
            else if(ameaca == Direita && lin_ori == lin_des && col_des == col_ori + 1)
            {
                return true;
            }
            else if(ameaca == Esquerda && lin_ori == lin_des && col_des == col_ori - 1)
            {
                return true;
            }
            else if(ameaca == Cima && col_ori == col_des && lin_des == lin_ori - 1)
            {
                return true;
            }
            else if(ameaca == Baixo && col_ori == col_des && lin_des == lin_ori + 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        if(tabuleiro[lin_des*8+col_des] < 8)
            {
                //Movimento para Cima ⬆
                if(col_ori == col_des && lin_ori == lin_des + 1)
                {
                    validar = true;
                }
                //Movimento para Diagonal Direita Cima ⬈
                else if(col_ori == col_des - 1 && lin_ori == lin_des + 1)
                {
                    validar = true;
                }
                //Movimento para Direita ⮕
                else if(col_ori == col_des - 1 && lin_ori == lin_des)
                {
                    validar = true;
                }
                //Movimento para Diagonal Direita Baixo ⬊
                else if(col_ori == col_des - 1 && lin_ori == lin_des - 1)
                {
                    validar = true;
                }
                //Movimento para Baixo ⬇
                else if(col_ori == col_des && lin_ori == lin_des - 1)
                {
                    validar = true;
                }
                //Movimento para Diagonal Esquerda Baixo ⬋
                else if(col_ori == col_des + 1 && lin_ori == lin_des - 1)
                {
                    validar = true;
                }
                //Movimento para Esquerda ⬅
                else if(col_ori == col_des + 1 && lin_ori == lin_des)
                {
                    validar = true;
                }
                //Movimento para Diagonal Esquerda Cima ⬉
                else if(col_ori == col_des + 1 && lin_ori == lin_des + 1)
                {
                    validar = true;
                }
                //Movimento nas Diagonais mais distantes
                else if(diagonal(lin_ori, col_ori, lin_des, col_des, tabuleiro) && verificadiagonal(lin_ori, col_ori, lin_des, col_des))
                {
                    validar = true;
                }        
                //Movimento para Verticais e Horizontais mais distantes   
                else if(verificadirecao(lin_ori, col_ori, lin_des, col_des))
                {
                    if((lin_ori < lin_des || lin_ori > lin_des) && col_ori == col_des && vertical(lin_ori, col_ori, lin_des, tabuleiro))
                    {
                        validar = true;
                    }
                    else if((col_ori < col_des || col_ori > col_des) && lin_ori == lin_des && horizontal(lin_ori, col_ori, col_des, tabuleiro))
                    {
                        validar = true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
        }
        else
        {
            return false;
        }
        break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case reiB:
        if(!verifica_ameaca_rei(horiz,diag,vert,cav,reiB))
        {
            return false;
        }

        if(tabuleiro[lin_des*8+col_des] <= 1 || tabuleiro[lin_des*8+col_des] >= 8)
        {
            //Movimento para Cima ⬆
            if(col_ori == col_des && lin_ori == lin_des + 1)
            {
                validar = true;
            }
            //Movimento para Diagonal Direita Cima ⬈
            else if(col_ori == col_des - 1 && lin_ori == lin_des + 1)
            {
                validar = true;
            }
            //Movimento para Direita ⮕
            else if(col_ori == col_des - 1 && lin_ori == lin_des)
            {
                validar = true;
            }
            //Movimento para Diagonal Direita Baixo ⬊
            else if(col_ori == col_des - 1 && lin_ori == lin_des - 1)
            {
                validar = true;
            }
            //Movimento para Baixo ⬇
            else if(col_ori == col_des && lin_ori == lin_des - 1)
            {
                validar = true;
            }
            //Movimento para Diagonal Esquerda Baixo ⬋
            else if(col_ori == col_des + 1 && lin_ori == lin_des - 1)
            {
                validar = true;
            }
            //Movimento para Esquerda ⬅
            else if(col_ori == col_des + 1 && lin_ori == lin_des)
            {
                validar = true;
            }
            //Movimento para Diagonal Esquerda Cima ⬉
            else if(col_ori == col_des + 1 && lin_ori == lin_des + 1)
            {
                validar = true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
        break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case reiP:
        if(!verifica_ameaca_rei(horiz,diag,vert,cav,reiP))
        {
            return false;
        }

        if(tabuleiro[lin_des*8+col_des] < 8)
        {
            //Movimento para Cima ⬆
            if(col_ori == col_des && lin_ori == lin_des + 1)
            {
                validar = true;
            }
            //Movimento para Diagonal Direita Cima ⬈
            else if(col_ori == col_des - 1 && lin_ori == lin_des + 1)
            {
                validar = true;
            }
            //Movimento para Direita ⮕
            else if(col_ori == col_des - 1 && lin_ori == lin_des)
            {
                validar = true;
            }
            //Movimento para Diagonal Direita Baixo ⬊
            else if(col_ori == col_des - 1 && lin_ori == lin_des - 1)
            {
                validar = true;
            }
            //Movimento para Baixo ⬇
            else if(col_ori == col_des && lin_ori == lin_des - 1)
            {
                validar = true;
            }
            //Movimento para Diagonal Esquerda Baixo ⬋
            else if(col_ori == col_des + 1 && lin_ori == lin_des - 1)
            {
                validar = true;
            }
            //Movimento para Esquerda ⬅
            else if(col_ori == col_des + 1 && lin_ori == lin_des)
            {
                validar = true;
            }
            //Movimento para Diagonal Esquerda Cima ⬉
            else if(col_ori == col_des + 1 && lin_ori == lin_des + 1)
            {
                validar = true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
        break;
    }
   
    free(diag);
    free(cav);
    free(vert);
    free(horiz);
    return validar;
}

void lermovimento(int *val_col,int *val_lin)
{
    //Ler a notação escrita e transformar na posição correspondente no tabuleiro
    bool validar = true;
    char notacao[3];

    while(validar)
    {
        scanf(" %c%c",&notacao[0],&notacao[1]);
        if(notacao[0] == '-' && notacao[1] == '-')
        {
            *val_col = -1;
            *val_lin = -1;
            return;
        }
        else if(notacao[0] < 'a' || notacao[0] > 'h' || notacao[1] < '1' || notacao[1] > '8')
        {
            printf("Erro!! Posição invalida, tente novamente.\n");
        }
        else
        {
            *val_col = notacao[0]-'a';
            *val_lin = '8' - notacao[1];
            validar = false;
        }
    };
}
int verificapeca(int* tab, int lin_ori, int col_ori)
{
    int peca = tab[lin_ori*8+col_ori];
    return peca;
}
void movimento(int *tab, int rodada)
{
    //Realizar o movimento proposto pelo jogador
    int lin_ori,col_ori,lin_des,col_des;
    int cor;
    bool validar = true;
    while(1)
    {
        bool cancelar = false;
        validar = true;

        while(validar)
        {
            printf("Informe a casa que você quer andar: ");
            lermovimento(&col_ori,&lin_ori);
            int peca = tab[lin_ori*8 + col_ori];

            if(peca == quadradoB || peca == quadradoP)
            {
                printf("Você não pode movimentar uma casa vazia! Tente novamente.\n");
                continue;
            }
            else if(lin_ori == -1 && col_ori == -1)
            {
                cancelar = true;
                break;
            }
            else if(!verifica_ameaca_servo(lin_ori,col_ori,tab,peca))
            {
                printf("Você não pode mover uma peça que protege o rei!");
                continue;
            }
            else if(rodada%2 == 0 && peca < 8)
            {
                printf("Você tentou movimentar uma peça preta na vez das brancas, tente novamente!\n");
                continue;
            }
            else if(rodada%2 != 0 && peca >= 8)
            {
                printf("Você tentou movimentar uma peça branca na vez das pretas, tente novamente!\n");
                continue;
            }
            else
            {
                validar = false;
            }
            printf("Você está movendo %s!\n", nomes[peca]);
            
        }

        if(cancelar)
        {
            printf("Ação cancelada\n\n");
            continue;
        }
        cancelar = false;
        validar = true;
        
        while(validar)
        {
            printf("Informe a casa para onde você quer andar: ");
            lermovimento(&col_des,&lin_des);
            int peca = tab[lin_ori*8 + col_ori];
            
            if(lin_des == -1 && col_des == -1)
            {
                cancelar = true;
                break;
            }
            else if(!sistema(peca, col_ori, lin_ori, lin_des, col_des, tab))
            {
                printf("Ação inválida!! Tente novamente.\n");
            }
            else
            validar = false;
        }

        if(cancelar)
        {
            printf("Ação cancelada\n\n");
            continue;
        } 
            
        break;
    }
    
    
    cor = cores(col_ori,lin_ori);
    tab[lin_des*8+col_des] = tab[lin_ori*8+col_ori];
    tab[lin_ori*8+col_ori] = cor;

    imprimirtabuleiro(tab);
}
