#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "funcoes_man.h"
#include "funcoes_arq.h"

int main(){
    FILE * fb_cursos = open_arq("cursos.bin");
    FILE* arq_txt;
    char txt[20];
    printf("digite o nome do arquivo: ");
    scanf("%[^\n]%*c",txt);
    arq_txt = fopen(txt,"r");

    ler_arquivoTexto_curso(arq_txt, fb_cursos);

    return 0;
}