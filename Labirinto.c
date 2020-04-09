#include "Labirinto.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define VISITADO 0
#define VAZIO 49
#define OBSTACULO 51
#define numCACHORRO 64

char **CriaLabirinto(FILE *fp, int Nlinhas, int Ncolunas){
    char **labirinto,linha[100];
    int   i;

    /* alocando a linha do labirinto*/
    labirinto = (char **)malloc(Nlinhas * sizeof(char *));
    if (labirinto == NULL) {
        printf("** Erro: Memoria Insuficiente **\n");
        return (NULL);
    }
    /* alocando as colunas do labirinto */
    for ( i = 0; i < Nlinhas; i++ ) {
        labirinto[i] = (char *)malloc(Ncolunas * sizeof(char));
        if (labirinto[i] == NULL) {
            printf ("** Erro: Memoria Insuficiente **\n");
            return (NULL);
        }
    }
    /*Lendo o labirinto do arquivo de texto*/
    for(i=0;i<Nlinhas;i++){
        fscanf(fp,"%s",&linha);
        strcpy(labirinto[i],linha);
    }
    fclose(fp);
    return (labirinto);
}

void ImprimeLabirinto(char **labirinto, int *cachorro, int Nlinhas, int Ncolunas){
    int i,j;

    for(i=0;i<(Ncolunas*2)+2;i++)
        printf("-");
    putchar('\n');

    labirinto[cachorro[0]][cachorro[1]] = '@';
    for(i=0;i<Nlinhas;i++){
        for(j=0;j<Ncolunas;j++){
            if(j == 0){
                if(labirinto[i][j] == VAZIO || labirinto[i][j] == VISITADO)
                    printf("|  ");
                else if(labirinto[i][j] == OBSTACULO)
                    printf("|* ");
                else if(labirinto[i][j] == numCACHORRO)
                    printf("|@ ");
            }else{
                if(labirinto[i][j] == VAZIO || labirinto[i][j] == VISITADO)
                    printf("  ");
                else if(labirinto[i][j] == OBSTACULO)
                    printf("* ");
                else if(labirinto[i][j] == numCACHORRO)
                    printf("@ ");
            }
        }
        printf("|\n");
    }
    for(i=0;i<(Ncolunas*2)+2;i++)
        printf("-");
}

void ProcuraCachorro(int *cachorro, char **labirinto, int Nlinhas, int Ncolunas){
    int i,j;

    for(i=0;i<Nlinhas;i++){
        for(j=0;j<Ncolunas;j++){
            if(labirinto[i][j] == 50){//número 2 na tabela ascii
                cachorro[0] = i;
                cachorro[1] = j;
            }
        }
    }
}

void MovimentaCachorro(char **labirinto, int *cachorro, int i, int j, int Nlinhas, int Ncolunas, int *sair,
                                    int *qtdMovimentos, int *rMAX, int *MAX){

    cachorro[0] = i;
    cachorro[1] = j;
    printf("Linha: %d | Coluna: %d\n",i,j);
    if(i == 0){
        *sair = EXIT_SUCCESS;
        return;
    }

    #if(ANALISE == 1)
        (*MAX)++;
    #endif

    (*qtdMovimentos)++;
    labirinto[i][j] = VISITADO;//marcando a posição já visitada

    if(*sair == EXIT_FAILURE && labirinto[i-1][j] == VAZIO)//para cima
        MovimentaCachorro(labirinto,cachorro,i-1,j,Nlinhas,Ncolunas,sair,qtdMovimentos,rMAX,MAX);

    if(*sair == EXIT_FAILURE && j-1 >= 0 && labirinto[i][j-1] == VAZIO)//para esquerda
        MovimentaCachorro(labirinto,cachorro,i,j-1,Nlinhas,Ncolunas,sair,qtdMovimentos,rMAX,MAX);

    if(*sair == EXIT_FAILURE && j+1 < Ncolunas && labirinto[i][j+1] == VAZIO)//para direita
        MovimentaCachorro(labirinto,cachorro,i,j+1,Nlinhas,Ncolunas,sair,qtdMovimentos,rMAX,MAX);

    if(*sair == EXIT_FAILURE && i+1 < Nlinhas && labirinto[i+1][j] == VAZIO)//ṕara baixo
        MovimentaCachorro(labirinto,cachorro,i+1,j,Nlinhas,Ncolunas,sair,qtdMovimentos,rMAX,MAX);

    #if(ANALISE == 1)
        if(*rMAX < *MAX)
            *rMAX = *MAX;

        (*MAX)--;
    #endif
}
