#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gestores.h"


Gestores* novoGestor(Gestores* new, int cod, char name[], char pass[]) {

	if (!haGestor(new, cod)) {
		Gestores* novo = malloc(sizeof(struct gestor));
		if (novo != NULL) {
			novo->codigo = cod;
			strcpy(novo->nome, name);
			strcpy(novo->password, pass);

			novo->next = NULL;

			// Caso a lista esteja vazia
			if (new == NULL) {
				new = novo;
				return new;
			}

			// Caso o novo registro tenha que ser adicionado no começo da lista
			if (cod < new->codigo) {
				novo->next = new;
				new = novo;
				return new;
			}

			// Percorre a lista procurando o local de inserção
			Gestores* atual = new;
			while (atual->next != NULL && cod > atual->next->codigo) {
				atual = atual->next;
			}

			// Adiciona o novo registro no local correto
			novo->next = atual->next;
			atual->next = novo;
		}
	}

	return new;
}

int haGestor(Gestores* comeco, int cod) {
	while (comeco != NULL)
	{
		if (comeco->codigo == cod) return(1);
		comeco = comeco->next;
	}
	return(0);
}

Gestores* menuGestores(Gestores* inicio, Clientes* comeco, Meio* inicial) {
	int choice, cod, login;
	char name[50], pass[12];
	printf("----------------------------------------------\n");
	printf("Tem registo?\tSim (1); Não (2)\n");
	scanf("%i", &choice);
	switch (choice) {
	case 1:
		system("cls");
		inicio = lerFicheiro();
		login = loginGestores(inicio);
		if (login == 1) inicio = Menu(inicio, comeco, inicial);
		else printf("Login incorreto!");
		break;
	case 2:
		getchar();
		printf("\n Nome: ");
		fgets(name, 50, stdin);
		printf("\n Codigo de Identificação: ");
		scanf("%i", &cod);
		getchar();
		printf("\nDefina a sua password: ");
		fgets(pass, 12, stdin);
		inicio = novoGestor(inicio, cod, name, pass);
		break;
	default:
		printf("Opção invalida!");
		return 0;
	}
	return inicio;
}

void listarGestores(Gestores* comeco) {
	while (comeco != NULL) {
		printf("%d\t%s\n", comeco->codigo, comeco->nome);
		comeco = comeco->next;
	}
}

Gestores* lerFicheiro() {
	FILE* arquivo = fopen("gestores.txt", "r");
	if (arquivo == NULL) {
		printf("Não encontramos a base de dados\n");
		return NULL;
	}

	Gestores* inicio = NULL;
	Gestores* novo_gestor;
	Gestores* ultimo_gestor = NULL;

	while (!feof(arquivo)) {
		novo_gestor = (Gestores*)malloc(sizeof(Gestores));
		if (fscanf(arquivo, "%d;%[^;];%[^\n]\n", &novo_gestor->codigo, novo_gestor->nome, novo_gestor->password) == 3) {
			novo_gestor->next = NULL;

			if (inicio == NULL) {
				inicio = novo_gestor;
			}
			else {
				ultimo_gestor->next = novo_gestor;
			}

			ultimo_gestor = novo_gestor;
		}
		else {
			free(novo_gestor);
		}
	}

	fclose(arquivo);

	return inicio;
}

int guardarGestores(Gestores* inicio)
{
	FILE* fp;
	fp = fopen("gestores.txt", "w");
	if (fp != NULL)
	{
		Gestores* aux = inicio;
		while (aux != NULL)
		{
			fprintf(fp, "%d;%s;%s\n", aux->codigo, aux->nome, aux->password);
			aux = aux->next;
		}
		fclose(fp);
		return(1);
	}
	else return(0);
}

int loginGestores(Gestores* comeco) {
	int cod;
	char pass[12];
	comeco = lerFicheiro();
	printf("\nCodigo de Identificação: ");
	scanf("%d", &cod);
	printf("\nPassword: ");
	scanf("%s", pass);

	while (comeco != NULL) {
		if (comeco->codigo == cod && strcmp(pass, comeco->password) == 0) return 1;
		comeco = comeco->next;
	}
	return 0;
}

int principalGestores(Gestores* comeco) {
	int choice;
	printf("Bem vindo %s!\n", comeco->nome);
	printf("1-Ver lista de clientes\n");
	printf("2-Ver lista de Gestores\n");
	printf("3-Ver lista de meios\n");
	printf("4-Adicionar meio novo\n");
	printf("5-Remover meio através do codigo\n");
	printf("6-Adicionar um novo gestor\n");
	printf("0-Sair\n");
	scanf("%d", &choice);
	return choice;
}

Gestores* Menu(Gestores* inicio, Clientes* comeco, Meio* inicial) {
	int op, cod, aut, alug;
	char type[50], loc[50];
	float carg;
	do {
		op = principalGestores(inicio);

		switch (op) {
		case 1:
			system("cls");
			listarClientes(comeco);
			system("PAUSE");
			break;
		case 2:
			system("cls");
			listarGestores(inicio);
			system("PAUSE");
			break;
		case 3:
			system("cls");
			listarRegisto(inicial);
			system("PAUSE");
			break;
		case 4:
			system("cls");
			printf("Codigo: ");
			scanf("%d", &cod);
			getchar();
			printf("Tipo de transporte: ");
			fgets(type, 50, stdin);
			printf("Autonomia: ");
			scanf("%i", &aut);
			getchar();
			printf("Localização: ");
			fgets(loc, 50, stdin);
			printf("Carga disponivel:  ");
			scanf("%f", &carg);
			printf("Está alugada(1 para esta ou 0 para nao esta): ");
			scanf("%d", &alug);
			inicial = novoRegisto(inicial, cod, type, aut, carg, loc, alug);
			guardarMeios(inicial);
			break;
		case 5:
			system("cls");
			printf("Qual é o codigo do transporte a ser retirado? ");
			scanf("%d", &cod);
			inicial = removerMeio(inicial, cod);
			system("PAUSE");
			break;
		case 6:
			system("cls");
			getchar();
			printf("\n Nome: ");
			fgets(type, 50, stdin);
			printf("\n Codigo de Identificação: ");
			scanf("%i", &cod);
			getchar();
			printf("\nDefina a sua password: ");
			fgets(loc, 12, stdin);
			inicio = novoGestor(inicio, cod, type, loc);
			guardarGestores(inicio);
			break;
		case 0:
			printf("Login out.");
			break;
		default:
			printf("Opção invalida!");
			system("cls");
			break;
		}
	} while (op != 0);
	return (inicio);
}
