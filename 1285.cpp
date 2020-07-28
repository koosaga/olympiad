// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1285
#include <cstdio>
#include <cstring>
int soma[6000];
int checa(int x){
	int freq[11];
	memset(freq,0,sizeof(freq));
	while(x > 0){
		freq[x%10]++;
		x /= 10;
	}
	for(int i=0;i<=9;i++){
		if(freq[i] >= 2){
			return 0;
		}
	}
	return 1;
}
int main(){
	for(int i=1;i<=5000;i++){
		soma[i] = soma[i-1] + checa(i);
	}
	int n,m;
	while(scanf("%d %d",&n,&m) != EOF){
		printf("%d\n",soma[m] - soma[n-1]);
	}
	return 0;
}
