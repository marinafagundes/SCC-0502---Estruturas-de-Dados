#include <stdio.h>
#include <stdlib.h>
#include "PilaouFilha.h"

//funcoes
int inicializarPilha(TipoPilha *P){
    P->topo = NULL;
    return SUCESSO;
}

int pilhaVazia(TipoPilha *P){
    return P->topo == NULL;
}

int empilhar(TipoPilha *P, TipoItem I){
    TipoApontador p = (TipoApontador) malloc(sizeof(TipoNo));
    if (p == NULL) { //erro de alocacao
        return ERRO;
    }

    p->item = I;

    if (pilhaVazia(P)) { //primeiro item
        p->prox = NULL;
        P->topo = p;
    } else {
        p->prox = P->topo;
        P->topo = p; // insere no inicio
    }
    return SUCESSO;
}

TipoChave desempilhar(TipoPilha *P) {
    if (pilhaVazia(P)) {
        return ERRO; //nao pode remover de uma pilha vazia
    }

    TipoApontador p = P->topo;
    TipoChave chave = p->item.chave;
    P->topo = P->topo->prox;
    free(p); //libera memoria do no desempilhado

    //se a pilha estiver vazia apos a remocao, inicialize a pilha
    if (P->topo == NULL) {
        inicializarPilha(P);
    }

    return chave;
}

int inicializarFila (TipoFila *F){
    F->inicio = NULL;
    F->fim = NULL;
    return SUCESSO;
 }

int filaVazia(TipoFila *F) {
    return F->inicio == NULL;
}

int enfileirar(TipoFila *F, TipoItem I) {
    TipoApontador p = (TipoApontador)malloc(sizeof(TipoNo));
    if (p == NULL) { //erro de alocacao
        return ERRO;
    }

    p->item = I;
    p->prox = NULL;

    if (filaVazia(F)) { //primeiro item
        F->inicio = p;
    } else {
        F->fim->prox = p;
    }

    F->fim = p;
    return SUCESSO;
}

TipoChave desenfileirar(TipoFila *F) {
    if (filaVazia(F)) { //nao pode desenfileirar de uma fila vazia
        return ERRO;
    }

    TipoApontador p = F->inicio;
    TipoChave chave = p->item.chave;
    F->inicio = F->inicio->prox;
    free(p);

    if (F->inicio == NULL) {
        F->fim = NULL;
    }

    return chave;
}

void verificarEstrutura(int n_operacoes, char operacoes[], TipoChave chaves[]) {
    TipoPilha P;
    TipoFila F;
    inicializarPilha(&P);
    inicializarFila(&F);

    int eh_fila = 1, eh_pilha = 1; //se for igual a 1, quer dizer que e pilha ou fila. Se for igual a zero, nao e pilha ou fila

    for (int i = 0; i < n_operacoes; i++) {
        if (operacoes[i] == 'i') {
            TipoItem novo_item;
            novo_item.chave = chaves[i];
            empilhar(&P, novo_item);
            enfileirar(&F, novo_item);
        } else if (operacoes[i] == 'r') {
            TipoChave chave_pilha = desempilhar(&P);
            TipoChave chave_fila = desenfileirar(&F);

            if (chave_pilha != chaves[i]) { //o ultimo item inserido deve ser o item removido, senao nao e pilha (estrutura LIFO)
                eh_pilha = 0;
            }
            if (chave_fila != chaves[i]) { //o primeiro item inserido deve ser o item removido, senao nao e fila (estrutura FIFO)
                eh_fila = 0;
            }
        }
    }

    if (eh_pilha == 1 && eh_fila == 1) {
        printf("indefinido\n");
    } else if (eh_pilha == 1) {
        printf("pilha\n");
    } else if (eh_fila == 1) {
        printf("fila\n");
    } else {
        printf("impossivel\n");
    }
}
void liberarPilha(TipoPilha *P) { //evitar vazamento de memoria
    while (!pilhaVazia(P)) {
        TipoApontador temp = P->topo;
        P->topo = P->topo->prox;
        free(temp);
    }
}

void liberarFila(TipoFila *F) { //evitar vazamento de memoria
    while (!filaVazia(F)) {
        TipoApontador temp = F->inicio;
        F->inicio = F->inicio->prox;
        free(temp);
    }
    F->fim = NULL;
}
