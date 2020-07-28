// Ivan Carvalho
// Solution to https://dmoj.ca/problem/thicc17p6
#include <bits/stdc++.h>
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 2*1e5 + 10;
vector<ii> grafo[MAXN];
int n,t,aux,dist,maior[MAXN],tot;
void dfs(int v,int p,int depth){
	if(depth > dist){
		dist = depth;
		aux = v;
	}
	maior[v] = max(maior[v],depth);
	for(int i = 0;i<grafo[v].size();i++){
		int u = grafo[v][i].first;
		int peso = grafo[v][i].second;
		if(u == p) continue;
		dfs(u,v,depth + peso);
	}
}
int main(){
	getint(n);getint(t);
	for(int i = 1;i<n;i++){
		int u,v,peso;
		getint(u);getint(v);getint(peso);
		grafo[u].push_back(ii(v,peso));
		grafo[v].push_back(ii(u,peso));
		tot += 2*peso;
	}
	dfs(1,-1,0);
	dist = 0;
	dfs(aux,-1,0);
	dist = 0;
	dfs(aux,-1,0);
	for(int i = 1;i<=n;i++){
		if(grafo[i].size() == t) printf("%d %d\n",i,tot - maior[i]);
	}
	return 0;
}