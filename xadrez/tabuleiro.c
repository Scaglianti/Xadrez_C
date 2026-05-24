#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tabuleiro.h"

static int RCP = true;
static int RLP = true;
static int RCB = true;
static int RLB = true;


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

void libera(int* n1,int* n2,int *n3, int*n4)
{
    //Função para liberar mais facilmente
    free(n1);
    free(n2);
    free(n3);
    free(n4);   
}

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
    printf("--Novo Tabuleiro--\n");
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
    pecas_numericas[2]     = pecas_numericas[5] = bispoP;
    pecas_numericas[6]     = pecas_numericas[1] = cavaloP;
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
    //Função criada para a rainha. Irá verificar se o movimento é válido para horizontal ou vertical
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

void modifica_tabuleiro_roque(int* tab, int roq)
{
    int cor;
    if(roq == RCBranco)
    {
        cor = cores(7,7);
        tab[7*8+5] = torreB;
        tab[7*8+7] = cor;
    }
    else if(roq == RLBranco)
    {
        cor = cores(0,7);
        tab[7*8+3] = torreB;
        tab[7*8] = cor;
    }
    else if(roq == RCPreto)
    {
        cor = cores(7,0);
        tab[5] = torreP;
        tab[7] = cor;
    }
    else if(roq == RLPreto)
    {
        cor = cores(0,0);
        tab[3] = torreP;
        tab[0] = cor;
    }
}
int verifica_roque(int lin_ori,int lin_des, int col_ori, int col_des, int*tab, int rei)
{
    if(rei == reiB)
    {
        if(lin_ori == 7 && col_ori == 4)
        {
            if(RCB == true && lin_ori == lin_des && col_des == col_ori + 2)
            {
                return true;
            }
            else if(RLB == true && lin_ori == lin_des && col_des == col_ori - 2)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        return false;
    }
    else if(rei == reiP)
    {
        if(lin_ori == 0 && col_ori == 4)
        {
            if(RCB == true && lin_ori == lin_des && col_des == col_ori + 2)
            {
                return true;
            }
            else if(RLB == true && lin_ori == lin_des && col_des == col_ori - 2)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        return false;
    }
    else
    {
        return false;
    }
}
int roque(int lin_ori,int col_ori, int lin_des, int col_des, int* tab, int rei)
{
    if(rei == reiB)
    {
        int* diag = peca_diagonal(lin_ori,col_ori,tab,reiB);
        int* horiz = peca_horizontal(lin_ori,col_ori,tab,reiB);
        int* vert = peca_vertical(lin_ori,col_ori,tab,reiB);
        int* cav = peca_cavalo(lin_ori, col_ori, tab);

        if(verifica_ameaca_rei(horiz,diag,vert,cav,reiB))
        {
            libera(diag,horiz,vert,cav);
            if(lin_ori == 7 && col_ori == 4 && horizontal(lin_ori,col_ori,col_des,tab))
            {
                if(lin_des == 7 && col_des == 6)
                {
                    int* diagRC1 = peca_diagonal(lin_des,5,tab,reiB);
                    int* horizRC1 = peca_horizontal(lin_des,5,tab,reiB);
                    int* vertRC1 = peca_vertical(lin_des,5,tab,reiB);
                    int* cavRC1 = peca_cavalo(lin_des, 5, tab);

                    int* diagRC2 = peca_diagonal(lin_des,6,tab,reiB);
                    int* horizRC2 = peca_horizontal(lin_des,6,tab,reiB);
                    int* vertRC2 = peca_vertical(lin_des,6,tab,reiB);
                    int* cavRC2 = peca_cavalo(lin_des, 6, tab);
                    if(RCB == true && verifica_ameaca_rei(horizRC1,diagRC1,vertRC1,cavRC1,reiB) && verifica_ameaca_rei(horizRC2,diagRC2,vertRC2,cavRC2,reiB))
                    {
                        modifica_tabuleiro_roque(tab,RCBranco);
                        RLB = false;
                        RCB = false;
                        libera(diagRC1,horizRC1,vertRC1,cavRC1);
                        libera(diagRC2,horizRC2,vertRC2,cavRC2);
                        return true;
                    }
                    else
                    {
                        libera(diagRC1,horizRC1,vertRC1,cavRC1);
                        libera(diagRC2,horizRC2,vertRC2,cavRC2);
                        return false;
                    }
                }
                else if(lin_des == 7 && col_des == 2)
                {
                    int* diagRL1 = peca_diagonal(lin_des,3,tab,reiB);
                    int* horizRL1 = peca_horizontal(lin_des,3,tab,reiB);
                    int* vertRL1 = peca_vertical(lin_des,3,tab,reiB);
                    int* cavRL1 = peca_cavalo(lin_des, 3, tab);

                    int* diagRL2 = peca_diagonal(lin_des,2,tab,reiB);
                    int* horizRL2 = peca_horizontal(lin_des,2,tab,reiB);
                    int* vertRL2 = peca_vertical(lin_des,2,tab,reiB);
                    int* cavRL2 = peca_cavalo(lin_des, 2, tab);
                    if(RLB == true && verifica_ameaca_rei(horizRL1,diagRL1,vertRL1,cavRL1,reiB) && verifica_ameaca_rei(horizRL2,diagRL2,vertRL2,cavRL2,reiB))
                    {
                        modifica_tabuleiro_roque(tab,RLBranco);
                        RCB = false;
                        RLB = false;
                        libera(diagRL1,horizRL1,vertRL1,cavRL1);
                        libera(diagRL2,horizRL2,vertRL2,cavRL2);
                        return true;
                    }
                    else
                    {
                        libera(diagRL1,horizRL1,vertRL1,cavRL1);
                        libera(diagRL2,horizRL2,vertRL2,cavRL2);
                        return false;
                    }
                }
                else 
                return false;
            }   
            else
            return false;
        }
        else
        {
            libera(diag,horiz,vert,cav);
            return false;
        }
        
    }
    else if(rei == reiP)
    {
        int* diag = peca_diagonal(lin_ori,col_ori,tab,reiP);
        int* horiz = peca_horizontal(lin_ori,col_ori,tab,reiP);
        int* vert = peca_vertical(lin_ori,col_ori,tab,reiP);
        int* cav = peca_cavalo(lin_ori, col_ori, tab);
        if(verifica_ameaca_rei(horiz,diag,vert,cav,reiP))
        {
            libera(diag,horiz,vert,cav);
            if(lin_ori == 0 && col_ori == 4 && horizontal(lin_ori,col_ori,col_des,tab))
            {
                if(lin_des == 0 && col_des == 6)
                {
                    int* diagRC1 = peca_diagonal(lin_des,5,tab,reiP);
                    int* horizRC1 = peca_horizontal(lin_des,5,tab,reiP);
                    int* vertRC1 = peca_vertical(lin_des,5,tab,reiP);
                    int* cavRC1 = peca_cavalo(lin_des, 5, tab);

                    int* diagRC2 = peca_diagonal(lin_des,6,tab,reiP);
                    int* horizRC2 = peca_horizontal(lin_des,6,tab,reiP);
                    int* vertRC2 = peca_vertical(lin_des,6,tab,reiP);
                    int* cavRC2 = peca_cavalo(lin_des, 6, tab);

                    if(RCP == true && verifica_ameaca_rei(horizRC1,diagRC1,vertRC1,cavRC1,reiP) && verifica_ameaca_rei(horizRC2,diagRC2,vertRC2,cavRC2,reiP))
                    {
                        modifica_tabuleiro_roque(tab,RCPreto);
                        libera(diagRC1,horizRC1,vertRC1,cavRC1);
                        libera(diagRC2,horizRC2,vertRC2,cavRC2);
                        RLP = false;
                        RCP = false;
                        return true;
                    }
                    else
                    {
                        libera(diagRC1,horizRC1,vertRC1,cavRC1);
                        libera(diagRC2,horizRC2,vertRC2,cavRC2);
                        return false;
                    }
                }
                else if(lin_des == 0 && col_des == 2)
                {
                    int* diagRL1 = peca_diagonal(lin_des,3,tab,reiP);
                    int* horizRL1 = peca_horizontal(lin_des,3,tab,reiP);
                    int* vertRL1 = peca_vertical(lin_des,3,tab,reiP);
                    int* cavRL1 = peca_cavalo(lin_des, 3, tab);

                    int* diagRL2 = peca_diagonal(lin_des,2,tab,reiP);
                    int* horizRL2 = peca_horizontal(lin_des,2,tab,reiP);
                    int* vertRL2 = peca_vertical(lin_des,2,tab,reiP);
                    int* cavRL2 = peca_cavalo(lin_des, 2, tab);
                    if(RLP == true && verifica_ameaca_rei(horizRL1,diagRL1,vertRL1,cavRL1,reiP) && verifica_ameaca_rei(horizRL2,diagRL2,vertRL2,cavRL2,reiP))
                    {
                        modifica_tabuleiro_roque(tab,RLPreto);
                        RCP = false;
                        RLP = false;
                        libera(diagRL1,horizRL1,vertRL1,cavRL1);
                        libera(diagRL2,horizRL2,vertRL2,cavRL2);
                        return true;
                    }
                    else
                    {
                        libera(diagRL1,horizRL1,vertRL1,cavRL1);
                        libera(diagRL2,horizRL2,vertRL2,cavRL2);
                        return false;
                    }
                }
                else
                return false;
            }
            else
            return false;
        }
        else
        {
            libera(diag,horiz,vert,cav);
            return false;
        }
    }
    else
    return false;
}

int reis(int peca)
{
    //Função para retornar o valor do rei (Preto ou Branco) que está atuando no momento
    if(peca > 1 && peca < 8)
    {
        return reiB;
    }
    else if(peca >= 8)
    {
        return reiP;
    }
    else
    {
        return false;
    }
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
            break;
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
            break;
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
            break;
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
            break;
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
            break;
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
            break;
        }
        else
            pecas[1] = false;
    }

    return pecas;
}
int* peca_cavalo(int lin, int col, int* tab)
{
    int* pecas = calloc(8, sizeof(int));

    int movimentos[8][2] = {
        {-1, +2}, {-1, -2},
        {+1, +2}, {+1, -2},
        {-2, +1}, {-2, -1},
        {+2, +1}, {+2, -1}
    };

    for(int k = 0; k < 8; k++)
    {
        int nl = lin + movimentos[k][0];
        int nc = col + movimentos[k][1];

        if(nl >= 0 && nl < 8 && nc >= 0 && nc < 8)
        {
            int p = tab[nl*8+nc];
            if(p == cavaloB || p == cavaloP)
                pecas[k] = p;
        }
    }

    return pecas;
}

int verifica_ameaca_rei(int* horizontal, int* diagonal, int*vertical, int* cavalo, int rei)
{
    //Função para identificar um possível check, não deixando o rei se movimentar para a posição caso necessário
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
    else if(rei == reiP)
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
    else
    return false;
}
int peao_protege(int lin,int col, int* tab, int peao)
{
    //Função específica para o peão na sua função de proteger o rei num possível check
    if(peao == peaoB)
    {
        if(tab[(lin-1)*8+(col-1)]>=8 && tab[(lin+1)*8+(col+1)] == reiB)
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
        if(tab[(lin-1)*8+(col-1)]>=8 && tab[(lin+1)*8+(col+1)] == reiP)
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
    //Função para as peças que protegem o rei
    //Permitem as peças se moverem caso possam defender o rei se colocando como escudo ou, se possível, matarem a peça que ameaça o rei 
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
                libera(diagonal,horizontal, vertical, NULL);
                return Cima;
            }
            else if((vertical[1]   ==  torreP || vertical[1]   == rainhaP) && vertical[0]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return Baixo;
            }
            else if((horizontal[0] ==  torreP || horizontal[0] == rainhaP) && horizontal[1] == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return Direita;
            }
            else if((horizontal[1] ==  torreP || horizontal[1] == rainhaP) && horizontal[0] == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return Esquerda;
            }
            else if((diagonal[0]   ==  bispoP || diagonal[0]   == rainhaP) && diagonal[2]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((diagonal[1]   ==  bispoP || diagonal[1]   == rainhaP) && diagonal[3]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((diagonal[2]   ==  bispoP || diagonal[2]   == rainhaP) && diagonal[0]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((diagonal[3]   ==  bispoP || diagonal[3]   == rainhaP) && diagonal[1]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else
        {
            libera(diagonal,horizontal, vertical, NULL);
            return true;
        }
        }
        else if(peca == peaoB)
        {
            if((vertical[0]        ==  torreP || vertical[0]   == rainhaP) && vertical[1]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((vertical[1]   ==  torreP || vertical[1]   == rainhaP) && vertical[0]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((horizontal[0] ==  torreP || horizontal[0] == rainhaP) && horizontal[1] == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((horizontal[1] ==  torreP || horizontal[1] == rainhaP) && horizontal[0] == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((diagonal[0]   ==  bispoP || diagonal[0]   == rainhaP) && diagonal[2]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((diagonal[1]   ==  bispoP || diagonal[1]   == rainhaP) && diagonal[3]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((diagonal[2]   ==  bispoP || diagonal[2]   == rainhaP) && diagonal[0]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
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
                libera(diagonal,horizontal, vertical, NULL);
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
                libera(diagonal,horizontal, vertical, NULL);
                return true;
            }
        } 
        else if(peca == bispoB)
        {
            if((vertical[0]        ==  torreP || vertical[0]   == rainhaP) && vertical[1]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((vertical[1]   ==  torreP || vertical[1]   == rainhaP) && vertical[0]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((horizontal[0] ==  torreP || horizontal[0] == rainhaP) && horizontal[1] == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((horizontal[1] ==  torreP || horizontal[1] == rainhaP) && horizontal[0] == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((diagonal[0]   ==  bispoP || diagonal[0]   == rainhaP) && diagonal[2]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return DB_Esquerda;
            }
            else if((diagonal[1]   ==  bispoP || diagonal[1]   == rainhaP) && diagonal[3]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return DB_Direita;
            }
            else if((diagonal[2]   ==  bispoP || diagonal[2]   == rainhaP) && diagonal[0]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return DC_Direita;
            }
            else if((diagonal[3]   ==  bispoP || diagonal[3]   == rainhaP) && diagonal[1]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return DC_Esquerda;
            }
            else
            {
                libera(diagonal,horizontal, vertical, NULL);
                return true;
            }
        }
        else if(peca == rainhaB)
        {
            if((vertical[0]        ==  torreP || vertical[0]   == rainhaP) && vertical[1]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return Cima;
            }
            else if((vertical[1]   ==  torreP || vertical[1]   == rainhaP) && vertical[0]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return Baixo;
            }
            else if((horizontal[0] ==  torreP || horizontal[0] == rainhaP) && horizontal[1] == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return Direita;
            }
            else if((horizontal[1] ==  torreP || horizontal[1] == rainhaP) && horizontal[0] == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return Esquerda;
            }
            else if((diagonal[0]   ==  bispoP || diagonal[0]   == rainhaP) && diagonal[2]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return DB_Esquerda;
            }
            else if((diagonal[1]   ==  bispoP || diagonal[1]   == rainhaP) && diagonal[3]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return DB_Direita;
            }
            else if((diagonal[2]   ==  bispoP || diagonal[2]   == rainhaP) && diagonal[0]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return DC_Direita;
            }
            else if((diagonal[3]   ==  bispoP || diagonal[3]   == rainhaP) && diagonal[1]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return DC_Esquerda;
            }
            else
            {
                libera(diagonal,horizontal, vertical, NULL);
                return true;
            }
        }
        else
        {
            if((vertical[0]        ==  torreP || vertical[0]   == rainhaP) && vertical[1]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((vertical[1]   ==  torreP || vertical[1]   == rainhaP) && vertical[0]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((horizontal[0] ==  torreP || horizontal[0] == rainhaP) && horizontal[1] == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((horizontal[1] ==  torreP || horizontal[1] == rainhaP) && horizontal[0] == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((diagonal[0]   ==  bispoP || diagonal[0]   == rainhaP) && diagonal[2]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((diagonal[1]   ==  bispoP || diagonal[1]   == rainhaP) && diagonal[3]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((diagonal[2]   ==  bispoP || diagonal[2]   == rainhaP) && diagonal[0]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((diagonal[3]   ==  bispoP || diagonal[3]   == rainhaP) && diagonal[1]   == reiB)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else
            {
                libera(diagonal,horizontal, vertical, NULL);
                return true;
            }
        }
    }
    else if(rei == reiP)
    {
        if(peca == torreP)
        {
            if((vertical[0]        ==  torreB || vertical[0]   == rainhaB) && vertical[1]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return Cima;
            }
            else if((vertical[1]   ==  torreB || vertical[1]   == rainhaB) && vertical[0]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return Baixo;
            }
            else if((horizontal[0] ==  torreB || horizontal[0] == rainhaB) && horizontal[1] == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return Direita;
            }
            else if((horizontal[1] ==  torreB || horizontal[1] == rainhaB) && horizontal[0] == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return Esquerda;
            }
            else if((diagonal[0]   ==  bispoB || diagonal[0]   == rainhaB) && diagonal[2]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((diagonal[1]   ==  bispoB || diagonal[1]   == rainhaB) && diagonal[3]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((diagonal[2]   ==  bispoB || diagonal[2]   == rainhaB) && diagonal[0]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((diagonal[3]   ==  bispoB || diagonal[3]   == rainhaB) && diagonal[1]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else
            {
                libera(diagonal,horizontal, vertical, NULL);
                return true;
            }
        }
        else if(peca == peaoP)
        {
            if((vertical[0]        ==  torreB || vertical[0]   == rainhaB) && vertical[1]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((vertical[1]   ==  torreB || vertical[1]   == rainhaB) && vertical[0]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((horizontal[0] ==  torreB || horizontal[0] == rainhaB) && horizontal[1] == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((horizontal[1] ==  torreB || horizontal[1] == rainhaB) && horizontal[0] == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((diagonal[0]   ==  bispoB || diagonal[0]   == rainhaB) && diagonal[2]   == reiP && peao_protege(lin,col,tab,peca))
            {
                libera(diagonal,horizontal, vertical, NULL);
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
                libera(diagonal,horizontal, vertical, NULL);
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
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((diagonal[3]   ==  bispoB || diagonal[3]   == rainhaB) && diagonal[1]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else
            {
                libera(diagonal,horizontal, vertical, NULL);
                return true;
            }
        } 
        else if(peca == bispoP)
        {
            if((vertical[0]        ==  torreB || vertical[0]   == rainhaB) && vertical[1]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((vertical[1]   ==  torreB || vertical[1]   == rainhaB) && vertical[0]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((horizontal[0] ==  torreB || horizontal[0] == rainhaB) && horizontal[1] == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((horizontal[1] ==  torreB || horizontal[1] == rainhaB) && horizontal[0] == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((diagonal[0]   ==  bispoB || diagonal[0]   == rainhaB) && diagonal[2]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return DB_Esquerda;
            }
            else if((diagonal[1]   ==  bispoB || diagonal[1]   == rainhaB) && diagonal[3]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return DB_Direita;
            }
            else if((diagonal[2]   ==  bispoB || diagonal[2]   == rainhaB) && diagonal[0]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return DC_Direita;
            }
            else if((diagonal[3]   ==  bispoB || diagonal[3]   == rainhaB) && diagonal[1]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return DC_Esquerda;
            }
            else
            {
                libera(diagonal,horizontal, vertical, NULL);
                return true;
            }
        }
        else if(peca == rainhaP)
        {
            if((vertical[0]        ==  torreB || vertical[0]   == rainhaB) && vertical[1]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return Cima;
            }
            else if((vertical[1]   ==  torreB || vertical[1]   == rainhaB) && vertical[0]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return Baixo;
            }
            else if((horizontal[0] ==  torreB || horizontal[0] == rainhaB) && horizontal[1] == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return Direita;
            }
            else if((horizontal[1] ==  torreB || horizontal[1] == rainhaB) && horizontal[0] == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return Esquerda;
            }
            else if((diagonal[0]   ==  bispoB || diagonal[0]   == rainhaB) && diagonal[2]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return DB_Esquerda;
            }
            else if((diagonal[1]   ==  bispoB || diagonal[1]   == rainhaB) && diagonal[3]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return DB_Direita;
            }
            else if((diagonal[2]   ==  bispoB || diagonal[2]   == rainhaB) && diagonal[0]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return DC_Direita;
            }
            else if((diagonal[3]   ==  bispoB || diagonal[3]   == rainhaB) && diagonal[1]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return DB_Esquerda;
            }
            else
            {
                libera(diagonal,horizontal, vertical, NULL);
                return true;
            }
        }
        else
        {
            if((vertical[0]        ==  torreB || vertical[0]   == rainhaB) && vertical[1]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((vertical[1]   ==  torreB || vertical[1]   == rainhaB) && vertical[0]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((horizontal[0] ==  torreB || horizontal[0] == rainhaB) && horizontal[1] == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((horizontal[1] ==  torreB || horizontal[1] == rainhaB) && horizontal[0] == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((diagonal[0]   ==  bispoB || diagonal[0]   == rainhaB) && diagonal[2]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((diagonal[1]   ==  bispoB || diagonal[1]   == rainhaB) && diagonal[3]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((diagonal[2]   ==  bispoB || diagonal[2]   == rainhaB) && diagonal[0]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else if((diagonal[3]   ==  bispoB || diagonal[3]   == rainhaB) && diagonal[1]   == reiP)
            {
                libera(diagonal,horizontal, vertical, NULL);
                return false;
            }
            else
            {
                libera(diagonal,horizontal, vertical, NULL);
                return true;
            }
        }
    }
    else
    {
        libera(diagonal,horizontal, vertical, NULL);
        return false;
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
        libera(diag,horiz,vert,cav);
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
        libera(diag,horiz,vert,cav);
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
        libera(diag,horiz,vert,cav);
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
        libera(diag,horiz,vert,cav);
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
        libera(diag,horiz,vert,cav);
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
        libera(diag,horiz,vert,cav);
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
        libera(diag,horiz,vert,cav);
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
                if(lin_ori == 7 && col_ori == 0)
                {
                    RLB = false;
                }
                else if(lin_ori == 7 && col_ori == 7)
                {
                    RCB = false;
                }
                validar = true;
            }
            //Movimento para Direita ⮕
            else if(col_ori == col_des - 1 && lin_ori == lin_des)
            {
                if(lin_ori == 7 && col_ori == 0)
                {
                    RLB = false;
                }
                else if(lin_ori == 7 && col_ori == 7)
                {
                    RCB = false;
                }
                validar = true;
            }
            //Movimento para Baixo ⬇
            else if(col_ori == col_des && lin_ori == lin_des - 1)
            {
                if(lin_ori == 7 && col_ori == 0)
                {
                    RLB = false;
                }
                else if(lin_ori == 7 && col_ori == 7)
                {
                    RCB = false;
                }
                validar = true;
            }
            //Movimento para Esquerda ⬅
            else if(col_ori == col_des + 1 && lin_ori == lin_des)
            {
                if(lin_ori == 7 && col_ori == 0)
                {
                    RLB = false;
                }
                else if(lin_ori == 7 && col_ori == 7)
                {
                    RCB = false;
                }
                validar = true;
            }
            //Movimento para as Verticais distantes
            else if(col_ori == col_des && (lin_ori < lin_des || lin_ori > lin_des) && vertical(lin_ori, col_ori, lin_des, tabuleiro))
            {
                if(lin_ori == 7 && col_ori == 0)
                {
                    RLB = false;
                }
                else if(lin_ori == 7 && col_ori == 7)
                {
                    RCB = false;
                }
                validar = true;
            }
            //Movimento para as Horizontais distantes
            else if(lin_ori == lin_des && (col_ori < col_des || col_ori > col_des) && horizontal(lin_ori, col_ori, col_des, tabuleiro))
            {
                if(lin_ori == 7 && col_ori == 0)
                {
                    RLB = false;
                }
                else if(lin_ori == 7 && col_ori == 7)
                {
                    RCB = false;
                }
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
        libera(diag,horiz,vert,cav);
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
                if(lin_ori == 0 && col_ori == 0)
                {
                    RLP = false;
                }
                else if(lin_ori == 0 && col_ori == 7)
                {
                    RCP = false;
                }
                validar = true;
            }
            //Movimento para Direita ⮕
            else if(col_ori == col_des - 1 && lin_ori == lin_des)
            {
                if(lin_ori == 0 && col_ori == 0)
                {
                    RLP = false;
                }
                else if(lin_ori == 0 && col_ori == 7)
                {
                    RCP = false;
                }
                validar = true;
            }
            //Movimento para Baixo ⬇
            else if(col_ori == col_des && lin_ori == lin_des - 1)
            {
                if(lin_ori == 0 && col_ori == 0)
                {
                    RLP = false;
                }
                else if(lin_ori == 0 && col_ori == 7)
                {
                    RCP = false;
                }
                validar = true;
            }
            //Movimento para Esquerda ⬅
            else if(col_ori == col_des + 1 && lin_ori == lin_des)
            {
                if(lin_ori == 0 && col_ori == 0)
                {
                    RLP = false;
                }
                else if(lin_ori == 0 && col_ori == 7)
                {
                    RCP = false;
                }
                validar = true;
            }
            //Movimento para as Verticais distantes
            else if(col_ori == col_des && (lin_ori < lin_des || lin_ori > lin_des) && vertical(lin_ori, col_ori, lin_des, tabuleiro))
            {
                if(lin_ori == 0 && col_ori == 0)
                {
                    RLP = false;
                }
                else if(lin_ori == 0 && col_ori == 7)
                {
                    RCP = false;
                }
                validar = true;
            }
            //Movimento para as Horizontais distantes
            else if(lin_ori == lin_des && (col_ori < col_des || col_ori > col_des) && horizontal(lin_ori, col_ori, col_des, tabuleiro))
            {
                if(lin_ori == 0 && col_ori == 0)
                {
                    RLP = false;
                }
                else if(lin_ori == 0 && col_ori == 7)
                {
                    RCP = false;
                }
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
        case rainhaB:
        libera(diag,horiz,vert,cav);
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
        libera(diag,horiz,vert,cav);
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
            libera(diag,horiz,vert,cav);
            return false;
        }
        libera(diag,horiz,vert,cav);
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
            else if(verifica_roque(lin_ori,lin_des,col_ori,col_des,tabuleiro,reiB) && roque(lin_ori,col_ori,lin_des,col_des,tabuleiro,reiB))
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
            libera(diag,horiz,vert,cav);
            return false;
        }
        libera(diag,horiz,vert,cav);
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
            else if(verifica_roque(lin_ori,lin_des,col_ori,col_des,tabuleiro,reiB) && roque(lin_ori,col_ori,lin_des,col_des,tabuleiro,reiB))
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
    int* diag = NULL;
    int* horiz = NULL;
    int* vert = NULL;
    int* cav = NULL;


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
                printf("\n---------Aviso---------\n");
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
                printf("\n---------Aviso---------\n");
                printf("Você não pode mover uma peça que protege o rei!");
                continue;
            }
            else if(rodada%2 == 0 && peca >= 8)
            {
                printf("\n---------Aviso---------\n");
                printf("Você tentou movimentar uma peça preta na vez das brancas, tente novamente!\n");
                continue;
            }
            else if(rodada%2 != 0 && peca < 8)
            {
                printf("\n---------Aviso---------\n");
                printf("Você tentou movimentar uma peça branca na vez das pretas, tente novamente!\n");
                continue;
            }
            else
            {
                validar = false;
                printf("Você está movendo %s!\n", nomes[peca]);
            }
            
        }

        if(cancelar)
        {
            printf("\n---------Aviso---------\n");
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
            int rei = reis(peca);
            int* diag = peca_diagonal(lin_des,col_des,tab,rei);
            int* horiz = peca_horizontal(lin_des,col_des,tab,rei);
            int* vert = peca_vertical(lin_des,col_des,tab,rei);
            int* cav = peca_cavalo(lin_des, col_des, tab);

            int resultado_sistema = sistema(peca, col_ori, lin_ori, lin_des, col_des, tab);
            int resultado_rei = verifica_ameaca_rei(horiz, diag, vert, cav, rei);

            if(lin_des == -1 && col_des == -1)
            {
                cancelar = true;
                validar = false;
            }
            else if(!resultado_sistema)
            {
                printf("\n---------Aviso---------\n");
                printf("Ação inválida!! Tente novamente.\n");
                printf("Funcão verifica roque: %d\n",verifica_roque(lin_ori,lin_des,col_ori,col_des,tab,rei));
                printf("Funcão roque: %d\n", roque(lin_ori,col_ori,lin_des,col_des,tab,rei));
                printf("Funcão verifica ameaça rei: %d\n",resultado_rei);
            }
            else
            validar = false;
            libera(diag,horiz,vert,cav);
        }

        if(cancelar)
        {
            printf("\n---------Aviso---------\n");
            printf("Ação cancelada\n\n");
            continue;
        } 
        break;
    }
    
    
    cor = cores(col_ori,lin_ori);
    tab[lin_des*8+col_des] = tab[lin_ori*8+col_ori];
    tab[lin_ori*8+col_ori] = cor;
}
