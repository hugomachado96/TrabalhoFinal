#ifndef _GRAFO_H_
#define _GRAFO_H_


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "meio.h"
#include "cliente.h"

typedef struct Node {
	char vertex[100];
	Meio* meios;
	Clientes* clientes;
	struct Node* next;
}node;

typedef struct Graph {
	int numVertices;
	int maxVeertices;
	struct Node** adjLists;
	int** weights;
}graph;

graph* createAGraph(int vertices, int maxVertice);
node* createNode(char* v, Meio* meios, Clientes* cliente);
void addEdge(graph* graph, char* s, char* d, int weight, Meio* meios, Clientes* cliente);
void addNodeToList(node** head, node* newNode);


#endif