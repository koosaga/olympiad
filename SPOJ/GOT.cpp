// Ivan Carvalho
// Solution to https://www.spoj.com/problems/GOT/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <unordered_set>
#define MAXN 100010
using namespace std;
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
vector<int> grafo[MAXN];
unordered_set<int> conjunto[MAXN];
int cor[MAXN],pai[MAXN],superpai[MAXN],nivel[MAXN],segmento,n,m,estrela[MAXN];
void dfs_pai(int x){
	for(int v : grafo[x]){
		if(pai[v] == -1){
			pai[v] = x;
			nivel[v] = nivel[x] + 1;
			dfs_pai(v);
		}
	}
}
void dfs_superpai(int x,int p){
	superpai[x] = p;
	if(nivel[x] % segmento == 0){
		p = x;
		estrela[x] = 1;
	}
	for(int v : grafo[x]){
		if(superpai[v] == -1){
			dfs_superpai(v,p);
		}
	}
}
int LCA(int u,int v,int c){
	if(!conjunto[0].count(c)) return 0;
	while(superpai[u] != superpai[v]){
		if(nivel[u] > nivel[v]){
			if(!estrela[u]){
				if(cor[u] == c) return 1;
				u = pai[u];
				continue;
			}
			if(conjunto[u].count(c)) return 1;
			u = superpai[u];
		}
		else{
			if(!estrela[v]){
				if(cor[v] == c) return 1;
				v = pai[v];
				continue;
			}
			if(conjunto[v].count(c)) return 1;
			v = superpai[v];
		}
	}
	while(u != v){
		if(nivel[u] > nivel[v]){
			if(cor[u] == c) return 1;
			u = pai[u];
		}
		else{
			if(cor[v] == c) return 1;
			v = pai[v];
		}
	}
	return cor[u] == c;
}
int main(){
	while(scanf("%d %d",&n,&m) != EOF){
		conjunto[0].clear();
		for(int i=1;i<=n;i++){
			estrela[i] = 0;
			pai[i] = -1;
			superpai[i] = -1;
			nivel[i] = -1;
			grafo[i].clear();
			conjunto[i].clear();
			getint(cor[i]);
			conjunto[0].insert(cor[i]);
		}
		for(int i=1;i<n;i++){
			int u,v;
			getint(u);
			getint(v);
			grafo[u].push_back(v);
			grafo[v].push_back(u);
		}
		nivel[1] = 0;
		pai[1] = 1;
		dfs_pai(1);
		segmento = 0;
		for(int i=1;i<=n;i++){
			segmento = max(segmento,nivel[i]);
		}
		segmento = sqrt(segmento);
		superpai[1] = 1;
		dfs_superpai(1,1);
		for(int i=1;i<=n;i++){
			if(!estrela[i]) continue;
			int alvo = superpai[i];
			int temp = i;
			while(temp != alvo){
				conjunto[i].insert(cor[temp]);
				temp = pai[temp];
			}
			conjunto[i].insert(cor[alvo]);
		}
		while(m--){
			int u,v,c;
			getint(u);
			getint(v);
			getint(c);
			printf("%s\n",LCA(u,v,c) ? "Find" : "NotFind");
		}
		printf("\n");
	}
	return 0;
}