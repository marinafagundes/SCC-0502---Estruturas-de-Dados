#ifndef AVL_H
#define AVL_H

#define SUCESSO 1
#define NAO_EXISTE -1
#define JA_EXISTE -2
#define INVALIDO -3
#define CHEIA -4
#define VAZIA -5

typedef int t_chave;

typedef struct t_no *t_apontador;
typedef struct t_no {
    t_apontador esq, dir;
    t_chave chave;
    int h;
} t_no;


typedef t_apontador t_avl;


void limpar(t_avl *t);
void inicializar(t_avl *t);
t_chave pesquisar(t_chave c, t_avl *t);
int inserir(t_chave c, t_avl *t);
int remover(t_chave c, t_avl *t);
int vazia(t_avl *t);
void em_ordem(t_avl *t);

// alterar

#endif
