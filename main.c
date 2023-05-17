#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include<stdio.h>
#include <string.h>
#include <locale.h>

#include "gestores.h"


int menuPrincipal() {
	int opcao;
	printf("Ol·!\nBem Vindo.\n… Gestor(1) ou Cliente(2)? \n");
	scanf("%i", &opcao);
	return opcao;
}

int main() {
	Meio* meios = NULL;
	Gestores* gestores = NULL;
	Clientes* cliente = NULL;
	Aluguer* alugar = NULL;
	int op;

	meios = lerMeios();
	gestores = lerFicheiro();
	cliente = readDataFromFile();

	do {
		op = menuPrincipal();
		switch (op) {
		case 1:
			system("cls");
			gestores = menuGestores(gestores, cliente, meios);
			system("PAUSE");
			break;
		case 2:
			system("cls");
			cliente = menuInicial(cliente, meios, alugar);
			system("PAUSE");
			break;
		default:
			break;
		}
	} while (op != 0);
	return 0;
}