#ifndef _MEIO_H
#define _MEIO_H

#include <stdlib.h>
#include <string.h>


typedef struct registo{
	int codigo;
	char tipo[25];
	int autonomia;
	float carga;
	char localizacao[100];
	int alugada;
	struct registo* next;
}Meio;

Meio* novoRegisto(Meio* comeco, int cod, char typ[], int auton, float charge, char local[], int alug);
void listarRegisto(Meio* comeco);
int haMeio(Meio* comeco, int cod);
Meio* removerMeio(Meio* comeco, int cod);
Meio* lerMeios();
Meio* removerMeio(Meio* comeco, int cod);
Meio* lerMeios();
void meiosDisponiveis(Meio* comeco);
int guardarMeios(Meio* inicio);
Meio* desalugar(Meio* inicio, int cod);
Meio* mudarAlugar(Meio* inicio, int cod);
void listarMeiosPorLocalizacao(Meio* inicio);
Meio* searchLocationMean(Meio* head, const char* location);

#endif