// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1316
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXN 2001
int M,L,N;
int vetor[MAXN],knapsack[MAXN];
int main(){
	while(scanf("%d %d",&M,&L) && (L||M)){
		scanf("%d",&N);
		memset(knapsack,0,sizeof(knapsack));
		knapsack[0] = -1;
		int total = 0;
		for(int i=1;i<=N;i++){
			scanf("%d",&vetor[i]);
			total += vetor[i];
			for(int j = M;j >= vetor[i];j--){
				if(knapsack[j - vetor[i]] != 0 && knapsack[j] == 0){
					knapsack[j] = i;
				}
			}
		}
		int minhasoma = -1;
		int possivel = 0;
		for(int somaescolhida = M;somaescolhida >= 0;somaescolhida--){
			if(knapsack[somaescolhida] != 0 && total - somaescolhida <= L){
				possivel = 1;
				minhasoma = somaescolhida;
				break;
			}
		}
		if(!possivel){
			printf("Impossible to distribute\n");
			continue;
		}
		vector<int> pilha;
		while(true){
			if(knapsack[minhasoma] == 0 || knapsack[minhasoma] == -1) break;
			//printf("%d\n",knapsack[minhasoma]);
			pilha.push_back(knapsack[minhasoma]);
			minhasoma -= vetor[pilha.back()];
		}
		sort(pilha.begin(),pilha.end());
		printf("%d",(int)pilha.size());
		for(int i=0;i<pilha.size();i++){
			printf(" %d",pilha[i]);
		}
		printf("\n");
	}
	return 0;
}
