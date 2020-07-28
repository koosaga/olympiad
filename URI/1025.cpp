// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1025
#include <cstdio>
#include <algorithm>
#define MAXN 100100
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
int n,m,vetor[MAXN],caso=1;
int buscab(int x){
	int ini=1;
	int fim=n;
	int meio;
	while (ini <= fim){
		meio = (ini+fim)/2;
		if (vetor[meio]==x && vetor[meio-1]!=x) return meio;
		if (vetor[meio]<x) ini = meio+1;
		else fim = meio-1;
	}
	return -1;
}
int main(){
	vetor[0]=10001;
	while(1){
		getint(n);
		getint(m);
		if (n==0 && m == 0) break;
		printf("CASE# %d:\n",caso++);
		for(int i=1;i<=n;i++) getint(vetor[i]);
		sort(vetor+1,vetor+n+1);
		for(int i=1;i<=m;i++){
			int davez,resposta;
			getint(davez);
			resposta = buscab(davez);
			if (resposta==-1) printf("%d not found\n",davez);
			else printf("%d found at %d\n",davez,resposta);
		}
	}
	return 0;
}
