#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <windows.h>
#include "descompactador.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo_compactado.comp>\n", argv[0]);
        return 0;
    }

    const char *nomeArquivoComp = argv[1];

    FILE *arquivoComp = fopen(nomeArquivoComp, "rb");

    if (arquivoComp) {
        // Salvar a posi��o atual no arquivo compactado
        long posicaoOriginal = ftell(arquivoComp);

        // Ler a �rvore de Huffman do arquivo compactado
        TipoNo *arvore = lerArvoreCompactada(arquivoComp);

        if (arvore) {
            // Ler informa��es da extens�o do arquivo compactado
            InfoExtensao info = lerInfoExtensao(arquivoComp);

            // Restaurar a posi��o original no arquivo compactado
            fseek(arquivoComp, posicaoOriginal, SEEK_SET);

            // Configurar o nome do arquivo de sa�da
            char nomeSaida[256];
            int len = strlen(nomeArquivoComp);
            int extensaoLen = strlen(info.extensao);
            snprintf(nomeSaida, sizeof(nomeSaida), "%.*s.%s", len - 5, nomeArquivoComp, info.extensao);

            FILE *arquivoDescomp = fopen(nomeSaida, "wb");

            if (arquivoDescomp) {
                // Descompactar, decodificar e escrever no arquivo de sa�da
                if (descompactarEAtualizar(arquivoComp, arquivoDescomp, arvore)) {
                    // Imprimir informa��es
                    printf("\nDescompactacao concluida. Arquivo descompactado e decodificado salvo como %s\n", nomeSaida);
                } else {
                    printf("\nERRO durante descompactacao e decodificacao.\n");
                }

                // Fechar os arquivos
                fclose(arquivoDescomp);
            } else {
                printf("\nERRO ao criar arquivo de saida em descompactarEAtualizar\n");
            }

            // Liberar mem�ria
            free_arvore(arvore);
        } else {
            printf("\nERRO ao ler a arvore de Huffman do arquivo compactado\n");
        }

        // Fechar o arquivo compactado
        fclose(arquivoComp);
    } else {
        printf("\nERRO ao abrir o arquivo compactado em descompactarEAtualizar\n");
    }

    return 0;
}
