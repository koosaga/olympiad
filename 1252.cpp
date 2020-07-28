// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1252
#include <cstdio>
#include <algorithm>
using namespace std;
int modulo,n;
int vetor[10010];
bool comp(int a,int b){
	if(a % modulo == b % modulo){
		int restoa = ((a % 2) + 2) % 2;
		int restob = ((b % 2) + 2) % 2;
		if(restoa > restob) return 1;
		if(restoa < restob) return 0;
		if(restoa == 1){
			return a > b;
		}
		return a < b;
	}
	return a % modulo < b % modulo;
}
int main(){
	while(scanf("%d %d",&n,&modulo)){
		printf("%d %d\n",n,modulo);
		if(n == 0 && modulo == 0) break;
		for(int i=0;i<n;i++){
			scanf("%d",&vetor[i]);
		}
		sort(vetor,vetor+n,comp);
		for(int i=0;i<n;i++){
			printf("%d\n",vetor[i]);
		}
	}
	return 0;
}
