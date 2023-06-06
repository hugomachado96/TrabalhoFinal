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
			while (atual->next != NULL && contr > atual->contribuinte) {
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

Clientes* menuInicial(Clientes* inicio, Meio* inicial, Aluguer* comeco, struct Grafo* grafo, struct vertices* vertices) {
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
			break;
		case 2:
			system("cls");
			pog = loginClientes(inicio);
			if (pog == 1) {
				//adicionarLocalizacaoCliente(grafo, inicio, vertices);
				inicio = menuAcesso(inicio, inicial, comeco);
			}
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
	printf("3-Ver os meios numa localizacao.\n");
	printf("4-Aluguer\n");
	printf("0-Log Out\n");
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
	FILE* fp;
	fp = fopen("aluguer.txt", "w");
	if (fp != NULL)
	{
		Aluguer* aux = inicio;
		while (aux != NULL)
		{
			fprintf(fp, "%s;%i;%f;%f\n", aux->nome,aux->codigo, aux->custo, aux->tempo);
			aux = aux->next;
		}
		fclose(fp);
		return(1);
	}
	else return(0);
	return 0;
}

int loginClientes(Clientes* comeco) {
	char codigo[50];
	char pass[12];
	getchar();
	printf("\nNome de Identificação: ");
	fgets(codigo, 50, stdin);
	codigo[strcspn(codigo, "\n")] = '\0';
	printf("Password: ");
	fgets(pass, 12, stdin);
	pass[strcspn(pass, "\n")] = '\0';

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

int menuAcesso(Clientes* cliente, Meio* meios, Aluguer* inicio)
{
	int op, retorno;
	while (cliente != NULL) {
		do{
			op = menu2(cliente);
			switch(op){
				case 1:
					system("cls");
					retorno=adicionarSaldo(cliente);
					if (retorno == 1) printf("Saldo adicionado com sucesso!");
					else if (retorno == 0) printf("O nome de utilizador nao foi encontrado!");
					system("PAUSE");
					break;
				case 2:
					system("cls");
					meiosDisponiveis(meios);
					system("PAUSE");
					break;
				case 3:
					system("cls");
					listarMeiosPorLocalizacao(meios);
					break;
				case 4:
					system("cls");
					menuAluger(cliente, meios, inicio);
					break;
				case 0:
					system("cls");
					guardarClientes(cliente);
					printf("Volta Sempre!");
					system("PAUSE");
					break;
				default:
					system("cls");
					printf("Opcao Invalida! Escolhe uma das opções");
					break;
					return 0;
				}
		}while (op != 0);
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

int adicionarSaldo(Clientes* inicio){
	float saldo;
	char utilizador[50];
	printf("Introduza o seu nome de utilizador novamente:");
	getchar();
	fgets(utilizador, 50, stdin);
	utilizador[strcspn(utilizador, "\n")] = '\0';
	Clientes* temp=inicio;
	while (temp!= NULL){
		if(strcmp(temp->utilizador, utilizador) == 0){
			printf("Quanto saldo queres adicionar a tua conta");
			scanf("%f", &saldo);
			temp->saldo=saldo;
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}

/*int adicionarLocalizacaoCliente(struct Grafo* g, Clientes* cliente, struct Vertice* verticeSelecionado) {
	printf("Selecione a localizacao do cliente:\n");
	imprimirVertices(g);

	int opcao;
	printf("Opcao: ");
	scanf("%d", &opcao);

	verticeSelecionado = procurarVertice(g, opcao);
	if (verticeSelecionado == NULL) {
		printf("Localizacao nao encontrada!\n");
		return 0;
	}
	
	strcpy(cliente->localizacao, verticeSelecionado->localizacao);
	printf("Localizacao do cliente adicionada com sucesso!\n");
	return 1;
}
*/
Clientes* searchLocationClient(Clientes* head, const char* location) {
	Clientes* resultHead = NULL;
	Clientes* resultTail = NULL;

	// Percorrer a lista de Clientes
	Clientes* current = head;
	while (current != NULL) {
		// Verificar se a localização coincide
		if (strcmp(current->localizacao, location) == 0) {
			// Criar um novo nó com a localização correspondente
			Clientes* newNode = malloc(sizeof(Clientes));
			strcpy(newNode->nome, current->nome);
			newNode->contribuinte = current->contribuinte;
			strcpy(newNode->utilizador, current->utilizador);
			strcpy(newNode->password, current->password);
			strcpy(newNode->morada, current->morada);
			newNode->saldo = current->saldo;
			strcpy(newNode->localizacao, current->localizacao);
			newNode->next = NULL;

			// Adicionar o novo nó à lista de resultados
			if (resultHead == NULL) {
				resultHead = newNode;
				resultTail = newNode;
			}
			else {
				resultTail->next = newNode;
				resultTail = newNode;
			}
		}

		// Avançar para o próximo nó
		current = current->next;
	}

	return resultHead;
}

