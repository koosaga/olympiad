// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ORDERS/
#include <cstdio>
#define MAXN 200011
#define LSOne(S) (S & (-S))
int vetor[MAXN],resposta[MAXN],bit[MAXN],n;
void update(int idx, int val){
	while(idx <= n){
		bit[idx] += val;
		idx += LSOne(idx);
	}
}
int sum(int idx){
	int answer = 0;
	while(idx > 0){
		answer += bit[idx];
		idx -= LSOne(idx);
	}
	return answer;
}
int find(int idx){
	int ini = 1, fim = n, meio, resp;
	while(ini <= fim){
		int meio = (ini+fim)/2;
		int soma = sum(meio);
		if (soma >= idx){
			fim = meio - 1;
			resp = meio;
		}
		else ini = meio + 1;
	}
	return resp;
}
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		scanf("%d",&n);
		for(int i=0;i<=n;i++) bit[i] = 0;
		for(int i=1;i<=n;i++){
			update(i,1);
			scanf("%d",&vetor[i]);
		}
		for(int i = n; i > 0; i--){
			int kth = i - vetor[i];
			resposta[i] = find(kth);
			update(resposta[i],-1);
		}
		for(int i=1;i<=n;i++) printf("%d ",resposta[i]);
		printf("\n");
	}
	return 0;
}