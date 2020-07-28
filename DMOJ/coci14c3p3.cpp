// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c3p3
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;

char entrada[MAXN][MAXN];
int N,maior[MAXN],max_heigt,min_x,max_x,perimetro;

int main(){

	max_x = -1;min_x = MAXN;

	for(int i = 0;i<MAXN;i++){
		for(int j = 0;j<MAXN;j++){
			entrada[i][j] = '.';
		}
	}

	scanf("%d",&N);

	for(int i = 1;i<=N;i++){
		int l,r,h;
		scanf("%d %d %d",&l,&r,&h);
		max_heigt = max(max_heigt,h);
		min_x = min(min_x,l);
		max_x = max(max_x,r - 1);
		for(int j = l;j<r;j++) maior[j] = max(maior[j],h);
	}

	for(int i = min_x;i<=max_x+1;i++){
		if(maior[i] != 0) perimetro++;
		perimetro += abs(maior[i] - maior[i-1]);
		if(maior[i] == maior[i-1]){
			// Caso 1 : igualdade
			entrada[i][maior[i]] = '#';
		}
		else if(maior[i] > maior[i-1]){
			// Caso 2 : subiu
			for(int j = maior[i-1];j<=maior[i];j++) entrada[i][j] = '#';
		}
		else{
			// Caso 3 : desceu
			for(int j = maior[i-1];j>=maior[i];j--) entrada[i-1][j] = '#';
			entrada[i][maior[i]] = '#';
		}
	}

	for(int i = min_x;i<=max_x;i++){
		entrada[i][0] = '*';	
	}

	printf("%d\n",perimetro);
	for(int j = max_heigt;j>=0;j--){
		for(int i = min_x;i<=max_x;i++){
			printf("%c",entrada[i][j]);	
		}
		printf("\n");
	}

	return 0;

}