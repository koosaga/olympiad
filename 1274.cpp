// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1274
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
int main(){
	int ordem,vetor[60];
	while(scanf("%d",&ordem) && ordem){
		set<int> contador;
		for(int i=1;i<=ordem;i++) {
			scanf("%d",&vetor[i]);
			contador.insert(vetor[i]);
		}
		if (contador.size()!=ordem) {
			printf("No solution\n");
			continue;
		}
		vector<int> trocas;
		for(int i=1;i<=ordem;i++){
			int indice;
			for(int j=i;j<=ordem;j++) if (vetor[j]==i) indice = j;
			for(int k=indice-1;k>=i;k--) {
				swap(vetor[k+1],vetor[k]);
				trocas.push_back(k);
			}
		}
		printf("%d",int(trocas.size()));
		for(int i=0;i<trocas.size();i++) printf(" %d",trocas[i]);
		printf("\n");
	}
	return 0;
}
