// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1437
#include <cstdio>
char entrada[1001];
int main(){
	int n;
	while(scanf("%d",&n) && n){
		scanf("%s",entrada);
		char direcao = 'N';
		for(int i=0;i<n;i++){
			if(direcao == 'N'){
				if(entrada[i] == 'D') direcao = 'L';
				if(entrada[i] == 'E') direcao = 'O';
			}
			else if(direcao == 'S'){
				if(entrada[i] == 'D') direcao = 'O';
				if(entrada[i] == 'E') direcao = 'L';
			}
			else if(direcao == 'L'){
				if(entrada[i] == 'D') direcao = 'S';
				if(entrada[i] == 'E') direcao = 'N';
			}
			else if(direcao == 'O'){
				if(entrada[i] == 'D') direcao = 'N';
				if(entrada[i] == 'E') direcao = 'S';
			}
		}
		printf("%c\n",direcao);
	}
	return 0;
}
