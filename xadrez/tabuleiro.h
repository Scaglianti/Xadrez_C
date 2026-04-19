#ifndef TABULEIRO_H
#define TABULEIRO_H

typedef enum
{
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
}peca;
extern const char* nomes[];

int cores(int col,int lin);
void imprimirtabuleiro(int *pecas);
int *criartabuleiro();

int peca_horizontal(int lin, int col, int *tab, int rei);
int peca_diagonal(int lin, int col, int *tab, int rei);
int peca_vertical(int lin, int col, int *tab, int rei);
int peca_cavalo(int lin, int col, int* tab);


int verificadirecao(int lin_ori, int col_ori, int lin_des, int col_des);
int verificadiagonal(int lin_ori, int col_ori, int lin_des, int col_des);
int horizontal(int lin_ori, int col_ori, int col_des, int *tab);
int diagonal(int lin_ori, int col_ori, int lin_des, int col_des, int *tab);
int vertical(int lin_ori, int col_ori, int lin_des, int *tab);
int sistema(int peca, int col_ori, int lin_ori, int lin_des, int col_des, int *tabuleiro);

void lermovimento(int *val_col,int *val_lin);
int verificapeca(int* tab, int lin_ori, int col_ori);
void movimento(int *tab, int rodada);

#endif