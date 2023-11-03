#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SkipList.h"

TipoNo *criarNo(TipoContato contato, int nivel) {
	TipoNo *novo_no = (TipoNo*) malloc(sizeof(TipoNo));
	if (novo_no != NULL) { //erro de alocacao de memoria
		novo_no->contato = contato;
		novo_no->proximo = (TipoNo**) malloc((nivel + 1) * sizeof(TipoNo*));

		if (novo_no->proximo != NULL) {
			for (int i = 0; i <= nivel; i++) {
				novo_no->proximo[i] = NULL;
			}
		} else { //erro de alocacao de memoria para novo_no->proximo
			free(novo_no->proximo);
			return ERRO;
		}
	} else { //erro de alocacao de memoria para novo_no
		free(novo_no);
		return ERRO;
	}
	return novo_no; //novo_no criado
}

TipoSkipList* criarSkipList(int nivelMAX, float P) {
	TipoSkipList *SL = (TipoSkipList*) malloc(sizeof(TipoSkipList));
	if (SL != NULL) { //alocacao de memoria deu certo
		SL->nivelMAX = nivelMAX;
		SL->P = P;
		SL->nivel = 0;

		//cria um contato para o cabecalho, que nao tem nome e telefone validos, serve como sentinela
		TipoContato cabecalho_contato;
		strncpy(cabecalho_contato.nome, "cabecalho", MAX_NOME);
		strncpy(cabecalho_contato.telefone, "cabecalho", MAX_TELEFONE);

		SL->cabecalho = criarNo(cabecalho_contato, nivelMAX);

		if (SL->cabecalho == NULL) { //erro de alocacao na cabecalho
			free(SL);
			return NULL;
		}
	} else { //erro de alocacao na skiplist
		return NULL;
	}
	return SL;
}

void liberarNo(TipoNo *no) { //liberar um no
	if (no != NULL) {
		free(no->proximo);
		free(no);
	}
}

void liberarSkipList(TipoSkipList* SL) { //liberar a skiplist
	if (SL == NULL) {
		return;
	}

	TipoNo *contato, *atual;
	atual = SL->cabecalho->proximo[0];

	while (atual != NULL) { //libera cada no
		contato = atual;
		atual = atual->proximo[0];
		liberarNo(contato);
	}
	free(SL->cabecalho); //libera o cabecalho
	free(SL); //libera a propria skiplist
}

int vaziaSkipList(TipoSkipList* SL) { //a skiplist esta vazia?
	if (SL == NULL || SL->cabecalho->proximo[0] == NULL) {
		return SUCESSO;
	} else {
		return ERRO;
	}
}

int sorteiaNivel(TipoSkipList *SL) {
	float r = (float)rand() / RAND_MAX;
	int nivel = 0;
	while (r < SL->P && nivel < SL->nivelMAX) {
		nivel++;
		r = (float)rand() / RAND_MAX;
	}
	return nivel;
}

TipoNo* buscarSkipList(TipoSkipList* SL, char nome[MAX_NOME]) {
	if (SL == NULL) { //skiplist vazia, nao vai encontrar o contato
		return NULL;
	}

	TipoNo *atual = SL->cabecalho;

	for (int i = SL->nivel; i >= 0; i--) { //varre a skiplist procurando o contato
		while (atual->proximo[i] != NULL && strcmp(atual->proximo[i]->contato.nome, nome) < 0) {
			atual = atual->proximo[i];
		}
	}

	atual = atual->proximo[0];
	if (atual != NULL && strcmp(atual->contato.nome, nome) == 0) {
		return atual; //se encontrar, retorna o contato
	} else {
		return NULL; //caso contrario, nao encontrou
	}
}

int inserirSkipList(TipoSkipList *SL, TipoContato contato) {
	if (SL == NULL || contato.nome[0] == '\0' || contato.telefone[0] == '\0') { //erro de alocacao ou nome/telefone invalidos
		return ERRO;
	}
	
	if (vaziaSkipList(SL)) { //quando a skiplist esta vazia, sempre vai inserir
		TipoNo *novo_no = criarNo(contato, SL->nivelMAX);
		if (novo_no == NULL) {
			return ERRO;
		}

		for (int i = 0; i <= SL->nivelMAX; i++) {
			SL->cabecalho->proximo[i] = novo_no;
		}

		SL->nivel = SL->nivelMAX;

		return SUCESSO;
	}
	
	TipoNo* ja_existe = buscarSkipList(SL, contato.nome);
	if (ja_existe != NULL){ //se encontrar o contato na busca, ele ja esta inserido
		printf("Contatinho ja inserido\n");
		return ERRO;
	}
	
	//procurar a posicao do novo no
	TipoNo *atual = SL->cabecalho;
	TipoNo **aux = (TipoNo**) malloc((SL->nivelMAX + 1) * sizeof(TipoNo*));

	if (aux == NULL) {
		   free(aux);
		   return ERRO;
	   }

	   int i;
	   for (i = SL->nivel; i >= 0; i--) {
		   while (atual->proximo[i] != NULL && strcmp(atual->proximo[i]->contato.nome, contato.nome) < 0) {
			   atual = atual->proximo[i];
		   }
		   aux[i] = atual;
	   }

	   //necessario criar o nivel para poder criar o no
	   int novo_nivel = sorteiaNivel(SL);
	   if (novo_nivel > SL->nivel) {
		   for (i = SL->nivel + 1; i <= novo_nivel; i++) {
			   aux[i] = SL->cabecalho;
		   }
		   SL->nivel = novo_nivel;
	   }

	   //criacao do novo no de contato
	   TipoNo *novo_no = criarNo(contato, novo_nivel);

	   if (novo_no == NULL) { //erro de alocacao
		   free(novo_no);
		   free(aux);
		   return ERRO;
	   }

	   for (i = 0; i <= novo_nivel; i++) {
		   novo_no->proximo[i] = aux[i]->proximo[i];
		   aux[i]->proximo[i] = novo_no;
	   }

	   free(aux);
	   return SUCESSO;
   }

int removerSkipList(TipoSkipList* SL, char nome[MAX_NOME]) {
	if (SL == NULL || nome == NULL) { //lista nao existe ou nome invalido
		return ERRO;
	}

	int i;
	TipoNo *atual = SL->cabecalho;
	TipoNo **aux = (TipoNo**) malloc((SL->nivelMAX + 1) * sizeof(TipoNo*));

	if (aux == NULL) { //erro de alocacao de memoria
		   free(aux);
		   return ERRO;
	   }
	
	for (i = 0; i <= SL->nivelMAX; i++) {
		aux[i] = NULL;
	}

	//busca a posicao do no a ser removido
	for (i = SL->nivel; i >= 0; i--) {
		while (atual->proximo[i] != NULL && strcmp(atual->proximo[i]->contato.nome, nome) < 0) {
			atual = atual->proximo[i];
		}
		aux[i] = atual;
	}

	atual = atual->proximo[0];
	
	//caso esse no exista, ele deve ser removido
	if (atual != NULL && strcmp(atual->contato.nome, nome) == 0) {
		for (i = 0; i <= SL->nivel; i++) {
			if (aux[i]->proximo[i] != atual) {
				break;
			}
			aux[i]->proximo[i] = atual->proximo[i];
		}

		while (SL->nivel > 0 && SL->cabecalho->proximo[SL->nivel] == NULL) {
			SL->nivel--;
		}

		free(atual->proximo);
		free(atual);
		free(aux);
		return SUCESSO;
	} else { //o contato a ser removido nao existe na agenda
		printf("Operacao invalida: contatinho nao encontrado\n");
		free(aux);
		return ERRO;
	}
}

int alterarSkipList(TipoSkipList* SL, TipoContato contato) {
	if (SL == NULL || contato.nome[0] == '\0') {
		return ERRO;
	} else {
		
		TipoNo* ja_existe = buscarSkipList(SL, contato.nome);
		if (ja_existe == NULL){ //o contato nao existe, portanto, nao pode ser alterado
			printf("Operacao invalida: contatinho nao encontrado \n");
			return ERRO;
		}
		
		TipoNo *atual = SL->cabecalho->proximo[0];
		
		//procura a posicao do contato a ser alterado
		while (atual != NULL && strcmp(atual->contato.nome, contato.nome) != 0) {
			atual = atual->proximo[0];
		}
		
		if (atual != NULL && strcmp(atual->contato.nome, contato.nome) == 0) { //achou o contato e altera o seu telefone
			strncpy(atual->contato.telefone, contato.telefone, MAX_TELEFONE);
			return SUCESSO;
		}
		return ERRO;
	}
}


//int tamanhoSkipList(TipoSkipList* SL) {
	//if (SL == NULL || SL->cabecalho == NULL) {
		//return ERRO;
	//}

	//int cont = 0;
	//TipoNo *atual;
	//atual = SL->cabecalho->proximo[0];
	//while (atual != NULL) {
		//atual = atual->proximo[0];
		//cont++;
	//}
	//return cont;
//}

//void imprimirSkipList(TipoSkipList *SL) {
	//if (SL == NULL) {
		//return;
	//}
	//int i;
	//printf("\n*****Skip List*****\n");
	//for (i = 0; i <= SL->nivel; i++) {
		//TipoNo *contato = SL->cabecalho->proximo[i];
		//printf("Nível %d: ", i);
		//while (contato != NULL) {
			//printf("%s, %s;", contato->contato.nome, contato->contato.telefone);
			//contato = contato->proximo[i];
		//}
		//printf("\n");
	//}
//}
