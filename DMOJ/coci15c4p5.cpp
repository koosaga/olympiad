// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci15c4p5
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 10;

vector<int> grafo[MAXN];
map<int,ll> freq[MAXN];
int xorsum[MAXN],pai[MAXN],e1[MAXN],e2[MAXN],e3[MAXN],tamanho[MAXN],tira[MAXN],N,K;
ll total,exibe[MAXN];

int find(int x){
	if(x == pai[x]) return x;
	return pai[x] = find(pai[x]);
}

void join(int x,int y){
	x = find(x);
	y = find(y);
	if(x == y) return;
	if(tamanho[x] < tamanho[y]) swap(x,y);
	tamanho[x] += tamanho[y];
	pai[y] = x;
	for(map<int,ll>::iterator it = freq[y].begin();it != freq[y].end();it++){
		ll v1 = (*it).first, v2 = (*it).second;
		if(freq[x].count(v1)) total += freq[x][v1]*v2;
	}
	for(map<int,ll>::iterator it = freq[y].begin();it != freq[y].end();it++){
		ll v1 = (*it).first, v2 = (*it).second;
		freq[x][v1] += v2;
	}
}

void dfs(int v,int p){
	for(int idx : grafo[v]){
		int u = (e1[idx] != v) ? (e1[idx]) : (e2[idx]),w = e3[idx];
		if(u == p) continue;
		xorsum[u] = xorsum[v] ^ w;
		dfs(u,v);
	}
	tamanho[v] = 1;
	pai[v] = v;
	freq[v][xorsum[v]]++;
}

int main(){
	scanf("%d",&N);
	for(int i = 1;i<N;i++){
		scanf("%d %d %d",&e1[i],&e2[i],&e3[i]);
		grafo[e1[i]].push_back(i);
		grafo[e2[i]].push_back(i);
	}
	for(int i = 1;i<N;i++) scanf("%d",&tira[i]);
	dfs(1,-1);
	exibe[N] = 0;
	for(int i = N-1;i>=1;i--){
		int j = tira[i];
		join(e1[j],e2[j]);
		exibe[i] = total;
	}
	for(int i = 1;i<=N;i++) printf("%lld\n",exibe[i]);
	return 0;
}