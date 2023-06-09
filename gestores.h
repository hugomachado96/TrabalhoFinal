#ifndef _GESTORES_H_
#define _GESTORES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "meio.h"

typedef struct gestor {
	int codigo;
	char nome[50];
	char password[12];
	struct gestor* next;
}Gestores;

Gestores* novoGestor(Gestores* new, int cod, char name[], char pass[]);
Gestores* menuGestores(Gestores* inicio, Clientes* comeco, Meio* inicial);
int haGestor(Gestores* comeco, int cod);
void listarGestores(Gestores* inicio);
Gestores* lerFicheiro();
int guardarGestores(Gestores* inicio);
int principalGestores(Gestores* comeco);
int loginGestores(Gestores* comeco);
Gestores* Menu(Gestores* inicio, Clientes* comeco, Meio* inicial);
Clientes* readDataFromFile();
int menuGestoresInicial();
int menuGrafos();

#endif