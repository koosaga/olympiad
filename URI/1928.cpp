// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1928
#include <cstdio>
#include <vector>
#include <algorithm>
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
#define MAXL 20
#define MAXN 50500
#define PB push_back
typedef long long ll;
ll resposta;
int n,c[MAXN],par[MAXN],pai[MAXN],nivel[MAXN],ancestral[MAXN][MAXL],visitado[MAXN];
vector<int> lista[MAXN];
void dfs(int x){
	for(int i=0;i<lista[x].size();i++){
		int y = lista[x][i];
		if (nivel[y]==-1){
			pai[y] = x;
			nivel[y] = nivel[x] + 1;
			dfs(y);
		}
	}
}
int LCA(int x, int y){
	if (nivel[x]<nivel[y]) swap(x,y);
	for(int i= MAXL-1;i>=0;i--) if (nivel[x] - (1<<i) >= nivel[y]) x = ancestral[x][i];
	if (x==y) return x;
	for(int i=MAXL-1;i>=0;i--){
		if (ancestral[x][i]!=-1 && ancestral[x][i]!=ancestral[y][i]) {
			x = ancestral[x][i];
			y = ancestral[y][i];
		}
	}
	return pai[x];
}
int main(){
	getint(n);
	for(int i=1;i<=n;i++){
		int davez;
		scanf("%d",&davez);
		if (c[davez]){
			par[i] = c[davez];
			par[c[davez]] = i;
		}
		c[davez] = i;
	}
	for(int i=1;i<n;i++){
		int a,b;
		getint(a);
		getint(b);
		lista[a].PB(b);
		lista[b].PB(a);
	}
	for(int i=0;i<n+10;i++) pai[i] = nivel[i] = -1;
	for(int i=0;i<=n+10;i++) for(int j=0;j<MAXL;j++) ancestral[i][j] = -1;
	nivel[1] = 0;
	dfs(1);
	for(int i=1;i<=n;i++) ancestral[i][0] = pai[i];
	for(int j=1;j<MAXL;j++) for(int i=1;i<=n;i++) ancestral[i][j] = ancestral[ancestral[i][j-1]][j-1];
	for(int i=1;i<=n;i++){
		if (visitado[i]) continue;
		visitado[par[i]] = 1;
		resposta += ll(nivel[i]+nivel[par[i]]-2*nivel[LCA(i,par[i])]);
	}
	printf("%lld\n",resposta);
	return 0;
}
