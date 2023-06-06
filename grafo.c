#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string.h>

#define VERTICES 5

#include "grafo.h"

node* createNode(node* inicio, char* v, Meio* meios, Clientes* cliente) {
    node* newNode = malloc(sizeof(struct Node));
        strcpy(newNode->vertex, v);
        newNode->next = NULL;
        newNode->meios = searchLocationMean(meios, v);
        newNode->clientes = searchLocationClient(cliente, v);
        return newNode;
}

graph* createAGraph(int vertices, int maxVertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->maxVeertices = maxVertices;

    graph->adjLists = malloc(vertices * sizeof(struct node*));
    graph->weights = malloc(vertices * sizeof(int*));

    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->weights[i] = malloc(vertices * sizeof(int));
        memset(graph->weights[i], 0, vertices * sizeof(int)); // Inicializar a matriz de pesos com 0
    }

    return graph;
}

void addEdge(graph* graph, char* s, char* d, int weight, Meio* meios, Clientes* cliente, node* inicio) {
    // Encontrar os �ndices dos v�rtices s e d
    int indexS = -1;
    int indexD = -1;
    for (int i = 0; i < graph->numVertices; i++) {
        if (strcmp(graph->adjLists[i]->vertex, s) == 0) {
            indexS = i;
        }
        if (strcmp(graph->adjLists[i]->vertex, d) == 0) {
            indexD = i;
        }
        if (indexS != -1 && indexD != -1) {
            break;
        }
    }

    // Verificar se os v�rtices foram encontrados
    if (indexS == -1) {
        // O v�rtice s n�o existe, adicione-o ao grafo
        if (graph->numVertices >= graph->maxVeertices) {
            printf("Erro: Limite m�ximo de v�rtices atingido.\n");
            return;
        }
        node* newNodeS = createNode(inicio, s, meios, cliente);
        indexS = graph->numVertices; // �ndice do novo v�rtice
        graph->adjLists[indexS] = newNodeS;
        graph->numVertices++;
    }

    if (indexD == -1) {
        // O v�rtice d n�o existe, adicione-o ao grafo
        if (graph->numVertices >= graph->maxVeertices) {
            printf("Erro: Limite m�ximo de v�rtices atingido.\n");
            return;
        }
        node* newNodeD = createNode(inicio, d, meios, cliente);
        indexD = graph->numVertices; // �ndice do novo v�rtice
        graph->adjLists[indexD] = newNodeD;
        graph->numVertices++;
    }
    // Criar e adicionar o n� de s na lista encadeada
    node* newNodeS = createNode(inicio, s, meios, cliente);
    addNodeToList(&(graph->adjLists[indexS]), newNodeS);

    // Criar e adicionar o n� de d na lista encadeada
    node* newNodeD = createNode(inicio, d, meios, cliente);
    addNodeToList(&(graph->adjLists[indexD]), newNodeD);

    // Atualizar o peso da aresta na matriz de pesos
    graph->weights[indexS][indexD] = weight;
    graph->weights[indexD][indexS] = weight;
}

void addNodeToList(node** head, node* newNode) {
    if (*head == NULL) {
        *head = newNode;
    }
    else {
        node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}
