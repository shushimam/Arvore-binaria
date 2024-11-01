#ifndef FUNCOES_MAN
#define FUNCOES_MAN

#include "structs.h"


void insert_lote(FILE* fr, FILE* fbCurso,FILE* fbDisc, FILE* fbDist, FILE* fbProfessor);

void ler_arquivoTexto_curso(FILE* fr, FILE* fbCurso);

void ler_arquivoTexto_disc(FILE* fr, FILE* fbDisciplina);

void ler_arquivoTexto_professsor(FILE* fr, FILE* fbProfessor);

void ler_arquivoTexto_dist(FILE* fr, FILE* fbDist);





#endif