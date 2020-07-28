// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1980
#include <cstdio>
#include <cstring>
typedef unsigned long long int llu;
int main(){
	char davez[20];
	while(scanf("%s",davez)){
		if(davez[0]=='0') break;
		llu resposta = 1;
		llu tamanho = llu(strlen(davez));
		while(tamanho){
			resposta *= tamanho--;
		}
		printf("%llu\n",resposta);
	}
	return 0;
}
