#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <windows.h>
#include "descompactador.h"

// Fun��o para ler informa��es da extens�o do arquivo compactado
InfoExtensao lerInfoExtensao(FILE *arquivoComp) {
    InfoExtensao info;
    rewind(arquivoComp);
    fread(&info.tamanho, sizeof(size_t), 1, arquivoComp);

    info.tamanho = info.tamanho + 1;//para acrescentar o caracter nulo no final

    fread(info.extensao, sizeof(char), info.tamanho, arquivoComp);
    info.extensao[info.tamanho -1] = '\0'; // Corrigir o �ndice para definir o caractere nulo

    return info;
}

// Fun��o para decodificar um �nico caractere
void decodificarEAtualizar(FILE *arquivoDescomp, TipoNo *raiz) {
    int bit;
    TipoNo *aux = raiz;
    char temp[2];

    while (fread(&bit, sizeof(int), 1, arquivoDescomp) > 0) {
        if (bit == '0')
            aux = aux->esquerda;
        else
            aux = aux->direita;

        if (aux->esquerda == NULL && aux->direita == NULL) {
            temp[0] = aux->chave;
            temp[1] = '\0';

            // Atualizar o arquivo descompactado com o caractere decodificado
            fwrite(temp, sizeof(char), 1, arquivoDescomp);

            aux = raiz;
        }
    }
}

// Fun��o para descompactar e decodificar o texto e escrever no arquivo descompactado
int descompactarEAtualizar(FILE *arquivoComp, FILE *arquivoDescomp, TipoNo *arvore) {
    if (!arquivoComp || !arvore) {
        printf("\nERRO: Arquivo compactado ou �rvore inv�lidos.\n");
        return 0;
    }

    unsigned char bit;
    TipoNo *noAtual = arvore;

    // L� as informa��es da extens�o uma vez
    InfoExtensao info = lerInfoExtensao(arquivoComp);

    // Imprime informa��es sobre a extens�o antes do loop
    printf("Extensao descompactada: %s\n", info.extensao);

    while (fread(&bit, sizeof(unsigned char), 1, arquivoComp) > 0) {
        for (int i = 7; i >= 0; i--) {
            if (bit & (1 << i)) {
                noAtual = noAtual->direita;
            } else {
                noAtual = noAtual->esquerda;
            }

            if (noAtual->esquerda == NULL && noAtual->direita == NULL) {
                // Encontrou um caractere, decodifica e escreve no arquivo
                char caractereDecodificado = noAtual->chave;
                if (fwrite(&caractereDecodificado, sizeof(char), 1, arquivoDescomp) != 1) {
                    printf("\nERRO: Falha ao escrever no arquivo descompactado.\n");
                    return 0;
                }
                noAtual = arvore; // Reinicia a busca a partir da raiz
            }
        }
    }

    return 1; // Sucesso
}


TipoNo *construirArvore(FILE *arquivo) {
    TipoNo *no = malloc(sizeof(TipoNo));
    fread(no, sizeof(TipoNo), 1, arquivo);

    if (no->esquerda != NULL) {
        no->esquerda = construirArvore(arquivo);
    }
    if (no->direita != NULL) {
        no->direita = construirArvore(arquivo);
    }

    return no;
}


TipoNo *lerArvoreCompactada(FILE *arquivoComp) {
    // Verificar se o arquivo est� vazio
    fseek(arquivoComp, 0, SEEK_END);
    if (ftell(arquivoComp) == 0) {
        return NULL;
    }

    // Voltar ao in�cio do arquivo
    fseek(arquivoComp, 0, SEEK_SET);

    // Construir e retornar a �rvore
    return construirArvore(arquivoComp);
}


void free_arvore(TipoNo *raiz) {
    // Implemente a l�gica para liberar a mem�ria da �rvore
    // Percorra a �rvore e libere cada n� recursivamente

    if (raiz != NULL) {
        free_arvore(raiz->esquerda);
        free_arvore(raiz->direita);
        free(raiz);
    }
}
