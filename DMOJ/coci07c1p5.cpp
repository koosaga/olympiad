// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci07c1p5
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
int resp,vetor[MAXN],alvo,n,posicao;
map<int,int> antesimpar,antespar,depoisimpar,depoispar;
int main(){
	scanf("%d %d",&n,&alvo);
	for(int i = 1;i<=n;i++){
		scanf("%d",&vetor[i]);
		if(vetor[i] == alvo) posicao = i;
	}
	antespar[0]++;
	depoispar[0]++;
	int qtd = 0,m =0;
	for(int i = posicao - 1;i >= 1;i--){
		m++;
		if(vetor[i] > alvo){
			qtd++;
		}
		else{
			qtd--;
		}
		if(m % 2 == 0) antespar[qtd]++;
		else antesimpar[qtd]++;
		//printf("%d %d\n",qtd,m);
	}
	qtd = 0;
	m = 0;
	for(int i = posicao + 1;i <= n;i++){
		m++;
		if(vetor[i] > alvo){
			qtd++;
		}
		else{
			qtd--;
		}
		if(m % 2 == 0) depoispar[qtd]++;
		else depoisimpar[qtd]++;
		//printf("%d %d\n",qtd,m);
	}
	for(auto it : depoispar){
		int v = it.first;
		int u = it.second;
		if(antespar.count(-v)){
			//printf("par V %d %d\n",v,antespar[-v]*u);
			resp += antespar[-v]*u;
		}
	}
	for(auto it : depoisimpar){
		int v = it.first;
		int u = it.second;
		if(antesimpar.count(-v)){
			//printf("impar V %d %d\n",v,antesimpar[-v]*u);
			resp += antesimpar[-v]*u;
		}
	}
	printf("%d\n",resp);
	return 0;
}