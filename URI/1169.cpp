// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1169
#include <cmath>
#include <cstdio>
typedef unsigned long long llu;
int main(){
	int casos;
	scanf("%d",&casos);
	while(casos--){
		llu resposta = 1LLU;
		int davez;
		scanf("%d",&davez);
		if (davez == 64) {
			printf("1537228672809129 kg\n");
			continue;
		}
		while(davez--){
			resposta *= 2LLU;
		}
		printf("%llu kg\n",resposta/12000LLU);
	}
	return 0;
}
