// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci15c1p3
#include <cstdio>
int vetor[1000010],marcado[1000010];
int main(){
	int resp = 0,n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&vetor[i]);
	for(int i=1;i<=n;i++){
		if(marcado[vetor[i]] == 0){
			resp++;
			marcado[vetor[i]-1]++;
		}
		else{
			marcado[vetor[i]]--;
			marcado[vetor[i]-1]++;
		}
	}
	printf("%d\n",resp);
	return 0;
}