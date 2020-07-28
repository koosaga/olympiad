// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADAINDEX/
#include <cstdio>
#include <cstring>
const int MAXN = 1e6 + 1;
const int ALPHABET_SIZE = 26;
int trie[MAXN][ALPHABET_SIZE];
int it;
int n,q;
int qtd[MAXN];
char entrada[MAXN];
int main(){
	scanf("%d %d",&n,&q);
	while(n--){
		scanf("%s",entrada);
		int tam = strlen(entrada);
		int atual = 0;
		for(int i=0;i < tam;i++){
			int c = entrada[i] - 'a';
			if(trie[atual][c] == 0){
				trie[atual][c] = ++it;
				atual = it;
			}
			else{
				atual = trie[atual][c];
			}
			qtd[atual]++;
		}
	}
	while(q--){
		scanf("%s",entrada);
		int tam = strlen(entrada);
		int atual = 0;
		int flag = 0;
		for(int i=0;i<tam;i++){
			int c = entrada[i] - 'a';
			if(trie[atual][c] == 0){
				flag = 1;
				break;
			}
			else{
				atual = trie[atual][c];
			}
		}
		if(flag) printf("0\n");
		else printf("%d\n",qtd[atual]);
	}
	return 0;
}