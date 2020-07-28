// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci07c5p4
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;

vector<int> grafo[MAXN];
int processado_numero[MAXN],processado_coluna[MAXN],frequencia[MAXN][3];
int vetor[MAXN][3],N,resposta;
queue<int> fila;

void processa_numero(int v){
	if(processado_numero[v]) return;
	processado_numero[v] = 1;
	for(int u : grafo[v]) fila.push(u);
}

int main(){

	scanf("%d",&N);
	for(int j = 0;j<3;j++){
		for(int i = 1;i<=N;i++){
			scanf("%d",&vetor[i][j]);
			frequencia[vetor[i][j]][j]++;
			grafo[vetor[i][j]].push_back(i);
		}
	}

	for(int i = 1;i<=N;i++){
		for(int j = 0;j<3;j++) if(frequencia[i][j] == 0) processa_numero(i);
	}

	while(!fila.empty()){

		int coluna = fila.front();
		fila.pop();
		if(processado_coluna[coluna]) continue;
		processado_coluna[coluna] = 1;
		resposta++;

		for(int j = 0;j<3;j++){
			frequencia[vetor[coluna][j]][j]--;
		}
		for(int j = 0;j<3;j++){
			for(int k = 0;k<3;k++){
				if(frequencia[vetor[coluna][j]][k] == 0) processa_numero(vetor[coluna][j]);
			}
		}

	}

	printf("%d\n",resposta);

	return 0;
}