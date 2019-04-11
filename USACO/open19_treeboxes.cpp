#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100005;
#include "grader.h"

/*
int nnn;
int getN(){ return nnn; }
void setFarmLocation(int id, int x, int y){ printf("%d %d\n", x, y); }
void addBox(int x1, int y1, int x2, int y2){ printf("%d %d %d %d\n", x1, y1, x2, y2); }
*/

vector<int> gph[MAXN];
int n, dep[MAXN], sz[MAXN], par[17][MAXN];
pi a[MAXN];

int lca(int x, int y){
	if(dep[x] > dep[y]) swap(x, y);
	int dx = dep[y] - dep[x];
	for(int i=0; i<17; i++){
		if((dx >> i) & 1) y = par[i][y];
	}
	for(int i=16; i>=0; i--){
		if(par[i][x] != par[i][y]){
			x = par[i][x];
			y = par[i][y];
		}
	}
	if(x != y) return par[0][x];
	return x;
}

void addRoad(int a, int b){
	gph[a].push_back(b);
	gph[b].push_back(a);
}

void dfs(int x, int p){
	sz[x] = 1;
	for(auto &i : gph[x]){
		if(i!=p){
			dep[i] = dep[x] + 1;
			dfs(i, x);
			sz[x] += sz[i];
			par[0][i] = x;
		}
	}
}

void solve(int x, int p, int offset1, int offset2){
	a[x] = pi(offset1 + 1, offset2 + 1);
	int curSum = 0;
	for(auto &i : gph[x]){
		if(i == p) continue;
		solve(i, x, offset1 + 1 + curSum, offset2 + sz[x] - sz[i] - curSum);
		curSum += sz[i];
	}
}

void buildFarms(){
	n = getN();
	dfs(0, -1);
	for(int i=1; i<17; i++){
		for(int j=0; j<n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	solve(0, -1, 0, 0);
	for(int i=0; i<n; i++){
		setFarmLocation(i, a[i].first, a[i].second);
	}
}

void notifyFJ(int x, int y){
	int l = lca(x, y);
	if(l != x){
		addBox(a[l].first + 1, a[l].second + 1, a[x].first, a[x].second);
	}
	addBox(a[l].first, a[l].second, a[y].first, a[y].second);
}

/*
int main(){
	nnn = 3;
	addRoad(0, 1);
	addRoad(0, 2);
	buildFarms();
	notifyFJ(0, 0);
	notifyFJ(0, 2);
}
*/
