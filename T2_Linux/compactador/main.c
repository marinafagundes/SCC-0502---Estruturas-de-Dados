#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <windows.h>
#include "compactador.h"

int main(int argc, char *argv[]) {
    const char *ext = "comp";
    if (argc <= 2) {
        printf("\nUso: %s <nome_do_arquivo>\n", argv[0]);
        if (argc != 2) {
            return 0;
        }
    }

    const char *nomeArquivo = argv[1];
    char nomeSemExtensao[256];
    char extensao[256];
    separarNomeExtensao(nomeArquivo, nomeSemExtensao, extensao);

    printf("\nNome: %s\n", nomeSemExtensao);
    printf("\nExtensao: %s\n", extensao);

    unsigned char *texto;
    unsigned int tabela_frequencia[TAM]; //tabela de frequências
    TipoLista lista;
    TipoNo *arvore;
    int colunas, tam;
    char **dicionario;
    char *codificado;

    //retire ou comente a linha a seguir para executar no Linux
    //SetConsoleOutputCP(65001);

    tam = descobrir_tamanho(nomeArquivo);
    printf("\nQuantidade: %d\n", tam);

    texto = calloc(tam + 2, sizeof(unsigned char));
    ler_texto(nomeArquivo, texto, tam);

    //printf("\nTEXTO:\n%s\n", texto); para caso quisesse imprimir o texto


    //tabela de frequência
    inicializa_tabela_frequencia(tabela_frequencia);
    preenche_tabela_frequencia(texto, tabela_frequencia);
    //imprime_tab_frequencia(tabela_frequencia);

    //Lista Encadeada Ordenada
    criar_lista(&lista);
    preencher_lista(tabela_frequencia, &lista);
    //imprimir_lista(&lista);

    //Montar a Árvore de Huffman
    arvore = montar_arvore(&lista);
    //printf("\n\tArvore de Huffam\n");
    //imprimir_arvore(arvore, 0);

    //Montar o dicionário
    colunas = altura_arvore(arvore) + 1;
    dicionario = alocar_dicionario(colunas);
    gerar_dicionario(dicionario, arvore, "", colunas);
    //imprime_dicionario(dicionario);

    //Codificar
    codificado = codificar(dicionario, texto);
    //printf("\n\tTexto codificado: %s\n", codificado);

    //Compactar
    compactar(codificado, nomeSemExtensao, extensao);

    free(texto);
    free(codificado);
    free_dicionario(dicionario, colunas);
    free_arvore(arvore);

    return 0;
}
