#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <windows.h>
#include "compactador.h"

//tabela de frequência
void inicializa_tabela_frequencia(unsigned int tab[]){ //inicializa a tabela de frequência
    int i;
    for(i = 0; i < TAM; i++){
        tab[i] = 0; //todos os elementos são iniciados com 0
    }
}

void preenche_tabela_frequencia(unsigned char texto[], unsigned int tab[]){ //preenche a tabela de frequências com as respectivas frequências de cada elemento
    int i = 0;

    while(texto[i] != '\0'){
        tab[texto[i]]++;
        i++;
    }
}

void imprime_tabela_frequencia(unsigned int tab[]){ //imprime a tabela de frequências
    int i;

    printf("\tTABELA DE FREQUENCIA\n");
    for(i = 0; i < TAM; i++){
        if(tab[i] > 0){ //imprime apenas quem tem frequência maior do que zero
            printf("\t%d = %u = %c\n", i, tab[i], i);
        }
    }
}

//Lista Encadeada Ordenada

void criar_lista(TipoLista *lista){ //inicializa a linha
    lista->inicio = NULL; //inicio aponta para NULL
    lista->tamanho = 0; //a lista está vazia, portanto, tamanho = 0
}

void inserir_ordenado_lista(TipoLista *lista, TipoNo *no){ //insere ordenado na lista
    TipoNo *aux;
    // a lista está vazia?
    if(lista->inicio == NULL){
        lista->inicio = no; //se a lista estiver vazia, insere o nó no início
    }
    // tem frequência menor que o início da lista
    else if(no->frequencia < lista->inicio->frequencia){ //insere o nó no início por causa da ordem
        no->proximo = lista->inicio;
        lista->inicio = no;
    }
    else{ //insere o nó na posição correta
        aux = lista->inicio;
        while(aux->proximo && aux->proximo->frequencia <= no->frequencia)
            aux = aux->proximo;
        no->proximo = aux->proximo;
        aux->proximo = no;
    }
    lista->tamanho++;
}

void preencher_lista(unsigned int tab[], TipoLista *lista){ //prenche a lista ordenada
    int i;
    TipoNo *novo;
    for(i = 0; i < TAM; i++){
        if(tab[i] > 0){
            novo = malloc(sizeof(TipoNo));
            if(novo){ //se novo existe, ou seja, se a alocação foi bem sucedida
                novo->chave = i;
                novo->frequencia = tab[i];
                novo->direita = NULL;
                novo->esquerda = NULL;
                novo->proximo = NULL;

                inserir_ordenado_lista(lista, novo); //insere o nó ordenado
            }
            else{
                printf("\tERRO ao alocar memoria em preencher_lista!\n");
                break;
            }
        }
    }
}

void imprimir_lista(TipoLista *lista){ //imprime a lista ordenada
    TipoNo *aux = lista->inicio;

    printf("\n\tLista ordenada: Tamanho: %d\n", lista->tamanho); //imprime o tamanho da lista
    while(aux){ //enquanto o aux não é nulo, ou seja, enquanto existe um aux
        printf("\tCaracter: %c Frequência: %d\n", aux->chave, aux->frequencia); //imprime caracter/chave e sua frequência
        aux = aux->proximo;
    }
}

//Montar a Árvore de Huffman

TipoNo* remover_no_inicio(TipoLista *lista){ //remover do início da lista
    TipoNo *aux = NULL;

    if(lista->inicio){ //se existe início, ou seja, se a lista não está vazia
        aux = lista->inicio;
        lista->inicio = aux->proximo;
        aux->proximo = NULL;
        lista->tamanho--;
    }

    return aux;
}

TipoNo* montar_arvore(TipoLista *lista){ //montar a árvore de Huffman
    TipoNo *primeiro, *segundo, *novo;
    while(lista->tamanho > 1){ //se existe mais do que um nó na lista, tem que remover dois nós para montar a árvore
        primeiro = remover_no_inicio(lista);
        segundo = remover_no_inicio(lista);
        novo = malloc(sizeof(TipoNo));

        if(novo){ //se a alocação dinâmica de novo deu certo
            novo->chave = '+'; //caracter aleatório, para indicar a união dos dois nós
            novo->frequencia = primeiro->frequencia + segundo->frequencia;
            novo->esquerda = primeiro;
            novo->direita = segundo;
            novo->proximo = NULL;

            inserir_ordenado_lista(lista, novo);
        }
        else{
            printf("\n\tERRO ao alocar memoria em montar_arvore!\n");
            break;
        }
    }
    return lista->inicio;
}

void imprimir_arvore(TipoNo *raiz, int tam){ //imprime a árvore de Huffman
    if(raiz->esquerda == NULL && raiz->direita == NULL) //se for um nó folha, ou seja, se existe uma chave ali
        printf("\tFolha: %c\tAltura: %d\n", raiz->chave, tam);
    else{
        imprimir_arvore(raiz->esquerda, tam + 1);
        imprimir_arvore(raiz->direita, tam + 1);
    }
}

//Montar o dicionário

int altura_arvore(TipoNo *raiz){ //calcula a altura da árvore
    int esq, dir;

    if(raiz == NULL) { //árvore vazia
        return -1;
    } else{
        esq = altura_arvore(raiz->esquerda) + 1;
        dir = altura_arvore(raiz->direita) + 1;

        if(esq > dir) {
            return esq;
        } else {
            return dir;
        }
    }
}

char** alocar_dicionario(int colunas){ //aloca o dicionário
    char **dicionario; //o dicionário é uma matriz
    int i;

    dicionario = malloc(sizeof(char*) * TAM);

    for(i = 0; i < TAM; i++) {
        dicionario[i] = calloc(colunas, sizeof(char));
    }

    return dicionario;
}

void gerar_dicionario(char **dicionario, TipoNo *raiz, char *caminho, int colunas){ //gera o dicionário
    char esquerda[colunas], direita[colunas];

    if(raiz->esquerda == NULL && raiz->direita == NULL) {
        strcpy(dicionario[raiz->chave], caminho);
    } else {
        strcpy(esquerda, caminho);
        strcpy(direita, caminho);

        strcat(esquerda, "0");
        strcat(direita, "1");

        gerar_dicionario(dicionario, raiz->esquerda, esquerda, colunas);
        gerar_dicionario(dicionario, raiz->direita, direita, colunas);
    }
}

void imprimir_dicionario(char **dicionario){ //imprimir o dicionário
    int i;

    printf("\n\tDicionario:\n");
    for(i = 0; i < TAM; i++){
        if(strlen(dicionario[i]) > 0)
            printf("\t%3d: %s\n", i, dicionario[i]);
    }
}

//Codificar

int calcular_tamanho_string(char **dicionario, unsigned char *texto){ //calcula o tamanho da string
    int i = 0, tam = 0;
    while(texto[i] != '\0'){
        tam = tam + strlen(dicionario[texto[i]]);
        i++;
    }
    return tam + 1; //ajusta o tamanho
}

char* codificar(char **dicionario, unsigned char *texto){ //codifica o texto

    int i = 0, tam = calcular_tamanho_string(dicionario, texto);
    char *codigo = calloc(tam, sizeof(char));

    while(texto[i] != '\0'){ //enquanto o texto não é o caracter de fim de texto
        strcat(codigo, dicionario[texto[i]]); //essa função junta uma string ao final de outra
        i++;
    }
    return codigo;
}

void separarNomeExtensao(const char *nomeArquivo, char *nome, char *extensao) {
    const char *ponto = strrchr(nomeArquivo, '.'); // encontrar o último ponto no nome do arquivo
    if (ponto != NULL && ponto != nomeArquivo) { // verificar se há um ponto e se não está no início do nome
        size_t tamanhoNome = ponto - nomeArquivo; // calcular o tamanho do nome (excluindo a extensão)
        strncpy(nome, nomeArquivo, tamanhoNome); // copiar o nome para a variável 'nome'
        nome[tamanhoNome] = '\0';

        // Agora, vamos verificar se há algum ponto após o último ponto encontrado
        const char *proximoPonto = strchr(ponto + 1, '.');
        if (proximoPonto != NULL) {
            // Se houver outro ponto, consideramos apenas a parte entre os dois pontos
            size_t tamanhoExtensao = proximoPonto - ponto - 1;
            strncpy(extensao, ponto + 1, tamanhoExtensao);
            extensao[tamanhoExtensao] = '\0';
        } else {
            // Se não houver outro ponto, copiamos a extensão como está (após o último ponto)
            strcpy(extensao, ponto + 1);
        }
    } else {
        strcpy(nome, nomeArquivo); // não há ponto ou está no início do nome, então não há extensão
        extensao[0] = '\0'; // extensão vazia
    }
}

//Compactar
void compactar(unsigned char str[], char *nomeArquivo, char *extensao) {
    char nomeSaida[256];
    snprintf(nomeSaida, sizeof(nomeSaida), "%s.comp", nomeArquivo);

    FILE* arquivoSaida = fopen(nomeSaida, "wb");
    int i = 0, j = 7;
    unsigned char mascara, byte = 0; // 00000000

    if (arquivoSaida) {
        //escreve o tamanho da extensão e a extensão no arquivo compactado
        size_t tamanhoExtensao = strlen(extensao);
        fwrite(&tamanhoExtensao, sizeof(size_t), 1, arquivoSaida);
        fwrite(extensao, sizeof(char), tamanhoExtensao, arquivoSaida);
        fputc('\n', arquivoSaida);  // Adiciona uma quebra de linha ao final da extensão


        while(str[i] != '\0'){ //enquanto o texto não chegar no final
            mascara = 1;
            if(str[i] == '1'){
                mascara = mascara << j; //desloca à esquerda a máscara em j bits
                byte = byte | mascara; //ou bít-a-bit
            }
            j--;

            if(j < 0){ // tem um byte formado
                fwrite(&byte, sizeof(unsigned char), 1, arquivoSaida); //escreve um byte no arquivo compactado
                byte = 0;
                j = 7;
            }

            i++;
        }
        if(j != 7){ // tem um byte em formação (incompleto)
            fwrite(&byte, sizeof(unsigned char), 1, arquivoSaida); //escreve o byte final incompleto no arquivo
        }
        fclose(arquivoSaida);
    }
    else{
        printf("\nERRO ao abrir/criar arquivo em compactar\n");
    }
}

int descobrir_tamanho(const char *nomeArquivo) {
    FILE *arq = fopen(nomeArquivo, "r");
    int tam = 0;

    if (arq) {
        while (fgetc(arq) != EOF) {
            tam++;
        }
        fclose(arq);
    } else {
        printf("\nErro ao abrir o arquivo em descobrir_tamanho\n");
    }
    return tam;
}

void ler_texto(const char *nomeArquivo, unsigned char *texto, int tam) {
    FILE *arq = fopen(nomeArquivo, "r");
    unsigned char letra;
    int i = 0;

    if (arq) {
        while ((letra = fgetc(arq)) != EOF && i < tam) {
            texto[i] = letra;
            i++;
        }
        fclose(arq);
    } else {
        printf("\nErro ao abrir o arquivo em ler_texto\n");
    }
}


void free_dicionario(char **dicionario, int colunas) { //liberar memória do dicionário
    for (int i = 0; i < TAM; i++) {
        free(dicionario[i]);
    }
    free(dicionario);
}

void free_arvore(TipoNo *raiz) { //liberar a árvore de Huffman
    if (raiz == NULL) return;
    free_arvore(raiz->esquerda);
    free_arvore(raiz->direita);
    free(raiz);
}

