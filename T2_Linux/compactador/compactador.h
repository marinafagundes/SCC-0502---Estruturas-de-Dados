#ifndef COMPACTADOR_H_INCLUDED
#define COMPACTADOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

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


void inicializa_tabela_frequencia (unsigned int tabela[]);
void preenche_tabela_frequencia(unsigned char texto[], unsigned int tabela[]);
void imprime_tabela_frequencia(unsigned int tabela[]);

void criar_lista (TipoLista *lista);
void inserir_ordenado_lista (TipoLista *lista, TipoNo *no);
void preencher_lista(unsigned int tab[], TipoLista *lista);
void imprimir_lista(TipoLista *lista);

TipoNo* remover_no_inicio(TipoLista *lista);
TipoNo* montar_arvore(TipoLista *lista);
void imprimir_arvore(TipoNo *raiz, int tamanho);

int altura_arvore(TipoNo *raiz);
char** alocar_dicionario(int colunas);
void gerar_dicionario(char **dicionario, TipoNo *raiz, char *caminho, int colunas);
void imprimir_dicionario(char **dicionario);

int calcular_tamanho_string(char **dicionario, unsigned char *texto);
char* codificar(char **dicionario, unsigned char *texto);

void separarNomeExtensao(const char *nomeArquivo, char *nome, char *extensao);

void compactar(unsigned char str[], char *nomeArquivo, char *extensao);
int descobrir_tamanho(const char *nomeArquivo);
void ler_texto(const char *nomeArquivo, unsigned char *texto, int tam);

void free_dicionario(char **dicionario, int colunas);

void free_arvore(TipoNo *raiz);

#endif // COMPACTADOR_H_INCLUDED
