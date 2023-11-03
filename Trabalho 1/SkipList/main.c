#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SkipList.h"

int main(void){
	TipoSkipList* SL = criarSkipList(5, 0.5); //decidimos que nivelMAX = 5 e que P = 50%
	//P e a probabilidade usada para determinar o nivel de cada no a ser inserido na skiplist
	//P = 0,5 significa que ha 50% de chance de um no ter nivel superior em comparacao a um no inferior
	//nivelMAX e o nivel maximo que um no pode atingir (controla a altura da skiplist). Ou seja, esta skiplist tem, no maximo, 5 niveis
	char operacao;
	char nome[MAX_NOME];
	TipoContato contato;
	
	while (1) {
		scanf(" %c", &operacao);

		if (operacao == '0') { //sair do programa
			break;
		}

		switch (operacao) {

			case 'I': //insercao de contato
				scanf(" %s %s", contato.nome, contato.telefone);
				inserirSkipList(SL, contato);
				break;

			case 'P': //busca de contato pelo nome
				scanf(" %s", nome);
				TipoNo* encontrado = buscarSkipList(SL, nome);
				if (encontrado != NULL) {
					// Atualize a variável 'contato' com os detalhes do contato encontrado
					strcpy(contato.nome, encontrado->contato.nome);
					strcpy(contato.telefone, encontrado->contato.telefone);

					printf("Contatinho encontrado: telefone %s\n", contato.telefone);
				} else {
					printf("Contatinho nao encontrado\n");
				}
				break;

			case 'R': //remocao de contato pelo nome
				scanf(" %s", nome);
				removerSkipList(SL, nome);
				break;

			case 'A': //alteracao de contato
				scanf(" %s %s", contato.nome, contato.telefone);
				alterarSkipList(SL, contato);
				break;

			default:
				printf("Operacao invalida\n");
				break;
		}
	}

	liberarSkipList(SL); //libera a skiplist, evitando vazamento de memoria
	return 0;
}
