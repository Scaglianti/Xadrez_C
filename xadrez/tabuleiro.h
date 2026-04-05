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

int cores(int col,int lin);
void imprimirtabuleiro(int *pecas);
int *criartabuleiro();

int verificadiagonal(int lin_ori, int col_ori, int lin_des, int col_des);
int horizontal(int lin_ori, int col_ori, int col_des, int *tab);
int diagonal(int lin_ori, int col_ori, int lin_des, int col_des, int *tab);
int vertical(int lin_ori, int col_ori, int lin_des, int *tab);
int sistema(int peca, int col_ori, int lin_ori, int lin_des, int col_des, int *tabuleiro);

void lermovimento(int *val_col,int *val_lin);
void movimento(int *tab);

#endif