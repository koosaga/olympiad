// Ivan Carvalho
// Solution to https://dmoj.ca/problem/thicc17p4
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 110;
double resp;
char A[MAXN],B[MAXN];
int tab[MAXN][MAXN];
int n,t,tamanho;
int solve(int a,int b){
	for(int i = 0;i<=a;i++){
		tab[i][0] = i;
	}
	for(int i = 0;i<=b;i++){
		tab[0][i] = i;
	}
	for(int i = 1;i<=a;i++){
		for(int j = 1;j <= b;j++){
			tab[i][j] = tab[i-1][j-1] + (A[i-1] == B[j-1] ? 0 : 1);
			tab[i][j] = min(tab[i-1][j] + 1,tab[i][j]);
			tab[i][j] = min(tab[i][j-1] + 1,tab[i][j]);
		}
	}
	return tab[a][b];
}
int main(){
	resp = 1e9;
	scanf("%s",B);
	tamanho = strlen(B);
	scanf("%d",&n);
	for(int i = 1;i<=n;i++){
		int total;
		int somatorio = 0;
		scanf("%d",&total);
		for(int j = 1;j<=total;j++){
			scanf("%s",A);
			somatorio += solve(strlen(A),tamanho);
		}
		double cand = double(somatorio)/double(total);
		resp = min(resp,cand);
	}
	printf("%.6lf\n",resp);
	return 0;
}