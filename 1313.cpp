// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1313
#include <cstdio>
#include <cstring>
typedef long long ll;
const int MAXN = 1e5 + 1;
const int MAXL = 1e3 + 1;
const int ALPHABET_SIZE = 26;
int P,S;
int itPt,itEs;
int TriePt[MAXN][ALPHABET_SIZE];
int TrieEs[MAXN][ALPHABET_SIZE];
ll freq[ALPHABET_SIZE];
char entrada[MAXL];
ll dfs_Es(int x,int depth){
	ll retorna = 0;
	for(int i=0;i<ALPHABET_SIZE;i++){
		if(TrieEs[x][i] != 0){
			if(depth + 1 != 1) freq[i]++;
			else retorna++;
			retorna += dfs_Es(TrieEs[x][i],depth+1);
			TrieEs[x][i] = 0;
		}
	}
	return retorna;
}
ll dfs_Pt(int x,int depth){
	ll retorna = 0;
	for(int i=0;i<ALPHABET_SIZE;i++){
		if(TriePt[x][i] != 0){
			retorna += dfs_Pt(TriePt[x][i],depth+1);
			TriePt[x][i] = 0;
		}
		else{
			if(depth != 0) retorna += freq[i];
		}
	}
	return retorna;
}
int main(){
	while(scanf("%d %d",&P,&S) && (P||S)){
		for(int i=0;i<ALPHABET_SIZE;i++){
			freq[i] = 0;
		}
		itPt = 0;
		itEs = 0;
		for(int stringdavez = 0;stringdavez < P;stringdavez++){
			int atual = 0;
			scanf("%s",entrada);
			int tam = strlen(entrada);
			for(int i=0;i<tam;i++){
				int c = entrada[i] - 'a';
				if(TriePt[atual][c] != 0){
					atual = TriePt[atual][c];
				}
				else{
					TriePt[atual][c] = ++itPt;
					atual = itPt;
				}
			}
		}
		for(int stringdavez =0;stringdavez < S;stringdavez++){
			int atual = 0;
			scanf("%s",entrada);
			int tam = strlen(entrada);
			for(int i=tam-1;i>=0;i--){
				int c = entrada[i] - 'a';
				if(TrieEs[atual][c] != 0){
					atual = TrieEs[atual][c];
				}
				else{
					TrieEs[atual][c] = ++itEs;
					atual = itEs;
				}
			}
		}
		ll tamanhosufixo = dfs_Es(0,0);
		ll exibir = dfs_Pt(0,0) + itPt*tamanhosufixo;
		printf("%lld\n",exibir);
	}
	return 0;
}
