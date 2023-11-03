#include <stdio.h>
#define PINOS 30
typedef int TipoChave;
typedef int TipoApontador;

typedef struct {
    TipoChave chave;
    // char nome[50]; // Voc� pode adicionar um campo "nome" se necess�rio
} TipoItem;

typedef struct {
    TipoItem itens[PINOS];
    TipoApontador ultimo; // �ltimo = topo
} TipoPilha;

void CriarPilha(TipoPilha *P) {
    P->ultimo = -1;
}

int PilhaVazia(TipoPilha *P) {
    return P->ultimo == -1;
}

int PilhaCheia(TipoPilha *P) {
    return P->ultimo == PINOS - 1;
}

int InserirPilha(TipoPilha *P, TipoItem I) {
    if (PilhaCheia(P)) {
        printf("Pilha cheia, n�o foi poss�vel inserir!\n");
        return 1;
    }
    P->ultimo++;
    P->itens[P->ultimo] = I;
    return 0;
}

int RemoverPilha(TipoPilha *P, TipoChave C) {
    if (!PilhaVazia(P)) {
        P->ultimo--;
        return 0;
    } else {
        return 1;
    }
}

int Hanoi(int n, TipoPilha *Orig, TipoPilha *Dest, TipoPilha *Temp) {
    if (n == 1) {
        TipoItem disco = Orig->itens[Orig->ultimo];
        RemoverPilha(Orig, disco.chave);
        InserirPilha(Dest, disco);
        return 1; // Um movimento foi realizado
    } else {
        int movimentos = 0;

        // Movimento dos n-1 discos superiores para o pino Tempor�rio
        movimentos += Hanoi(n - 1, Orig, Temp, Dest);

        // Movimento do maior disco da Origem para o Destino
        TipoItem disco = Orig->itens[Orig->ultimo];
        RemoverPilha(Orig, disco.chave);
        InserirPilha(Dest, disco);
        movimentos++; // Incrementa o contador de movimentos

        // Movimento dos n-1 discos superiores do pino Tempor�rio para o Destino
        movimentos += Hanoi(n - 1, Temp, Dest, Orig);

        return movimentos; // Retorna o n�mero total de movimentos
    }
}

int main() {
    int npinos;
    TipoPilha Orig, Dest, Temp;
    TipoItem torre[PINOS];

    scanf("%d", &npinos);
    if (npinos == 0) {
        return 0; // Sai imediatamente se n�o houver discos para mover
    }
    CriarPilha(&Orig);
    int j = npinos;
    for (int i = 0; i < npinos; i++) {
        torre[i].chave = j; // Preenche a torre com discos de tamanhos diferentes
        j--;
    }
    CriarPilha(&Dest);
    CriarPilha(&Temp);

    // Chama a fun��o Hanoi para resolver o problema e obt�m o n�mero de movimentos
    int cont = Hanoi(npinos, &Orig, &Dest, &Temp);

    printf("Teste %d\n", npinos); // N�mero do teste baseado no n�mero de pinos
    printf("%d\n", cont); // N�mero de movimentos
    printf("\n");

    return 0;
}
