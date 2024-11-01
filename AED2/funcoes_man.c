#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs.h"
#include "funcoes_man.h"
#include "funcoes_arq.h"

void insert_lote(FILE* fr, FILE* fbCurso,FILE* fbDisc, FILE* fbDist, FILE* fbProfessor){
    char categoria;

    while(fscanf(fr,"%c;", &categoria) != EOF){
        
        if(categoria=='C'){
            ler_arquivoTexto_curso(fr, fbCurso);
        }
      /**   else if(categoria =='D'){
           // ler_arquivoTexto_disc(fr,fbDisc);
         }
        else if(categoria =='P'){
           // ler_arquivoTexto_professsor(fr,fbProfessor);
        }
        else if(categoria =='M'){
           // ler_arquivoTexto_dist(fr,fbDist);
        }*/
    }
}

void ler_arquivoTexto_curso(FILE* fr, FILE* fbCurso){
    InfosCurso aux;

    fscanf(fr, "%d;", &aux.codigo);
    fscanf(fr, "%[^;]%*c", aux.nome);
    fscanf(fr, "%c\n", &aux.area);
    printf("%d %s %c", aux.codigo,aux.nome,aux.area);
    inserir_produto(fbCurso, &aux);
}
/*
void ler_arquivoTexto_disc(FILE* fr, FILE* fbDisciplina){
    infoDisc aux;

    fscanf(fr,"%d;",&aux.cod_disc);
    fscanf(fr,"%[^;]%*c",aux.nome_disc);
    fscanf(fr,"%d;",&aux.cod_curso);
    fscanf(fr,"%d\n",&aux.serie);
//    if(!verifica_disc(fbDisciplina,aux))
//    insere_disc(fbDisciplina,aux);
}

void ler_arquivoTexto_professsor(FILE* fr, FILE* fbProfessor){
    infoProf aux;

    fscanf(fr,"%d;",&aux.codigo);
    fscanf(fr,"%[^\n]%*c",aux.nome);
//    if(!verifica_prof(fbProfessor,aux))
//    insere_professor(fbProfessor,aux);
}

void  ler_arquivoTexto_dist(FILE* fr, FILE* fbDist){
    infoDist aux;

    fscanf(fr,"%[^;]%*c",&aux.codigo_disciplina);
    fscanf(fr,"%[^;]%*c",&aux.ano_letivo);
    fscanf(fr,"%d\n",&aux.codigo_professor);
    strcat(aux.codigo_dist,aux.ano_letivo);
    strcat(aux.codigo_dist,aux.codigo_disciplina);
  //  if(!verifica_dist(fbDist,aux))
  //  insere_dist(fbDist,aux);
}
*/
