// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c1p6
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
const ll MAXN = 5*1e5 + 10;
vector<ii> grafo[MAXN];
ll n,k,especiais[MAXN],marcado[MAXN],raiz,aux,processado[MAXN];
ll best,pesototal,resposta[MAXN],maioral[MAXN];
ll dfs_marca(ll v,ll p){
	for(ii davez : grafo[v]){
		ll u = davez.first;
		ll peso = davez.second;
		if(u == p) continue;
		marcado[v] |= dfs_marca(u,v);
		if(marcado[u]) pesototal += peso;
	}
	return marcado[v]; 
}
void dfs_maior(ll v,ll p,ll depth){
	if(depth > best){
		best = depth;
		aux = v;
	}
	maioral[v] = max(maioral[v],depth);
	for(ii davez : grafo[v]){
		ll u = davez.first;
		ll peso = davez.second;
		if(u == p || !marcado[u]) continue;
		dfs_maior(u,v,depth + peso);
	}
}
int main(){
	scanf("%lld %lld",&n,&k);
	for(ll i = 1;i<n;i++){
		ll u,v;
		ll peso;
		scanf("%lld %lld %lld",&u,&v,&peso);
		grafo[u].push_back(ii(v,peso));
		grafo[v].push_back(ii(u,peso));
	}
	for(ll i = 1;i<=k;i++){
		scanf("%lld",&especiais[i]);
		marcado[especiais[i]] = 1;
	}
	raiz = especiais[1];
	dfs_marca(raiz,-1);
	dfs_maior(raiz,-1,0LL);
	best = 0;
	dfs_maior(aux,-1,0LL);
	best = 0;
	dfs_maior(aux,-1,0LL);
	priority_queue<ii, vector<ii>, greater<ii> > guloso;
	for(ll i = 1;i<=k;i++){
		guloso.push(ii(2LL*pesototal - maioral[especiais[i]],especiais[i]));
	}
	while(!guloso.empty()){
		ii davez = guloso.top();
		guloso.pop();
		ll peso = davez.first, v = davez.second;
		if(processado[v]) continue;
		processado[v] = 1;
		resposta[v] = peso;
		for(ii novo : grafo[v]){
			ll u = novo.first;
			ll adiciona = novo.second;
			if(!processado[u]) guloso.push(ii(peso + adiciona,u));
		}
	}
	for(ll i = 1;i<=n;i++) printf("%lld\n",resposta[i]);
	return 0;
}
}