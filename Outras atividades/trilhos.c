#include <stdio.h>
#define MAX_VAGOES 1000
typedef int TipoChave;
typedef int TipoApontador;

typedef struct {
    TipoChave chave;
    // char nome[50]; // Você pode adicionar um campo "nome" se necessário
} TipoItem;

typedef struct {
    TipoItem itens[MAX_VAGOES];
    TipoApontador ultimo; // último = topo
} TipoPilha;

void CriarPilha(TipoPilha *P) {
    P->ultimo = -1;
}

int PilhaVazia(TipoPilha *P) {
    return P->ultimo == -1;
}

int PilhaCheia(TipoPilha *P) {
    return P->ultimo == MAX_VAGOES - 1;
}

int InserirPilha(TipoPilha *P, TipoItem I) {
    if (PilhaCheia(P)) {
        printf("Pilha cheia, não foi possível inserir!\n");
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
        printf("Pilha vazia, não é possível remover!\n");
        return 1;
    }
}

int main() {
    int nvagoes;
    TipoPilha estacao;
    TipoItem ordemDesejada[MAX_VAGOES];
    int ordemAtual;

    while (1) {
        scanf("%d", &nvagoes);
        if (nvagoes == 0) {
            break; // Fim do input
        }

        CriarPilha(&estacao);
        ordemAtual = 1; // sempre comeca assim: 1, 2, 3, 4, 5... 1000

        for (int i = 0; i < nvagoes; i++) {
            scanf("%d", &ordemDesejada[i].chave);//ordem inserida
        }

        int possivel = 1;//se nao for possivel, muda para 0

        for (int i = 0; i < nvagoes; i++) {
            while (ordemAtual <= nvagoes && ordemDesejada[i].chave != estacao.itens[estacao.ultimo].chave) {
                TipoItem novo_vagao;
                novo_vagao.chave = ordemAtual;
                if (InserirPilha(&estacao, novo_vagao)) { // se a pilha estiver cheia
                    possivel = 0;
                    break;
                }
                ordemAtual++; // se a pilha nao estiver cheia, atualiza a ordem
            }

            if (ordemDesejada[i].chave == estacao.itens[estacao.ultimo].chave) {
                RemoverPilha(&estacao, estacao.itens[estacao.ultimo].chave);
            } else {
                possivel = 0;
                break;
            }
        }

        if (possivel) { // se possivel = 1
            printf("Yes\n");
        } else {
            printf("No\n");
        }

        if (nvagoes < nvagoes - 1) {
            printf("\n"); // Linha em branco entre os casos de teste
        }
    }

    return 0;
}
