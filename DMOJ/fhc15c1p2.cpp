// Ivan Carvalho
// Solution to https://dmoj.ca/problem/fhc15c1p2
#include <cstdio>
#include <cstring>
const int MAXN = 1e6 + 10;
const int ALPHABET_SIZE = 26;
char entrada[MAXN];
int Trie[MAXN][ALPHABET_SIZE];
int ptr;
int main(){
	int TC;
	scanf("%d",&TC);
	for(int tc=1;tc<=TC;tc++){
		for(int i=0;i<=ptr;i++) memset(Trie[i],0,sizeof(Trie[i]));
		ptr = 0;
		int n,resp = 0;
		scanf("%d",&n);
		while(n--){
			scanf("%s",entrada);
			int tam = strlen(entrada);
			int atual = 0;
			int delta = 1;
			for(int i=0;i<tam;i++){
				int c = entrada[i] - 'a';
				resp += delta;
				if(Trie[atual][c]){
					atual = Trie[atual][c];
				}
				else{
					Trie[atual][c] = ++ptr;
					atual = ptr;
					delta = 0;
				}
			}
		}
		printf("Case #%d: %d\n",tc,resp);
	}
	return 0;
}