// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1382
#include <cstdio>
#include <algorithm>
#define MAXN 10010
using namespace std;
int vetor[MAXN],n,TC,trocas,pos[MAXN];
int main(){
	scanf("%d",&TC);
	while(TC--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&vetor[i]);
			pos[vetor[i]] = i;
		}
		trocas = 0;
		for(int i=1;i<=n;i++){
			if(vetor[i] == i) continue;
			trocas++;
			int queremos = pos[i];
			int old = vetor[i];
			vetor[queremos] = old;
			vetor[i] = i;
			pos[old] = queremos;
			pos[i] = i;
		}
		printf("%d\n",trocas);
	}
	return 0;
}
