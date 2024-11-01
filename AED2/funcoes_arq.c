#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs.h"
#include "funcoes_arq.h"

FILE* open_arq(char* str){
    FILE* arq = fopen(str, "r+b");
    if(arq==NULL){
        arq = fopen(str, "w+b");
        Cabecalho* cab = (Cabecalho*) malloc(sizeof(Cabecalho));
        cab->posCabeca = -1;
        cab->posLivre = -1;
        cab->posTopo = 0;
        escreveCabecalho(arq, cab);
        free(cab);
    }
    return arq;
}

void escreveCabecalho(FILE * fb, Cabecalho * cab){
    fseek(fb, 0, SEEK_SET);
    fwrite(cab, sizeof(Cabecalho), 1, fb);
}

//Le o cabeçalho atual
Cabecalho * lerCabecalho(FILE * fb){
    Cabecalho *cab = (Cabecalho*)malloc(sizeof(Cabecalho));

    fseek(fb, 0, SEEK_SET);

    fread(cab, sizeof(Cabecalho), 1, fb);

    return cab;
}

/*
void insere_curso(FILE * fb_ListaCurso, InfosCurso info){
    Cabecalho * cab = lerCabecalho(fb_ListaCurso);
    ListaCurso aux;
    
    aux.info.codigo = info.codigo;                       //passa a info para o auxiliar
    strcpy(aux.info.nome,info.nome);              //copia um nome para o outro
    aux.info.area = info.area;

    aux.pos_dir = cab->posCabeca;//faz a esqueda e direita apontarem para onde começa a lista
    aux.pos_esq = cab->posCabeca;

    if(cab->posLivre == -1){ //não há nós livres
        escreve_curso(fb_ListaCurso, &aux, cab->posTopo);   //escreve o nó na proxima posição livre (topo)
        cab->posCabeca = cab->posTopo;
        cab->posTopo++;                                 //incrementa o topo
    }

    else {                  //usa nós livres
        ListaCurso * aux = leCurso(fb_ListaCurso,cab->posLivre);

        escreve_curso(fb_ListaCurso, aux, cab->posLivre);

        cab->posCabeca = cab->posLivre;
        cab->posLivre = aux->pos_esq;

        free (aux);
    }
    escreveCabecalho(fb_ListaCurso, cab); free(cab);
}*/

void link_no(FILE* f, int raiz, int pos, int codigo){
    ListaCurso* aux = (ListaCurso*) malloc(sizeof(ListaCurso));
    fseek(f, sizeof(Cabecalho)+sizeof(ListaCurso)*raiz, SEEK_SET);
    fread(aux, sizeof(ListaCurso), 1, f);

    // Código à esquerda do nó atual
    if(codigo < aux->info.codigo){
        // O novo nó será filho esquerdo do nó atual
        if(aux->pos_esq==-1){
            aux->pos_esq = pos;
            fseek(f, sizeof(Cabecalho)+sizeof(ListaCurso)*raiz, SEEK_SET);
            fwrite(aux, sizeof(ListaCurso), 1, f);
            free(aux);
        }
        else{
            int pos_aux = aux->pos_esq;
            free(aux);
            link_no(f, pos_aux, pos, codigo);
        }
    }

    // Código à direita do nó atual
    if(codigo > aux->info.codigo){
        // O novo nó será filho direito do nó atual
        if(aux->pos_dir==-1){
            aux->pos_dir = pos;
            fseek(f, sizeof(Cabecalho)+sizeof(ListaCurso)*raiz, SEEK_SET);
            fwrite(aux, sizeof(ListaCurso), 1, f);
            free(aux);
        }
        else{
            int pos_aux = aux->pos_dir;
            free(aux);
            link_no(f, pos_aux, pos, codigo);
        }

    }

    if(codigo == aux->info.codigo) free(aux);
}


int buscar_produto_aux(FILE* f, int raiz, int codigo){
    if(raiz==-1) return -1;
    ListaCurso* aux = (ListaCurso*) malloc(sizeof(ListaCurso));
    fseek(f, sizeof(Cabecalho)+sizeof(ListaCurso)*raiz, SEEK_SET);
    fread(aux, sizeof(ListaCurso), 1, f);

    if(aux->info.codigo==codigo){
        free(aux);
        return raiz;
    }

    else{
        int pos;
        if(aux->info.codigo>codigo)
            pos=aux->pos_esq;
        else
            pos=aux->pos_dir;
        free(aux);
        return buscar_produto_aux(f, pos, codigo);
    }
}

int buscar_produto(FILE* f, int codigo){
    Cabecalho* cab = lerCabecalho(f);
    int pos = buscar_produto_aux(f, cab->posCabeca, codigo);
    free(cab);
    return pos;
}

void inserir_produto(FILE* f, InfosCurso* curso){
    if(buscar_produto(f, curso->codigo)==-1){
        Cabecalho* cab = lerCabecalho(f);

        // Novo nó é uma folha
        ListaCurso* r = (ListaCurso*) malloc(sizeof(ListaCurso));
        r->info = *curso;
        r->pos_dir = -1;
        r->pos_esq = -1;

        int pos;
        ListaCurso* aux = (ListaCurso*) malloc(sizeof(ListaCurso));

        // Há nós livres no arquivo
        if(cab->posLivre!=-1){
            fseek(f, sizeof(Cabecalho)+sizeof(ListaCurso)*cab->posLivre, SEEK_SET);
            fread(aux, sizeof(ListaCurso), 1, f);
            pos = cab->posLivre;
            cab->posLivre = aux->pos_dir;
        }

        else
            pos = (cab->posTopo)++;

        // Novo nó será a raiz da árvore
        if(cab->posCabeca==-1)
            cab->posCabeca = pos;

        fseek(f, sizeof(Cabecalho)+sizeof(ListaCurso)*pos, SEEK_SET);
        fwrite(r, sizeof(ListaCurso), 1, f);
        escreveCabecalho(f, cab);
        link_no(f, cab->posCabeca, pos, r->info.codigo);
        free(aux);
        free(curso);
        free(cab);
        free(r);
    }
}
