#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

vector<int> gph[250000];
int par[18][250000], dep[250000], dx[250000];
int n, q;

void dfs(int x, int p){
	for(auto &i : gph[x]){
		if(i != p){
			par[0][i] = x;
			dep[i] = dep[x] + 1;
			dfs(i, x);
		}
	}
}

void dfs2(int x, int p){
	for(auto &i : gph[x]){
		if(i != p){
			dfs2(i, x);
			dx[x] += dx[i];
		}
	}
}

int lca(int s, int e){
	if(dep[s] < dep[e]) swap(s, e);
	int dx = dep[s] - dep[e];
	for(int i=0; i<=17; i++){
		if((dx >> i) & 1) s = par[i][s];
	}
	for(int i=17; i>=0; i--){
		if(par[i][s] != par[i][e]){
			s = par[i][s];
			e = par[i][e];
		}
	}
	if(s != e) return par[0][s];
	return s;
}

int main(){
	scanf("%d %d",&n,&q);
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, 0);
	for(int i=1; i<=17; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	for(int i=0; i<q; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		int l = lca(s, e);
		dx[s]++;
		dx[e]++;
		dx[l]-=2;
	}
	dfs2(1, 0);
	int ret = -1;
	pi ret2(-1, -1);
	for(int i=2; i<=n; i++){
		int p = par[0][i];
		int q = i;
		if(p > q) swap(p, q);
		if(ret < dx[i]){
			ret = dx[i];
			ret2 = pi(p, q);
		}
		if(ret == dx[i]){
			ret2 = min(ret2, pi(p, q));
		}
	}
	printf("%d %d %d\n",ret2.first, ret2.second, ret);
}