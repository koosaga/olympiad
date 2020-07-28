// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmpg18g3
#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))
using namespace std;
typedef tuple<int,int,int> tupla;
const int MAXN = 2*1e5 + 10;
int BUCKET;
long long respostas[MAXN],frequencias[MAXN],quadrados[MAXN],total[MAXN];
int sz[MAXN],nivel[MAXN],N,Q,ini[MAXN],fim[MAXN],vetor[MAXN],dfsPtr,pai[MAXN],pesado[MAXN],range_update[MAXN];
int bit[MAXN],MAXIMO;
vector<int> grafo[MAXN];
vector<tupla> perguntas[MAXN];

void dfs_precalculo(int v,int p){
	pai[v] = p;
	ini[v] = ++dfsPtr;
	vetor[dfsPtr] = v;
	sz[v] = 1;
	for(int u : grafo[v]){
		if(u == p) continue;
		nivel[u] = nivel[v] + 1;
		dfs_precalculo(u,v);
		sz[v] += sz[u];
	}
	fim[v] = dfsPtr;
}

void processa_pesado(int v){
	for(int i = 0;i<=MAXIMO;i++){
		range_update[i] = quadrados[i] = total[i] = 0;
	}
	for(int u : grafo[v]){
		if(u == pai[v]) continue;
		int min_h = nivel[v] + 1, max_h = nivel[v] + 1;
		for(int i = ini[u];i<=fim[u];i++){
			int w = vetor[i];
			max_h = max(max_h,nivel[w]);
			frequencias[nivel[w]]++;
			total[nivel[w]]++;
		}
		for(int i = min_h;i<=max_h;i++){
			frequencias[i] += frequencias[i-1];
			quadrados[i] += frequencias[i]*frequencias[i];
		}
		range_update[max_h + 1] += frequencias[max_h]*frequencias[max_h];
		for(int i = min_h;i<=max_h;i++){
			frequencias[i] = 0;
		}
	}
	total[nivel[v]]++;
	for(int i = 1;i<=MAXIMO;i++) total[i] += total[i-1];
	for(int i = 1;i<=MAXIMO;i++){
		range_update[i] += range_update[i-1];
		quadrados[i] += range_update[i];
	}
	for(tupla davez : perguntas[v]){
		int id = get<0>(davez),hi = get<1>(davez);
		respostas[id] = (total[hi])*(total[hi]) - (quadrados[hi]);
		respostas[id]++;
		respostas[id] /= 2;
	}
}

void update(int idx,int val){
	while(idx <= MAXIMO){
		bit[idx] += val;
		idx += LSOne(idx);
	}
}

int read(int idx){
	int ans = 0;
	while(idx > 0){
		ans += bit[idx];
		idx -= LSOne(idx);
	}
	return ans;
}

void dfs_sack(int v,int p,int keep){
	int mx = -1,big = -1;
	for(int u : grafo[v]){
		if(u == p) continue;
		if(sz[u] > mx){
			mx = sz[u];
			big = u;
		}
	}
	for(int u : grafo[v]){
		if(u == p || u == big) continue;
		dfs_sack(u,v,0);
	}
	if(big != -1) dfs_sack(big,v,1);
	update(nivel[v],1);
	if(pesado[v]){
		for(int u : grafo[v]){
			if(u == p || u == big) continue;
			for(int i = ini[u];i<=fim[u];i++){
				int w = vetor[i];
				update(nivel[w],1);
			}
		}
	}
	else{
		for(int i = 0;i<perguntas[v].size();i++){
			int id = get<0>(perguntas[v][i]), h = get<1>(perguntas[v][i]), tot = 0;
			tot = read(h);
			respostas[id] += tot;
			get<2>(perguntas[v][i]) = tot;
		}
		for(int u : grafo[v]){
			if(u == p || u == big) continue;
			for(int i = ini[u];i<=fim[u];i++){
				int w = vetor[i];
				update(nivel[w],1);
				for(int j = 0;j<perguntas[v].size();j++){
					int id = get<0>(perguntas[v][j]), h = get<1>(perguntas[v][j]), tot = get<2>(perguntas[v][j]);
					if(nivel[w] <= h) respostas[id] += tot;
				}
			} 
			for(int i = ini[u];i<=fim[u];i++){
				int w = vetor[i];
				for(int j = 0;j<perguntas[v].size();j++){
					int id = get<0>(perguntas[v][j]), h = get<1>(perguntas[v][j]);
					if(nivel[w] <= h) get<2>(perguntas[v][j])++;
				}
			} 
		}
	}
	if(keep) return;
	for(int i = ini[v];i<=fim[v];i++){
		int u = vetor[i];
		update(nivel[u],-1);
	}
}

int main(){
	scanf("%d",&N);
	for(int i = 1;i<N;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}
	nivel[1] = 1;
	dfs_precalculo(1,-1);
	for(int i = 1;i<=N;i++){
		MAXIMO = max(MAXIMO,nivel[i]);
	}
	scanf("%d",&Q);
	for(int i = 1;i<=Q;i++){
		int v,d;
		scanf("%d %d",&v,&d);
		perguntas[v].push_back(make_tuple(i,min(nivel[v]+d,MAXIMO),0));
	}
	BUCKET = int(sqrt(Q)/(log(MAXIMO)/log(2)));
	for(int i = 1;i<=N;i++) pesado[i] = (perguntas[i].size() >= BUCKET);
	dfs_sack(1,-1,1);
	for(int i = 1;i<=N;i++) if(pesado[i]) processa_pesado(i); 
	for(int i = 1;i<=Q;i++) printf("%lld\n",respostas[i]);
	return 0;
}
