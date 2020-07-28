// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1910
#include <cstdio>
#include <queue>
#define MP make_pair
#define MAXN 100000
using namespace std;
typedef pair<int,int> ii;
int processado[MAXN+1],iteracao,o,d,k;
int main(){
	while(scanf("%d %d %d",&o,&d,&k) && (o||d||k)){
		int possivel = 0;
		iteracao++;
		while(k--){
			int davez;
			scanf("%d",&davez);
			processado[davez] = iteracao;
		}
		queue<ii> fila;
		fila.push(MP(o,0));
		while(!fila.empty()){
			int v = fila.front().first, apertos = fila.front().second;
			fila.pop();
			if(v == d){
				possivel = 1;
				printf("%d\n",apertos);
				break;
			}
			if(processado[v] == iteracao) continue;
			processado[v] = iteracao;
			if(v % 2 == 0) fila.push(MP(v/2,apertos+1));
			if(v * 3 <= MAXN) fila.push(MP(v*3,apertos+1));
			if(v * 2 <= MAXN) fila.push(MP(v*2,apertos+1));
			if(v + 1 <= MAXN) fila.push(MP(v+1,apertos+1));
			if(v - 1 > 0) fila.push(MP(v-1,apertos+1));
		}
		if(!possivel) printf("-1\n");
	}
	return 0;
}
