#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cliente.h"


/**
 * Introduçao ordenada de novo cliente.
 *
 * Nesta função, usamos os elementos dados para a introduçao de um novo cliente.
 * Usando o numero de contibuito, a função tenta ordenar a localizaçao do novo registo
 * comparando os registos que ja tem.
 *
 * @struct comeco ponteiro para o primeiro elemento da lista ligada de clientes.
 * @char name nome do cliente.
 * @int contr número de contribuite do novo cliente.
 * @char adress morada do novo cliente
 * @char uti nome de utilizador
 * @char pass password associada a nova conta
 *
 * @return retorna a estrutura, que passamos como argumento, atualizada.
 */

Clientes* novoCliente(Clientes* comeco, char name[], int contr, char adress[], char uti[], char pass[], float credit) {
	if (!haCliente(comeco, contr)) {
		Clientes* novo = malloc(sizeof(struct cliente));
		if (novo != NULL) {
			novo->contribuinte = contr;
			strcpy(novo->nome, name);
			strcpy(novo->morada, adress);
			strcpy(novo->utilizador, uti);
			strcpy(novo->password, pass);
			if (credit > 0) novo->saldo = credit;
			else novo->saldo = 0;
			novo->next = NULL;

			// Caso a lista esteja vazia
			if (comeco == NULL) {
				comeco = novo;
				return comeco;
			}

			// Caso o novo registro tenha que ser adicionado no começo da lista
			if (contr < comeco->contribuinte) {
				novo->next = comeco;
				comeco = novo;
				return comeco;
			}

			// Percorre a lista procurando o local de inserção
			Clientes* atual = comeco;
			while (atual->next != NULL && contr > atual->next->contribuinte) {
				atual = atual->next;
			}

			// Adiciona o novo registro no local correto
			novo->next = atual->next;
			atual->next = novo;
		}
	}

	return comeco;
}

/**
 * estrutura do menu inicial para clientes
 *
 * serie de printf com a exibição das várias opcões e lê, do input do utilizador, a escolha.
 *
 * @return retorna o valor da opção a ser usada mais tarde.
 */

int menu1() {
	int choice;
	printf("Bem Vindo!\n");
	printf("1-Novo Cliente\n");
	printf("2-Já tens conta? Faz login.\n");
	printf("0-Voltar\n");
	scanf("%i", &choice);

	return choice;
}

Clientes* menuInicial(Clientes* inicio, Meio* inicial, Aluguer* comeco) {
	int op, contr, pog;
	char name[50], adress[100], uti[50], pass[12];
	do {
		op = menu1();
		switch (op) {
		case 1:
			system("cls");
			printf("Numero de contribuinte: ");
			scanf("%d", &contr);
			getchar();
			printf("Nome: ");
			fgets(name, 50, stdin);
			getchar();
			printf("Morada: ");
			fgets(adress, 100, stdin);
			getchar();
			printf("Nome de utilizador: ");
			fgets(uti, 50, stdin);
			printf("Password a ser atribuida:  ");
			fgets(pass, 12, stdin);
			inicio = novoCliente(inicio, name, contr, adress, uti, pass, 0);
			guardarClientes(inicio);
			system("PAUSE");
		case 2:
			system("cls");
			pog = loginClientes(inicio);
			if (pog == 1)inicio = menuAcesso(inicio, inicial, comeco);
			else if (pog == 0) printf("Não foi possivel fazer login.");
			system("PAUSE");
			break;
		case 0:
			break;
		default:
			break;
		}
	} while (op != 0);
	return inicio;
}

/**
 * estrutura do menu de cliente
 *
 * serie de printf com a exibição das várias opcões e lê, do input do utilizador, a escolha.
 *
 * @struct comeco ponteiro direcionada ao inicio da lista ligada de clientes
 * @return retorna o valor da opção a ser usada mais tarde.
 */

int menu2(Clientes* comeco) {
	int choice;
	printf("Bem vindo %s!\n", comeco->nome);
	printf("1-Adicionar Saldo\n");
	printf("2-Ver meios disponiveis\n");
	printf("3-Aluguer\n");
	printf("0-Voltar\n");
	scanf("%i", &choice);

	return choice;
}

/**
 * estrutura do menu de aluguer
 *
 * serie de printf com a exibição das várias opcões e lê, do input do utilizador, a escolha.
 *
 * @return retorna o valor da opção a ser usada mais tarde.
 */

int menu3() {
	int choice;
	printf("1-Ver meios disponiveis\n");
	printf("2-Alugar\n");
	printf("3-Devolver o veiculo\n");
	printf("0-Voltar\n");
	scanf("%i", &choice);

	return choice;
}

/**
 * Breve descrição da função.
 *
 * Descrição mais detalhada da função.
 *
 * @param param1 Descrição do primeiro parâmetro.
 * @param param2 Descrição do segundo parâmetro.
 * @return Descrição do valor de retorno.
 */

int menuAluger(Clientes* comeco, Meio* inicio, Aluguer* inicial) {
	int pog, cod;
	float time;
	Aluguer* aux = NULL;
	pog = menu3();
	switch (pog) {
	case 1:
		system("cls");
		meiosDisponiveis(inicio);
		system("PAUSE");
		break;
	case 2:
		system("cls");
		meiosDisponiveis(inicio);
		printf("\nCodigo do meio que quer usar: ");
		scanf("%d", &cod);
		printf("Quanto tempo vai usar a esse meio: ");
		scanf("%f", &time);
		aux = criarAluguer(aux, cod, time, comeco, inicio);
		guardarAluguer(aux);
		printf("Aluguer realizado com sucesso!\n");
		system("PAUSE");
		break;
	case 3:
		system("cls");
		printf("Qual é o codigo do veiculo que quer devolver: ");
		scanf("%d", &cod);
		inicio = desalugar(inicio, cod);
		system("PAUSE");
		break;
	default:
		break;
	}
	return 0;
}

Aluguer* criarAluguer(Aluguer* inicio, int cod, float time, Clientes* comeco, Meio* inicial) {
	Aluguer* novo = malloc(sizeof(struct aluga));
	if (novo != NULL) {
		while (inicial != NULL) {
			if (cod == inicial->codigo) {
				if (inicial->alugada == 0) {
					novo->codigo = cod;
					novo->tempo = time;
					strcpy(novo->nome, comeco->nome);
					novo->custo = time * 0.18;
					novo->next = inicio;
					return (novo);
				}
				else printf("Este Meio já se encontra alugado.");
			}
			inicial = inicial->next;
		}
		printf("Não existe este meio.");
	}
	return novo;
}

/**
 * Confirmar se existe o cliente
 *
 * Esta função percorre a lista ligada dos clientes e verifica se um contribuinte ja existe na
 * na estrutura
 *
 * @estrutura comeco apontador para o inicio da lista ligada dos clientes.
 * @inteiro cod contribuinte sujeito á verificação.
 * @return retorna 1 se o contribuite existir e 0 se nao existir.
 */

int haCliente(Clientes* comeco, int cod) {
	while (comeco != NULL)
	{
		if (comeco->contribuinte == cod) return(1);
		comeco = comeco->next;
	}
	return(0);
}

int guardarAluguer(Aluguer* inicio) {
	return 0;
}

int loginClientes(Clientes* comeco) {
	char codigo[50];
	char pass[12];
	getchar();
	printf("\nNome de Identificação: ");
	fgets(codigo, 50, stdin);
	printf("Password: ");
	fgets(pass, 12, stdin);

	Clientes* temp = comeco;
	while (temp != NULL) {
		if (strcmp(temp->utilizador, codigo) == 0 && strcmp(temp->password, pass) == 0) {
			// Credentials match
			return 1;
		}
		temp = temp->next;
	}

	// No match found
	return 0;
}

int menuAcesso(Clientes* cliente, Meio* meios)
{
	while (cliente != NULL) {

	}
	return 0;
}

int guardarClientes(Clientes* inicio)
{
	FILE* fp;
	fp = fopen("clientes.txt", "w");
	if (fp != NULL)
	{
		Clientes* aux = inicio;
		while (aux != NULL)
		{
			fprintf(fp, "%s;%d;%s;%s;%s;%f\n", aux->nome, aux->contribuinte, aux->utilizador, aux->password, aux->morada, aux->saldo);
			aux = aux->next;
		}
		fclose(fp);
		return(1);
	}
	else return(0);
}

void listarClientes(Clientes* comeco) {
	while (comeco != NULL)
	{
		printf("%s %d %s %s %f\n", comeco->nome, comeco->contribuinte, comeco->utilizador, comeco->morada, comeco->saldo);
		comeco = comeco->next;
	}
	if (comeco == NULL) {
		printf("Não ha lista de clientes!");
	}
}

/**
 * Abertura de ficheiro e inserção na estrutura.
 *
 * Nesta função, abrimos um ficheiro que, se existir, tem os registos dos clientes existentes e
 * guardamos dentro de uma estrutura do tipo cliente auxiliar.
 *
 * @return devolve .
 */

 /*Clientes* clientesExistentes() {
	 FILE* arquivo = fopen("clientes.txt", "r");
	 if (arquivo == NULL) {
		 printf("Não encontramos a base de dados\n");
		 return NULL;
	 }

	 Clientes* inicio = NULL;
	 Clientes* novoCliente;
	 Clientes* ultimoCliente = NULL;

	 while (!feof(arquivo)) {
		 novoCliente = (Clientes*)malloc(sizeof(Clientes));
		 if (sscanf(arquivo, "%[^;];%i;%[^;];%[^;];%[^;];%f", novoCliente->nome, &novoCliente->contribuinte, novoCliente->utilizador, novoCliente->password, novoCliente->morada, &novoCliente->saldo) == 6) {
			 novoCliente->next = NULL;

			 if (inicio == NULL) {
				 inicio = novoCliente;
			 }
			 else {
				 ultimoCliente->next = novoCliente;
			 }

			 ultimoCliente = novoCliente;
		 }
		 else {
			 free(novoCliente);
		 }
	 }

	 fclose(arquivo);

	 return inicio;
 }*/

Clientes* readDataFromFile() {
	FILE* file = fopen("clientes.txt", "r");
	if (file == NULL) {
		printf("Failed to open the file.\n");
		return NULL;
	}

	Clientes* inicio = NULL;
	Clientes* aux = NULL;
	char line[200];

	while (fgets(line, sizeof(line), file) != NULL) {
		// Allocate memory for a new node
		aux = (Clientes*)malloc(sizeof(Clientes));
		if (aux == NULL) {
			printf("Memory allocation error.\n");
			return inicio;
		}

		// Parse the line and populate the new node
		sscanf(line, "%[^;];%d;%[^;];%[^;];%[^;];%f",
			aux->nome, &aux->contribuinte, aux->utilizador,
			aux->password, aux->morada, &aux->saldo);
		aux->next = NULL;

		// Add the new node to the linked list
		if (inicio == NULL) {
			inicio = aux;
		}
		else {
			Clientes* temp = inicio;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = aux;
		}
	}

	fclose(file);
	return inicio;
}