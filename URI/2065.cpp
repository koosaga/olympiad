// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/2065
#include <cstdio>
#include <queue>
#include <algorithm>
#define MAXN 10000
#define MP make_pair
using namespace std;
typedef pair<int,int> pii;
priority_queue<pii, vector<pii>, greater<pii> > fila;
int tempos[MAXN],caixas,clientes,momento;
int main(){
	scanf("%d %d",&caixas,&clientes);
	for(int i=0;i<caixas;i++) {
		scanf("%d",&tempos[i]);
		fila.push(MP(0,i));
	}
	while(clientes--){
		int quantidade;
		scanf("%d",&quantidade);
		int instante = fila.top().first, id = fila.top().second;
		fila.pop();
		int proximo = instante + quantidade*tempos[id];
		momento = max(proximo,momento);
		fila.push(MP(proximo,id));
	}
	printf("%d\n",momento);
	return 0;
}
