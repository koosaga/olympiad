// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c2p4
#include <bits/stdc++.h>
#define gc getchar_unlocked
void getint(int &x){
    int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
typedef long long ll;
const int MAXN = 1e3 + 10;
int matriz[MAXN][MAXN],vaiate[MAXN][MAXN],n,m;
ll resp;
int main(){
	getint(n);getint(m);
	for(int i = 1;i<=n;i++){
		for(int j = 1;j<=m;j++){
			getint(matriz[i][j]);
		}
	}
	for(int coluna = 1;coluna <= m;coluna++){
		vaiate[n][coluna] = 1;
		for(int linha = n - 1;linha >= 1;linha--){
			if(matriz[linha][coluna] == matriz[linha+1][coluna]) vaiate[linha][coluna] = 1 + vaiate[linha+1][coluna];
			else vaiate[linha][coluna] = 1;
		}
	}
	for(int i = 1;i<=n;i++){
		for(int j = 1;j <= m;j++){
			int minimo = vaiate[i][j];
			for(int k = j;k <= m;k++){
				if(matriz[i][k] != matriz[i][j]) break;
				minimo = min(minimo,vaiate[i][k]);
				resp += 1LL*minimo;
			}
		}
	}
	printf("%lld\n",resp);
	return 0;
}