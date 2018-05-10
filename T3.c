#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int** AlocarMatrizRecurso(int linhas);
int flood_fill(int linha, int coluna, int v[9][9], int contador);

int main(int argc, char const *argv[]){
	int mapa[9][9] = {0}, jogador1[2] = {0}, jogador2[2] = {0}, nRec = 0;
	int** posRec;
	
	for (int i = 0; i < 9; ++i){
		for (int j = 0; j < 9; ++j){
			scanf("%d", &mapa[i][j]);
		}
	}

	scanf("%d %d", &jogador1[0], &jogador1[1]);
	scanf("%d %d", &jogador2[0], &jogador2[1]);
	scanf("%d", &nRec);

	posRec = AlocarMatrizRecurso(nRec);

	for (int i = 0; i < nRec; ++i){
		for (int j = 0; j < 2; ++j){
			scanf("%d", &posRec[i][j]);
		}
	}

	flood_fill(jogador1[0], jogador1[1], mapa, 0);

	printf("%d\n", flood_fill(jogador1[0], jogador1[1], mapa, 0));

	return 0;
}

int** AlocarMatrizRecurso(int linhas){
	int** v;
	v = (int**) calloc(linhas, sizeof(int*));
	for (int i = 0; i < linhas; ++i){
		v[i] = (int*) calloc(2, sizeof(int));
	}
	return v;
}

int flood_fill(int linha, int coluna, int v[9][9], int contador){
	if(v[linha][coluna] == 1) return;

	v[linha][coluna] = 1;

	if(linha-1>-1)flood_fill(linha-1, coluna, v, contador+1);
	if(linha+1<9)flood_fill(linha+1, coluna, v, contador+1);
	if(coluna-1>-1)flood_fill(linha, coluna-1, v, contador+1);
	if(coluna+1<9)flood_fill(linha, coluna+1, v, contador+1);

	return contador;
}
/*
Entrada:
0 1 0 0 0 0 0 0 0
0 1 0 0 0 0 0 0 0
0 1 0 0 0 0 0 0 0
0 1 1 1 1 1 1 1 1
0 0 0 0 0 0 0 0 0
1 1 1 1 1 1 1 1 0
0 0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 1 0
0 0
8 8
1
4 4

Saída:
0.152542
0.152542
O mapa eh balanceado
*/