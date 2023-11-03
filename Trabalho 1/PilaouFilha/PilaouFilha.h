#ifndef PILAOUFILHA_H_INCLUDED
#define PILAOUFILHA_H_INCLUDED

#define SUCESSO 1
#define ERRO 0

#include <stdio.h>
#include <stdlib.h>

//estrutura de pilha

typedef int TipoChave;

typedef struct {
    TipoChave chave;
} TipoItem;

typedef struct TipoNo {
    TipoItem item;
    struct TipoNo *prox; // pode ter *ant tambem
} TipoNo;


typedef struct TipoNo* TipoApontador;

typedef struct {
    TipoApontador inicio;
    TipoApontador fim;
} TipoFila;


typedef struct {
    TipoApontador topo;
} TipoPilha;


int inicializarPilha(TipoPilha *P);
int pilhaVazia(TipoPilha *P);
int empilhar(TipoPilha *P, TipoItem I);
TipoChave desempilhar (TipoPilha *P);

int inicializarFila (TipoFila *f);
int filaVazia(TipoFila *F);
int  enfileirar(TipoFila *F , TipoItem I);
TipoChave desenfileirar(TipoFila *F) ;

void verificarEstrutura(int n_operacoes, char operacoes[], TipoChave chaves[]);

void liberarPilha(TipoPilha *P);
void liberarFila(TipoFila *F);

#endif // PILAOUFILHA_H_INCLUDED

