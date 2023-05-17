#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include<stdio.h>
#include <string.h>

#include "meio.h"

Meio* novoRegisto(Meio* comeco, int cod, char typ[], int auton, float charge, char local[], int alug) {
	if (!haMeio(comeco, cod)) {
		Meio* novo = malloc(sizeof(struct registo));
		if (novo != NULL) {
			novo->codigo = cod;
			strcpy(novo->tipo, typ);
			novo->autonomia = auton;
			novo->carga = charge;
			strcpy(novo->localizacao, local);
			novo->alugada = alug;
			novo->next = NULL;

			// Caso a lista esteja vazia
			if (comeco == NULL) {
				comeco = novo;
				return comeco;
			}

			// Caso o novo registro tenha que ser adicionado no começo da lista
			if (charge < comeco->carga) {
				novo->next = comeco;
				comeco = novo;
				return comeco;
			}

			// Percorre a lista procurando o local de inserção
			Meio* atual = comeco;
			while (atual->next != NULL && charge > atual->next->carga) {
				atual = atual->next;
			}

			// Adiciona o novo registro no local correto
			novo->next = atual->next;
			atual->next = novo;
		}
	}

	return comeco;
}



void listarRegisto(Meio* comeco) {
	while (comeco != NULL)
	{
		printf("%d %s %d %.2f %s %d\n", comeco->codigo, comeco->tipo,
			comeco->autonomia, comeco->carga, comeco->localizacao, comeco->alugada);
		comeco = comeco->next;
	}
}

int haMeio(Meio* comeco, int cod) {
	while (comeco != NULL)
	{
		if (comeco->codigo == cod) return(1);
		comeco = comeco->next;
	}
	return(0);
}

Meio* removerMeio(Meio* comeco, int cod) {
	Meio* anterior = NULL;
	Meio* atual = comeco;

	while (atual != NULL && atual->codigo != cod) {
		anterior = atual;
		atual = atual->next;
	}

	if (atual == NULL) {
		return comeco;
	}

	if (anterior == NULL) {
		comeco = atual->next;
	}
	else {
		anterior->next = atual->next;
	}


	free(atual);
	return (comeco);
}

Meio* lerMeios()
{
	FILE* fp;
	int cod, aut, alug;
	float bat;
	char tipo[50], local[100];
	Meio* aux = NULL;
	fp = fopen("meio.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d;%[^;];%d;%f;%[^;]s;%d\n", &cod, tipo, &aut, &bat, local, &alug);
			aux = novoRegisto(aux, cod, tipo, aut, bat, local, alug);
		}
		fclose(fp);
	}
	return(aux);
}

void meiosDisponiveis(Meio* comeco) {
	while (comeco != NULL)
	{
		if (comeco->alugada != 1) {
			printf("%d %s %d %.2f %s %d\n", comeco->codigo, comeco->tipo,
				comeco->autonomia, comeco->carga, comeco->localizacao, comeco->alugada);
		}
		comeco = comeco->next;
	}
}

int guardarMeios(Meio* inicio)
{
	FILE* fp;
	fp = fopen("meio.txt", "w");
	if (fp != NULL)
	{
		Meio* aux = inicio;
		while (aux != NULL)
		{
			fprintf(fp, "%d;%s;%d;%f;%s;%d\n", aux->codigo, aux->tipo, aux->autonomia, aux->carga, aux->localizacao, aux->alugada);
			aux = aux->next;
		}
		fclose(fp);
		return(1);
	}
	else return(0);
}

Meio* desalugar(Meio* inicio, int cod) {
	while (inicio != NULL) {
		if (cod == inicio->codigo) {
			if (inicio->alugada == 0) {
				printf("Este veiculo não esta alugado.");
				return NULL;
			}
			else {
				inicio->alugada = 0;
				printf("O veiculo foi entregue. Obrigado pela sua preferência.");
				return inicio;
			}
		}
		inicio = inicio->next;
	}
	printf("Não foi encontardo nenhum veiculo com esse codigo.");
	return inicio;
}

Meio* mudarAlugar(Meio* inicio, int cod) {
	while (inicio != NULL) {
		if (cod == inicio->codigo) {
			if (inicio->alugada == 1) {
				printf("Este veiculo ja esta alugado.");
				return NULL;
			}
			else {
				inicio->alugada = 1;
				return inicio;
			}
		}
		inicio = inicio->next;
	}
	printf("Não foi encontardo nenhum veiculo com esse codigo.");
	return NULL;
}

