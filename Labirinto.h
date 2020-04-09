#include <stdio.h>
/*1 para ativado
  0 para desativado*/
#define ANALISE 1

char **CriaLabirinto(FILE *fp, int Nlinhas, int Ncolunas);//Lê o arquivo texto, aloca dinâmicamente a matriz e retorna o ponteiro para o labirinto
void ImprimeLabirinto(char **labirinto, int *cachorro, int Nlinhas, int Ncolunas);//Imprime o labirinto em um formato legível
void ProcuraCachorro(int *cachorro, char **labirinto, int Nlinhas, int Ncolunas);//faz a busca pelo cachorro dentro da matriz

void MovimentaCachorro(char **labirinto, int *cachorro, int i, int j, int Nlinhas, int Ncolunas,int *sair, int *qtdMovimentos, int *rMAX, int *MAX);
/*A função recursiva MovimentaCachorro é o algoritmo backtracking que encontra a saída do cachorro do labirinto inserido*/
