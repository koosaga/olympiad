#include "Joi.h"
#include <bits/stdc++.h>
using namespace std;

static struct disj{
	int pa[10005];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	int uni(int x, int y){
		x = find(x);
		y = find(y);
		if(x == y) return 0;
		pa[x] = y; return 1;
	}
}disj;

static vector<int> gph[10005];
static queue<int> que;
static int col[10005], par[10005];
static int piv, noson, chk[10005];
static int contain[10005][66];

static void dfs(int x, int p){
	if(piv >= 60){
		que.push(x);
		return;
	}
	col[x] = ++piv;
	for(auto &i : gph[x]){
		if(i != p){
			par[i] = x;
			dfs(i, x);
		}
	}
}

static void get_spanning(int x, int p){
	for(auto &i : gph[x]){
		if(i != p && chk[i]){
			noson = i;
			get_spanning(i, x);
		}
	}
}

void Joi(int N, int M, int A[], int B[], long long X, int T) {
	disj.init(N);
	for(int i=0; i<M; i++){
		if(disj.uni(A[i], B[i])){
			gph[A[i]].push_back(B[i]);
			gph[B[i]].push_back(A[i]);
		}
	}
	dfs(0, -1);
	vector<int> aux;
	for(int i=0; i<N; i++){
		if(col[i]) aux.push_back(i);
	}
	for(int i=0; i<60; i++){
		for(int j=0; j<60; j++){
			contain[aux[i]][j] = aux[j];
		}
	}
	while(!que.empty()){
		int i = que.front();
		que.pop();
		noson = -1;
		for(int j=0; j<60; j++){
			chk[contain[par[i]][j]] = 1;
		}
		get_spanning(par[i], -1);
		col[i] = col[noson];
		for(int j=0; j<60; j++){
			contain[i][j] = contain[par[i]][j];
			if(contain[i][j] == noson) contain[i][j] = i;
			chk[contain[par[i]][j]] = 0;
		}
		for(auto &j : gph[i]){
			if(j != par[i]){
				par[j] = i;
				que.push(j);
			}
		}
	}
	for(int i=0; i<N; i++) MessageBoard(i, (X >> (col[i] - 1)) & 1);
}
