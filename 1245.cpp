// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1245
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int direita[70],esquerda[70];
int main(){
	int n;
	while(scanf("%d",&n)!=EOF){
		memset(direita,0,sizeof(direita));
		memset(esquerda,0,sizeof(esquerda));
		while(n--){
			int tamanho;
			char par;
			scanf("%d %c",&tamanho,&par);
			if (par=='E') esquerda[tamanho]++;
			else direita[tamanho]++;
		}
		int resposta = 0;
		for(int i=30;i<=60;i++) resposta += min(esquerda[i],direita[i]);
		printf("%d\n",resposta);
	}
	return 0;
}
