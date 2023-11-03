#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SKIPLIST_H_INCLUDED
#define SKIPLIST_H_INCLUDED

#define MAX_NOME 11
#define MAX_TELEFONE 10
#define SUCESSO 1
#define ERRO 0

//implementacao das estruturas baseada no modo realizado em sala, mas a implementacao das funcoes foi baseada no livro Algoritmos e Estruturas de Dados em linguagem CM de Andre Ricardo Backes (adaptado para essa estrutura)

//estruturas: contato, no, apontador e agenda/skiplist
typedef struct TipoContato{
	char nome[MAX_NOME];
	char telefone[MAX_TELEFONE];
}TipoContato;

typedef struct TipoNo** TipoApontador;

typedef struct TipoNo{
	TipoContato contato;
	TipoApontador proximo;
}TipoNo;

typedef struct TipoSkipList{
	int nivelMAX;
	float P;
	int nivel;
	TipoNo *cabecalho;
}TipoSkipList;

//funcoes usadas no problema
TipoNo *criarNo(TipoContato contato, int nivel);
TipoSkipList* criarSkipList(int nivelMAX, float P);
void liberarContato(TipoNo *no);
void liberarSkipList(TipoSkipList *SL);
int vaziaSkipList(TipoSkipList *SL);
int sorteiaNivel(TipoSkipList *SL);
int inserirSkipList(TipoSkipList* SL, TipoContato contato);
int removerSkipList(TipoSkipList *SL, char nome[MAX_NOME]);
TipoNo* buscarSkipList(TipoSkipList *SL, char nome[MAX_NOME]);
TipoNo* buscarAuxiliarSkipList(TipoSkipList* SL, char nome[MAX_NOME]);
int alterarSkipList(TipoSkipList* SL,TipoContato contato);

//funcoes complementares do livro, estao comentadas porque nao serao usadas
//int tamanhoSkipList(TipoSkipList *SL);
//void imprimirSkipList(TipoSkipList *SL);

#endif // SKIPLIST_H_INCLUDED
