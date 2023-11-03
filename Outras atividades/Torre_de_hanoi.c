#include <stdio.h>
#include <stdlib.h>

#define MAX_DISCOS 10

typedef struct {
    int array[MAX_DISCOS];
    int topo;
} Pilha;

void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1;
}

int estaVazia(Pilha *pilha) {
    return pilha->topo == -1;
}

void empilhar(Pilha *pilha, int valor) {
    pilha->topo++;
    pilha->array[pilha->topo] = valor;
}

int desempilhar(Pilha *pilha) {
    int valor = pilha->array[pilha->topo];
    pilha->topo--;
    return valor;
}

void mostrarPilha(Pilha *pilha) {
    for (int i = pilha->topo; i >= 0; i--) {
        printf("%d ", pilha->array[i]);
    }
    printf("\n");
}

int movimentoValido(Pilha *origem, Pilha *destino) {
    if (estaVazia(origem)) {
        printf("Origem vazia. Escolha outra torre.\n");
        return 0;
    } else if (!estaVazia(destino) && origem->array[origem->topo] > destino->array[destino->topo]) {
        printf("Movimento inválido. Disco maior não pode ser colocado sobre um menor.\n");
        return 0;
    }
    return 1;
}

int main() {
    int numDiscos, origem, destino, movimentos = 0;
    Pilha torre[3];

    printf("Digite o número de discos (entre 3 e 10): ");
    scanf("%d", &numDiscos);

    if (numDiscos < 3 || numDiscos > 10) {
        printf("Número de discos inválido. O número de discos deve estar entre 3 e 10.\n");
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        inicializarPilha(&torre[i]);
    }

    for (int i = numDiscos; i >= 1; i--) {
        empilhar(&torre[0], i);
    }

    printf("Estado inicial das torres:\n");
    for (int i = 0; i < 3; i++) {
        printf("Torre %d: ", i + 1);
        mostrarPilha(&torre[i]);
    }

    while (!estaVazia(&torre[0]) || !estaVazia(&torre[1])) {
        printf("Movimento #%d: Escolha a torre de origem (1, 2 ou 3): ", movimentos + 1);
        scanf("%d", &origem);
        printf("Movimento #%d: Escolha a torre de destino (1, 2 ou 3): ", movimentos + 1);
        scanf("%d", &destino);

        if (origem < 1 || origem > 3 || destino < 1 || destino > 3) {
            printf("Torre inválida. Escolha entre 1, 2 ou 3.\n");
            continue;
        }

        origem--;
        destino--;

        if (movimentoValido(&torre[origem], &torre[destino])) {
            int disco = desempilhar(&torre[origem]);
            empilhar(&torre[destino], disco);
            movimentos++;

            printf("Estado atual das torres:\n");
            for (int i = 0; i < 3; i++) {
                printf("Torre %d: ", i + 1);
                mostrarPilha(&torre[i]);
            }
        } else {
            printf("Jogada inválida. Tente novamente.\n");
        }
    }

    printf("Parabéns! Você completou o jogo em %d movimentos.\n", movimentos);

    return 0;
}
