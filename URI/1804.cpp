// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1804
#include <cstdio>
#define MAXN 1000001
#define LSOne(S) (S & (-S))
int tree[MAXN],vetor[MAXN],n;
void update(int idx, int val){
	while(idx <= n){
		tree[idx] += val;
		idx += LSOne(idx);
	}
}
int rsq(int x){
	int s = 0;
	while(x>0){
		s += tree[x];
		x -= LSOne(x);
	}
	return s;
}
int main(){
	int davez;
	char operacao;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&vetor[i]);
		update(i,vetor[i]);
	}
	getchar();
	while(scanf("%c %d",&operacao,&davez)!=EOF){
		if (operacao == 'a'){
			update(davez,-vetor[davez]);
		}
		else {
			printf("%d\n",rsq(davez-1));
		}
		getchar();
	}
	return 0;
}
