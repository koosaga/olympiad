// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADAGRAFT/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 4*1e5 + 10;
const ll MOD = 1e9 + 7;
bitset<MOD> cjt;
ll produto;
vector<int> grafo[MAXN];
int ini[MAXN],fim[MAXN],ptr,sz[MAXN],resp,cor[MAXN],raiz,N,vetor[MAXN];
void add(int val){
	if(!cjt.test(val)){
		resp++;
		cjt.flip(val);
	}
}
void remove(int val){
	if(cjt.test(val)){
		resp--;
		cjt.flip(val);
	}
}
void dfs_init(int v){
	sz[v] = 1;
	ini[v] = ++ptr;
	vetor[ptr] = v;
	for(int u : grafo[v]){
		dfs_init(u);
		sz[v] += sz[u];
	}
	fim[v] = ptr;
}
void dfs_sack(int v,int keep){
	int mx = -1,big = -1;
	for(int u : grafo[v]){
		if(sz[u] > mx){
			mx = sz[u];
			big = u;
		}
	}
	for(int u : grafo[v]){
		if(u == big) continue;
		dfs_sack(u,0);
	}
	if(big != -1){
		dfs_sack(big,1);
		for(int i = ini[v];i<ini[big];i++) add(cor[vetor[i]]);
		for(int i = fim[big] + 1;i<=fim[v];i++) add(cor[vetor[i]]);
	}
	else{
		add(cor[v]);
	}
	produto *= 1LL*resp;
	produto %= MOD;
	if(keep == 0){
		for(int i = ini[v];i<=fim[v];i++) remove(cor[vetor[i]]);
	}
}
int main(){
	produto = 1LL;
	scanf("%d",&N);
	for(int i = 1;i<N;i++){
		int p;
		scanf("%d",&p);
		grafo[p].push_back(i);
	}
	for(int i = 0;i<N;i++) scanf("%d",&cor[i]);
	dfs_init(0);
	dfs_sack(0,1);
	printf("%lld\n",produto);
	return 0;
}