// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci07c1p6
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2*1e4 + 10;

vector<int> grafo[MAXN],tree[MAXN];
deque<int> ciclo[MAXN];
int cicloId,N,M,path[MAXN],tour[MAXN],dfs1Parent[MAXN],num[MAXN],low[MAXN],dfsCount;

void dfs1(int v,int p){
	
	num[v] = ++dfsCount;
	low[v] = dfsCount;


	for(int u : grafo[v]){
		if(u == p) continue;
		if(num[u] == 0){
			dfs1Parent[u] = v;
			dfs1(u,v);
			if(num[v] < low[u]){
				tree[u].push_back(v);
				tree[v].push_back(u);
			}
			low[v] = min(low[v],low[u]);
		}
		else if(num[u] < num[v]){
			low[v] = min(low[v],num[u]);
			cicloId++;
			int k = v;
			while(k != u){
				ciclo[cicloId].push_back(k);
				k = dfs1Parent[k];
			}
			ciclo[cicloId].push_back(u);
			reverse(ciclo[cicloId].begin(),ciclo[cicloId].end());
			for(int k : ciclo[cicloId]){
				tree[k].push_back(cicloId);
				tree[cicloId].push_back(k);
			}
		}
	}

}

void dfs2(int v,int p){

	if(v <= N){

		tour[v] = 0;
		path[v] = 0;

		for(int u : tree[v]){
			if(u == p) continue;
			dfs2(u,v);
			if(u > N){
				tour[v] += (1 + tour[u]);
			}
		}

		for(int u : tree[v]){
			
			if(u == p) continue;

			if(u <= N){
				path[v] = max(path[v], tour[v] + path[u] + 1);
			}
			else{
				path[v] = max(path[v], tour[v] - (1 + tour[u]) + (1 + path[u]) );
			}

		}

		path[v] = max(path[v],tour[v]);

	}
	else{

		tour[v] = 0;
		path[v] = 0;

		while(ciclo[v].front() != p){
			ciclo[v].push_back(ciclo[v].front());
			ciclo[v].pop_front();
		}

		for(int u : ciclo[v]){
			if(u == p) continue;
			dfs2(u,v);
			tour[v] += (1 + tour[u]);
		}

		int pref = 0;
		for(int u : ciclo[v]){
			if(u == p) continue;
			path[v] = max(path[v], pref + path[u] );
			pref += (1 + tour[u]);
		}

		reverse(ciclo[v].begin(),ciclo[v].end());
		pref = 0;
		for(int u : ciclo[v]){
			if(u == p) continue;
			path[v] = max(path[v], pref + path[u] );
			pref += (1 + tour[u]);
		}

		path[v] = max(path[v],tour[v]);

	}

}

int main(){

	scanf("%d %d",&N,&M);
	cicloId = N;

	for(int i = 1;i<=M;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}

	dfs1(1,-1);
	dfs2(1,-1);

	//for(int i = 1;i<=cicloId;i++) printf("I %d P %d T %d\n",i,path[i],tour[i]); 

	printf("%d\n",path[1]);

	return 0;

}