// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1284
#include <cstdio>
#include <cstring>
const int ALPHABET_SIZE = 26;
const int MAXN = 1e6 + 1;
int iterador,resp,n;
int trie[MAXN][ALPHABET_SIZE];
int contador[MAXN],filhos[MAXN],pai[MAXN],fim[MAXN];
char entrada[101];
void dfs_filhos(int x){
	for(int i=0;i<ALPHABET_SIZE;i++){
		if(trie[x][i] != 0){
			dfs_filhos(trie[x][i]);
			pai[trie[x][i]] = x;
			filhos[x]++;
		}
	}
}
void dfs_conta(int x,int depth){
	for(int i=0;i<ALPHABET_SIZE;i++){
		if(trie[x][i] != 0){
			dfs_conta(trie[x][i],depth+1);
			trie[x][i] = 0;
		}
	}
	if(depth > 2 && filhos[pai[x]] <= 1 && !fim[pai[x]]){
		//printf("%d nao conta\n",x);
		contador[x] = 0;
		filhos[x] = 0;
		pai[x] = 0;
		fim[x] = 0;
		return;
	}
	//printf("%d conta %d\n",x,contador[x]);
	resp += contador[x];
	contador[x] = 0;
	filhos[x] = 0;
	pai[x] = 0;
	fim[x] = 0;
}
int main(){
	while(scanf("%d",&n) != EOF){
		iterador = 0;
		resp = 0;
		for(int stringdavez=0;stringdavez<n;stringdavez++){
			scanf("%s",entrada);
			int atual = 0;
			int tamanhodastring = strlen(entrada);
			for(int i=0;i<tamanhodastring;i++){
				char c = entrada[i];
				if(!trie[atual][c - 'a']){
					trie[atual][c - 'a'] = ++iterador;
					atual = iterador;
					contador[iterador] = 1;
					//printf("%c de %s eh %d\n",c,entrada,iterador);
				}
				else{
					contador[trie[atual][c - 'a']]++;
					atual = trie[atual][c - 'a'];
					//printf("%c de %s eh %d\n",c,entrada,atual);
				}
				if(i == tamanhodastring - 1) fim[atual] = 1;
			}
		}
		dfs_filhos(0);
		dfs_conta(0,1);
		printf("%.2lf\n",double(resp)/double(n));
	}
	return 0;
}
