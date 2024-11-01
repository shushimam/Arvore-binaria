#ifndef FUNCOES_H
#define FUNCOES_H

#include "structs.h"

FILE* open_arq(char* str);

void escreveCabecalho(FILE * fb, Cabecalho * cab);

Cabecalho * lerCabecalho(FILE * fb);

void insere_curso(FILE * fb_ListaCurso, InfosCurso info);

void insere_dist(FILE * fb_ListaDist, infoDist info);

void insere_professor(FILE * fb_ListaProfs, infoProf info);

void insere_disc(FILE * fb_ListaDisc, infoDisc info);

void insere_curso(FILE * fb_ListaCurso, InfosCurso info);

int buscar_produto(FILE* f, int codigo);

int buscar_produto_aux(FILE* f, int raiz, int codigo);

void inserir_produto(FILE* f, InfosCurso* p);

#endif