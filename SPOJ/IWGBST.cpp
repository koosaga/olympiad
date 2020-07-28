// Ivan Carvalho
// Solution to https://www.spoj.com/problems/IWGBST/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 5*1e5 + 10;

int grau[MAXN],vaipara[MAXN],tamanho[MAXN],marcado[MAXN],N,C,D;
ll A,B;

ll gcd(ll x,ll y){
	if(x < y) swap(x,y);
	if(y == 0) return x;
	return gcd(y,x % y);
}

ll lcm(ll x,ll y){
	return x*(y/gcd(x,y));
}

ll conta(ll X){
	if(X <= 0) return 0;
	ll periodo = 1;
	for(int i = 1+C;i<=N-D;i++){
		if(tamanho[i] == -1) return 1;
		periodo = lcm(periodo,tamanho[i]);
		if(periodo > X) return 1;
	}
	return ((X-1)/periodo) + 1;
}

int main(){

	scanf("%d %lld %lld %d %d",&N,&A,&B,&C,&D);
	for(int i = 1;i<=N;i++){
		scanf("%d",&vaipara[i]);
		grau[vaipara[i]]++;
	}

	queue<int> fila;
	for(int i = 1;i<=N;i++) if(grau[i] == 0) fila.push(i);
	while(!fila.empty()){
		int v = fila.front();
		fila.pop();
		marcado[v] = 1;
		tamanho[v] = -1;
		int u = vaipara[v];
		grau[u]--;
		if(grau[u] == 0) fila.push(u);
	}

	for(int i = 1;i<=N;i++){
		if(marcado[i]) continue;
		marcado[i] = 1;
		int j = vaipara[i];
		tamanho[i] = 1;
		while(j != i){
			tamanho[i]++;
			j = vaipara[j];
		}
		j = vaipara[i];
		while(j != i){
			tamanho[j] = tamanho[i];
			marcado[j] = 1;
			j = vaipara[j];
		}
	}

	printf("%lld\n",conta(B) - conta(A-1));

	return 0;
}
