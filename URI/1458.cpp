// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1458
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#define MAXN 1001
#define endl '\n'
using namespace std;
double dp[13][13][MAXN];
int vetor[MAXN],X[MAXN],Y[MAXN],contador,teclas;
double custo[MAXN][MAXN];
double solve(int esq,int dir,int davez){
	if(dp[esq][dir][davez] >= 0) return dp[esq][dir][davez];
	if(davez == teclas + 1) return 0.0;
	int proximo = vetor[davez];
	return dp[esq][dir][davez] = 0.2 + min( custo[esq][proximo] + solve(proximo,dir,davez+1), custo[dir][proximo] + solve(esq,proximo,davez+1) ); 
}
int main(){
	for(int i=1;i<=4;i++){
		for(int j=1;j<=3;j++){
			X[++contador] = i;
			Y[contador] = j;
		}
	}
	for(int i=1;i<=12;i++){
		for(int j=1;j<=12;j++){
			custo[i][j] = hypot(X[i] - X[j], Y[i] - Y[j])/30.0;
		}
	}
	string entrada;
	while(getline(cin,entrada)){
		teclas = 0;
		for(int i=0;i<entrada.size();i++){
			char c = entrada[i];
			if(c == 'a' || c == 'b' || c == 'c'){
				int tipo = 2;
				int qtd = c - 'a' + 1;
				if(teclas > 0 && vetor[teclas] == tipo) vetor[++teclas] = 12;
				while(qtd--) vetor[++teclas] = tipo;
			}
			else if(c == 'd' || c == 'e' || c == 'f'){
				int tipo = 3;
				int qtd = c - 'd' + 1;
				if(teclas > 0 && vetor[teclas] == tipo) vetor[++teclas] = 12;
				while(qtd--) vetor[++teclas] = tipo;
			}
			else if(c == 'g' || c == 'h' || c == 'i'){
				int tipo = 4;
				int qtd = c - 'g' + 1;
				if(teclas > 0 && vetor[teclas] == tipo) vetor[++teclas] = 12;
				while(qtd--) vetor[++teclas] = tipo;
			}
			else if(c == 'j' || c == 'k' || c == 'l'){
				int tipo = 5;
				int qtd = c - 'j' + 1;
				if(teclas > 0 && vetor[teclas] == tipo) vetor[++teclas] = 12;
				while(qtd--) vetor[++teclas] = tipo;
			}
			else if(c == 'm' || c == 'n' || c == 'o'){
				int tipo = 6;
				int qtd = c - 'm' + 1;
				if(teclas > 0 && vetor[teclas] == tipo) vetor[++teclas] = 12;
				while(qtd--) vetor[++teclas] = tipo;
			}
			else if(c == 'p' || c == 'q' || c == 'r' || c == 's'){
				int tipo = 7;
				int qtd = c - 'p' + 1;
				if(teclas > 0 && vetor[teclas] == tipo) vetor[++teclas] = 12;
				while(qtd--) vetor[++teclas] = tipo;
			}
			else if(c == 't' || c == 'u' || c == 'v'){
				int tipo = 8;
				int qtd = c - 't' + 1;
				if(teclas > 0 && vetor[teclas] == tipo) vetor[++teclas] = 12;
				while(qtd--) vetor[++teclas] = tipo;
			}
			else if(c == 'w' || c == 'x' || c == 'y' || c == 'z'){
				int tipo = 9;
				int qtd = c - 'w' + 1;
				if(teclas > 0 && vetor[teclas] == tipo) vetor[++teclas] = 12;
				while(qtd--) vetor[++teclas] = tipo;
			}
			else if(c == ' '){
				int tipo = 11;
				vetor[++teclas] = tipo;
			}
		}
		//for(int i=1;i<=teclas;i++){
		//	printf("%d ",vetor[i]);
		//}
		//printf("\n");
		memset(dp,-1.0,sizeof(dp));
		printf("%.2lf\n",solve(4,6,1));
	}
	return 0;
}
