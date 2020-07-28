// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c6p3
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3010;

char entrada[MAXN][MAXN],resposta[MAXN][MAXN];
int ultimo[MAXN],primeiro[MAXN],R,C;

int main(){

	scanf("%d %d",&R,&C);
	for(int j = 0;j<C;j++){
		ultimo[j] = -1;
		primeiro[j] = R;
	}

	for(int i = 0;i<R;i++){
		scanf("%s",entrada[i]);
		for(int j = 0;j<C;j++){
			if(entrada[i][j] == '#'){
				resposta[i][j] = '#';
				primeiro[j] = min(primeiro[j],i);
			}
			else if(entrada[i][j] == 'X'){
				resposta[i][j] = '.';
				ultimo[j] = i;
			}
			else{
				resposta[i][j] = '.';
			}
		}
	}

	int diferenca = R-1;
	for(int j = 0;j<C;j++){
		if(ultimo[j] == -1) continue;
		diferenca = min(diferenca, primeiro[j] - ultimo[j] );
	}
	diferenca--;

	for(int i = 0;i<R;i++){
		for(int j = 0;j<C;j++){
			if(entrada[i][j] == 'X'){
				resposta[i+diferenca][j] = 'X';
			}
		}
	}

	for(int i = 0;i<R;i++){
		for(int j = 0;j<C;j++){
			printf("%c",resposta[i][j]);
		}
		printf("\n");
	}

	return 0;
}