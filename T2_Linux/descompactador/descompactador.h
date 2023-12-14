#ifndef DESCOMPACTADOR_H_INCLUDED
#define DESCOMPACTADOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <windows.h>

#define TAM 256

typedef struct TipoNo* TipoApontador;
typedef unsigned char TipoChave;

typedef struct TipoNo { //mesma estrutura para arvore ou lista
    TipoChave chave;
    int frequencia;
    TipoApontador esquerda; //so usa no caso de arvore
    TipoApontador direita; //so usa no caso de arvore
    TipoApontador proximo; //so usa no caso de lista
} TipoNo;

typedef struct { //estrutura de lista encadeada
    TipoNo *inicio;
    int tamanho;
}TipoLista;

typedef struct {
    size_t tamanho;
    char extensao[256];
} InfoExtensao;

InfoExtensao lerInfoExtensao(FILE *arquivoComp);

void decodificarEAtualizar(FILE *arquivoDescomp, TipoNo *raiz);

// Fun��o para descompactar
int descompactarEAtualizar(FILE *arquivoComp, FILE *arquivoDescomp, TipoNo *arvore);

// Fun��o para ler a �rvore de Huffman do arquivo compactado
TipoNo *lerArvoreCompactada(FILE *arquivoComp);

// Fun��o para liberar a �rvore de Huffman
void free_arvore(TipoNo *raiz);
void decodificarEImprimir(FILE *arquivoComp, TipoNo *arvore);
int eh_bit_um(unsigned char byte, int i);
#endif // DESCOMPACTADOR_H_INCLUDED
