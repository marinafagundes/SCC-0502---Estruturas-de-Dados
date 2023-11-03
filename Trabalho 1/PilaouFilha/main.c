#include <stdio.h>
#include <stdlib.h>
#include "PilaouFilha.h"

int main(void) {
    TipoPilha P;
    TipoFila F;
    inicializarPilha(&P);
    inicializarFila(&F);
    
    int n;
    scanf("%d", &n);
    
    if (n < 1 || n > 100){ //verificacao 1
        return ERRO;
    } else {
        for (int i = 0; i < n; i++) {
            int n_operacoes;
            scanf("%d", &n_operacoes);
            
            char operacoes[n_operacoes];
            int chaves[n_operacoes];
            
            if (n_operacoes < 2 || n_operacoes > 100){ //verificacao 2
                return ERRO;
            } else {
                for (int j = 0; j < n_operacoes; j++) {
                    scanf(" %c %d", &operacoes[j], &chaves[j]);
                }
                verificarEstrutura(n_operacoes, operacoes, chaves);
            }
            
        }
    }
        
    liberarPilha(&P);
    liberarFila(&F);
    return 0;
}

