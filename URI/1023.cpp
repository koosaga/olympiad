// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1023
#include <cstdio>
#include <cstring>
#include <algorithm>
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
int consumismo[201];
int main(){
	int cidade = 0,n;
	while(scanf("%d",&n) && n){
		memset(consumismo,0,sizeof(consumismo));
		if(cidade) printf("\n");
		printf("Cidade# %d:\n",++cidade);
		int total = 0,populacao = 0;
		for(int i=1;i<=n;i++){
			int pessoas,consumo;
			getint(pessoas);
			getint(consumo);
			total += consumo;
			populacao += pessoas;
			consumismo[consumo/pessoas] += pessoas;
		}
		int primeirao = 0;
		for(int i=0;i<=200;i++){
			if(consumismo[i] == 0) continue;
			if(primeirao) printf(" ");
			else primeirao = 1;
			printf("%d-%d",consumismo[i],i);
		}
		printf("\nConsumo medio: %.2lf m3.\n",double(total)/double(populacao) - 0.004999);
	}
	return 0;
}
