#ifndef _CLIENTE_H_
#define _CLIENTE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "meio.h"


typedef struct cliente {
	char nome[50];
	int contribuinte;
	char utilizador[50], password[12], morada[100];
	float saldo;
	char localizacao[100];
	struct Clientes* next;
}Clientes;


typedef struct aluga {
	float custo, tempo;
	int codigo;
	char nome[50];
	struct aluga* next;
}Aluguer;

Clientes* novoCliente(Clientes* inicio, char name[], int contr, char adress[], char uti[], char pass[], float credit);
void listarClientes(Clientes* inicio);
int menuCliente(Clientes* inicio);
int loginClientes(Clientes* inicio);
int menuAcesso(Clientes* cliente, Meio* meios, Aluguer* inicio);
int menu1();
int menu2(Clientes* comeco);
int menu3();
int menuAluguer(Clientes* comeco, Meio* inicio, Aluguer* inicial);
int haCliente(Clientes* comeco, int cod);
Aluguer* criarAluguer(Aluguer* inicio, int cod, float time, Clientes* comeco, Meio* inicial);
Clientes* menuInicial(Clientes* inicio, Meio* inicial, Aluguer* comeco, struct Grafo* grafo, struct vertices* vertices);
int guardarClientes(Clientes* inicio);
int guardarAluguer(Aluguer* inicio);
Clientes* clientesExistentes();
int adicionarSaldo(Clientes* inicio);
//int adicionarLocalizacaoCliente(struct Grafo* g, Clientes* cliente);
Clientes* searchLocationClient(Clientes* head, const char* location);

#endif