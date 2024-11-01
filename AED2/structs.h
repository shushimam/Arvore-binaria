#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct{
    char nome[30];
    char area;
    int codigo;
}InfosCurso;

typedef struct {
    int codigo;
    char nome[30];
}infoProf;

typedef struct {
    int cod_disc;   
    char nome_disc[30];
    int cod_curso;
    int serie;
}infoDisc;

typedef struct {
    int codigo_professor;
    char ano_letivo[6];
    char codigo_disciplina[3];
    char codigo_dist[6];
}infoDist;

typedef struct{
    int posCabeca;//raiz
    int posTopo;  //vazio
    int posLivre; //livre
}Cabecalho;


typedef struct{
    InfosCurso info;
    int pos_esq;
    int pos_dir;
}ListaCurso;

typedef struct{
    infoDist info;
    int pos_esq;
    int pos_dir;
}ListaDistribuicao;

typedef struct{
    infoProf info;
    int pos_esq;
    int pos_dir;
}ListaProfessor;        

typedef struct{
    infoDisc info;
    int pos_esq;
    int pos_dir;
}ListaDisc;

#endif