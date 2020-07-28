// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1487
#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 1000
int main(){
	int atracoes,tempo,instancia=1;
	while(scanf("%d %d",&atracoes,&tempo) && (atracoes || tempo)){
		int tabela[MAXN],duracao[MAXN],recompensa[MAXN];
		for(int i=0;i<atracoes;i++) scanf("%d %d",&duracao[i],&recompensa[i]);
		for(int i=0;i<=tempo+2;i++) tabela[i]=0;
		for(int i=0;i<atracoes;i++){
			for(int j=duracao[i];j<=tempo;j++){
				tabela[j] = max(tabela[j],tabela[j-duracao[i]]+recompensa[i]);
			}
		}
		printf("Instancia %d\n%d\n\n",instancia++,tabela[tempo]);
	}
	return 0;
}
