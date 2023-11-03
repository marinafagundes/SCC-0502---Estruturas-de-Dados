#include <stdio.h>
#include <string.h>

#include "ListaEstatica.h"

int main(void) {

    t_lista l1, l2;
    t_elemento e;
    int n, m;

    inicializar(&l1);
    inicializar(&l2);

    printf("Informe a quantidade de elementos para l1: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Informe o elemento %d de l1: ", i + 1);
        scanf("%d", &e.chave);
        inserir(e, &l1);
    }

    printf("Lista l1: ");
    imprimir(&l1);

    printf("Informe a chave para fazer o split: ");
    scanf("%d", &m);
    split(&l1, m, &l2);

    printf("Lista l1 após o split: ");
    imprimir(&l1);
    printf("Lista l2 após o split: ");
    imprimir(&l2);
}
