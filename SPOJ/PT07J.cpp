// Ivan Carvalho
// Solution to https://www.spoj.com/problems/PT07J/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 1e5 + 10;
int inicio[MAXN],fim[MAXN],dfsNum,vetor[MAXN],numero[MAXN],segIt,raiz[MAXN],n;
vector<int> val,esq,dir,grafo[MAXN],corresponde;
vector<ii> compressao;
void dfs(int v,int p){
	inicio[v] = ++dfsNum;
	vetor[inicio[v]] = numero[v];
	for(int u : grafo[v]){
		if(u == p) continue;
		dfs(u,v);
	}
	fim[v] = dfsNum;
}
void update(int velho,int novo,int l,int r,int x,int delta){
	if(l == r){
		val[novo] = val[velho] + delta;
		return;
	}
	int m = (l+r)/2;
	val[novo] = val[velho] + delta;
	if(x <= m){
		val.push_back(0);
		esq.push_back(0);
		dir.push_back(0);
		dir[novo] = dir[velho];
		esq[novo] = ++segIt;
		update(esq[velho],esq[novo],l,m,x,delta);
	}
	else{
		val.push_back(0);
		esq.push_back(0);
		dir.push_back(0);
		dir[novo] = ++segIt;
		esq[novo] = esq[velho];
		update(dir[velho],dir[novo],m+1,r,x,delta);
	}
}
int kth(int p1,int p2,int l,int r,int count){
	if(l == r){
		return l;
	}
	int m = (l+r)/2;
	int davez = val[esq[p2]] - val[esq[p1]];
	if(count <= davez){
		return kth(esq[p1],esq[p2],l,m,count);
	}
	return kth(dir[p1],dir[p2],m+1,r,count - davez);
}
int main(){
	val.push_back(0);
	esq.push_back(0);
	dir.push_back(0);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&numero[i]);
		compressao.push_back(ii(numero[i],i));
	}
	sort(compressao.begin(),compressao.end());
	corresponde.push_back(0);
	for(int i=0;i<compressao.size();i++){
		corresponde.push_back(compressao[i].second);
	}
	for(int i=1;i<=n;i++){
		numero[i] = lower_bound(compressao.begin(),compressao.end(),ii(numero[i],i)) - compressao.begin() + 1;
	}
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}
	dfs(1,-1);
	for(int i=1;i<=n;i++){
		raiz[i] = ++segIt;
		val.push_back(0);
		esq.push_back(0);
		dir.push_back(0);
		update(raiz[i-1],raiz[i],1,n,vetor[i],1);
	}
	int q;
	scanf("%d",&q);
	while(q--){
		int v,k;
		scanf("%d %d",&v,&k);
		printf("%d\n",corresponde[kth(raiz[inicio[v]-1],raiz[fim[v]],1,n,k)]);
	}
	return 0;
}