// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADAORANG/
#include <cstdio>
#include <cstring>
#include <vector>
#include <bitset>
#include <algorithm>
#define gc getchar_unlocked
inline void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
inline void print(int n){
	char buf[11];
	buf[10] = '\n';
	int i = 9;
	while (n){
		buf[i--] = n % 10 + '0';
		n /= 10;
	}
	while (buf[i] != '\n') putchar_unlocked(buf[++i]);
}
using namespace std;
const int MAXS = 250;
const int MAXN = 450001;
const int MAXL = 19;
int N,Q,raiz;
int ancestral[MAXN][MAXL];
int nivel[MAXN];
int cor[MAXN];
int dp[MAXN];
bitset<MAXS> truque[MAXN];
vector<int> grafo[MAXN];
void dfs(int v,int p){
	truque[v].reset();
	truque[v].set(cor[v]);
	ancestral[v][0] = p;
	for(int u : grafo[v]){
		if(u == p) continue;
		nivel[u] = nivel[v] + 1;
		dfs(u,v);
		truque[v] |= truque[u];
	}
	dp[v] = truque[v].count();
}
inline int LCA(int u, int v){
	if(nivel[u] < nivel[v]) swap(u,v);
	for(int i  = MAXL - 1;i >= 0;i--){
		if(ancestral[u][i] != -1 && nivel[ancestral[u][i]] >= nivel[v]){
			u = ancestral[u][i];
		}
	}
	if(u == v) return u;
	for(int i = MAXL - 1;i >= 0;i--){
		if(ancestral[u][i] != ancestral[v][i] && ancestral[u][i] != -1){
			u = ancestral[u][i];
			v = ancestral[v][i];
		}
	}
	return ancestral[u][0];
}
int main(){
	int TC;
	getint(TC);
	while(TC--){
		getint(N);
		getint(Q);
		getint(raiz);
		raiz++;
		for(int i=1;i<=N;i++){
			getint(cor[i]);
			grafo[i].clear();
			cor[i]--;
			nivel[i] = 0;
		}
		for(int i = 1;i<N;i++){
			int u,v;
			getint(u);
			getint(v);
			u++;
			v++;
			grafo[u].push_back(v);
			grafo[v].push_back(u);
		}
		memset(ancestral,-1,sizeof(ancestral));
		dfs(raiz,-1);
		for(int j = 1;j<MAXL;j++){
			for(int i=1;i<=N;i++){
				if(ancestral[i][j-1] != -1) ancestral[i][j] = ancestral[ancestral[i][j-1]][j-1];
			}
		}
		while(Q--){
			int u,v;
			getint(u);
			getint(v);
			u++;
			v++;
			print(dp[LCA(u,v)]);
		}
	}
	return 0;
}