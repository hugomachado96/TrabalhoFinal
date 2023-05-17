#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "meio.h"


typedef struct cliente {
	char nome[50];
	int contribuinte;
	char utilizador[50], password[12], morada[100];
	float saldo;
	struct cliente* next;
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
int menuAcesso(Clientes* cliente, Meio* meios);
//Clientes* clientesExitentes();
int menu1();
int menu2(Clientes* comeco);
int menu3();
int menuAluguer(Clientes* comeco, Meio* inicio, Aluguer* inicial);
int haCliente(Clientes* comeco, int cod);
Aluguer* criarAluguer(Aluguer* inicio, int cod, float time, Clientes* comeco, Meio* inicial);
void listarClientes(Clientes* comeco);
Clientes* menuInicial(Clientes* inicio, Meio* inicial, Aluguer* comeco);
int guardarClientes(Clientes* inicio);
int guardarAluguer(Aluguer* inicio);
Clientes* clientesExistentes();
