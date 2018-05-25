#include <stdio.h>
#include <stdlib.h>

int** AlocarMatrizRecurso(int linhas);
void flood_fill(int linha, int coluna, int v[9][9], int* contador, int* cobertura, int** posRec, int nRec, int indice);

int main(int argc, char const *argv[]){
	int mapa[9][9] = {0}, jogador1[2] = {0}, jogador2[2] = {0}, nRec = 0, contador = 0;
	float Ejogador1 = 0.0, Ejogador2 = 0.0;
	int **posRec;
	
	for (int i = 0; i < 9; ++i){
		for (int j = 0; j < 9; ++j){
			scanf("%d", &mapa[i][j]);
		}
	}

	scanf("%d %d", &jogador1[0], &jogador1[1]);
	scanf("%d %d", &jogador2[0], &jogador2[1]);
	scanf("%d", &nRec);

	posRec = AlocarMatrizRecurso(nRec);
	int cobertura[nRec];

	for (int i = 0; i < nRec; ++i){
		for (int j = 0; j < 2; ++j){
			scanf("%d", &posRec[i][j]);
		}
	}

	flood_fill(jogador1[0], jogador1[1], mapa, &contador, cobertura, posRec, nRec, 0);

	float f, a;
	for (int i = 0; i < nRec; ++i){
		f = (float) 1/(nRec);
		a = (float) cobertura[i]/contador;
		Ejogador1 += (f*a);
	}

	printf("%.6f\n", Ejogador1);

	flood_fill(jogador2[0], jogador2[1], mapa, &contador, cobertura, posRec, nRec, 0);

	for (int i = 0; i < nRec; ++i){
		f = (float) 1/(nRec);
		a = (float) cobertura[i]/contador;
		Ejogador2 += (f*a);
	}

	printf("%.6f\n", Ejogador2);

	if (Ejogador1 > Ejogador2){
		printf("O jogador 2 possui vantagem\n");
	}
	else if (Ejogador2 > Ejogador1){
		printf("O jogador 1 possui vantagem\n");
	} else{
		printf("O mapa eh balanceado\n");
	}

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

void flood_fill(int linha, int coluna, int v[9][9], int* contador, int* cobertura, int** posRec, int nRec, int indice){
	if(v[linha][coluna] == 1) return;

	v[linha][coluna] = 1;
	*contador = *contador + 1;

	for (int i = 0; i < nRec; ++i){
		if(linha == posRec[i][0] && coluna == posRec[i][1]){
			cobertura[indice] = *contador;
			indice++;
		}
	}

	if(linha-1>-1)flood_fill(linha-1, coluna, v, contador, cobertura, posRec, nRec, indice);
	if(linha+1<9)flood_fill(linha+1, coluna, v, contador, cobertura, posRec, nRec, indice);
	if(coluna-1>-1)flood_fill(linha, coluna-1, v, contador, cobertura, posRec, nRec, indice);
	if(coluna+1<9)flood_fill(linha, coluna+1, v, contador, cobertura, posRec, nRec, indice);
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