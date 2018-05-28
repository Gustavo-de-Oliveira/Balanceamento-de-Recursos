#include <stdio.h>
#include <stdlib.h>

int** AlocarMatrizRecurso(int linhas);
void flood_fill(int linha, int coluna, int v[9][9], int* contador, int* cobertura, int** posRec, int nRec);

int main(int argc, char const *argv[]){
	int mapa[9][9] = {0}, mapa2[9][9] = {0}, jogador1[2] = {0}, jogador2[2] = {0}, nRec = 0, contador = 0, contadorZero = 0, cobertura = 0;
	double Ejogador1 = 0.0, Ejogador2 = 0.0;
	int **posRec;
	
	for (int i = 0; i < 9; ++i){//Recebe o mapa do jogo, uma matriz 9x9
		for (int j = 0; j < 9; ++j){
			
			scanf("%d", &mapa[i][j]);
			mapa2[i][j] = mapa[i][j];//A mesma matriz é copiada para um mapa auxiliar que será usado para o cálculo com o jogador 2

			if (mapa[i][j] == 0){
				contadorZero++;//Conta a quantidade de locais tranponíveis no mapa
			}
		}
	}

	scanf("%d %d", &jogador1[0], &jogador1[1]);//Recebe a localização do jogador 1
	scanf("%d %d", &jogador2[0], &jogador2[1]);//Recebe a localização do jogador 2
	scanf("%d", &nRec);

	posRec = AlocarMatrizRecurso(nRec);//Aloca a matriz com as posições dos recursos na heap

	for (int i = 0; i < nRec; ++i){
		for (int j = 0; j < 2; ++j){
			scanf("%d", &posRec[i][j]);//Lê as posições dos recursos
		}
	}

	flood_fill(jogador1[0], jogador1[1], mapa, &contador, &cobertura, posRec, nRec);

	Ejogador1 = (1/(double)nRec) * ((double)cobertura/(double)contadorZero);//E = 1/(N-1) 'Somatório' (e1 i->j)/P

	printf("%f\n", Ejogador1);

	cobertura = 0;
	contador = 0;

	flood_fill(jogador2[0], jogador2[1], mapa2, &contador, &cobertura, posRec, nRec);
	
	Ejogador2 = (1/(double)nRec) * ((double)cobertura/(double)contadorZero);////E = 1/(N-1) 'Somatório' (e2 i->j)/P

	printf("%f\n", Ejogador2);

	if (Ejogador1 > Ejogador2){
		printf("O jogador 2 possui vantagem\n");
	}
	else if (Ejogador2 > Ejogador1){
		printf("O jogador 1 possui vantagem\n");
	} else{
		printf("O mapa eh balanceado\n");
	}

	for (int i = 0; i < nRec; ++i){//Libera o espaço na heap
		free(posRec[i]);
	}
	free(posRec);

	return 0;
}

int** AlocarMatrizRecurso(int linhas){//função para alocar matrizes na memória heap
	int** v;
	v = (int**) calloc(linhas, sizeof(int*));
	for (int i = 0; i < linhas; ++i){
		v[i] = (int*) calloc(2, sizeof(int));
	}
	return v;
}

void flood_fill(int linha, int coluna, int v[9][9], int* contador, int* cobertura, int** posRec, int nRec){
	if(v[linha][coluna] == 1) return;//verifica se o local é transponível

	v[linha][coluna] = 1;//Seta o local como intrasnponível
	*contador = *contador + 1;//Incrementa o número de passos

	//Soma a quantidade de passos toda vez que encontra um recurso no mapa, numerador na soma
	for (int i = 0; i < nRec; ++i){
		if(linha == posRec[i][0] && coluna == posRec[i][1]){
			*cobertura = *contador + *cobertura;
		}
	}

	if(linha+1<9)flood_fill(linha+1, coluna, v, contador, cobertura, posRec, nRec);//Move para o sul
	if(linha-1>-1)flood_fill(linha-1, coluna, v, contador, cobertura, posRec, nRec);//Move para o norte
	if(coluna-1>-1)flood_fill(linha, coluna-1, v, contador, cobertura, posRec, nRec);//Move para o oeste
	if(coluna+1<9)flood_fill(linha, coluna+1, v, contador, cobertura, posRec, nRec);//Move para o leste
}