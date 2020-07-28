// Ivan Carvalho
// Solution to https://www.spoj.com/problems/PHONELST/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 1;
const int ALPHABET_SIZE = 10;
int Trie[MAXN][ALPHABET_SIZE];
int fim[MAXN];
char entrada[ALPHABET_SIZE*2];
int ptr,T,N;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		int flag = 0;
		for(int i = 0;i<=ptr;i++){
			fim[i] = 0;
			memset(Trie[i],0,sizeof(Trie[i]));
		}
		ptr = 0;
		while(N--){
			scanf("%s",entrada);
			int tam = 0,atual = 0;
			tam = strlen(entrada);
			for(int i = 0;i<tam;i++){
				int c = entrada[i] - '0';
				if(Trie[atual][c]){
					atual = Trie[atual][c];
				}
				else{
					Trie[atual][c] = ++ptr;
					atual = ptr;
				}
				if(fim[atual]){
					flag = 1;
				}
			}
			fim[atual] = 1;
			if(atual != ptr) flag = 1;
		}
		if(flag) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}