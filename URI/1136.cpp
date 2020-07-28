// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1136
#include <cstdio>
#define MAXN 1001
int abs(int x){
	if(x > 0) return x;
	return -x;
}
int possivel[MAXN],vetor[MAXN],n,b;
int main(){
	while(scanf("%d %d",&n,&b) && (n||b)){
		for(int i=0;i<=n;i++){
			possivel[i] = 0;
		}
		for(int i=0;i<b;i++){
			scanf("%d",&vetor[i]);
		}
		for(int i=0;i<b;i++){
			for(int j=0;j<b;j++){
				possivel[abs(vetor[i] - vetor[j])] = 1;
			}
		}
		int flag = 1;
		for(int i=0;i<=n;i++){
			flag &= possivel[i];
		}
		printf("%c\n",flag ? 'Y' : 'N');
	}
	return 0;
}
