#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

vector<int> graph[50005];
int n, k;

int dep[50005], par[50005][16];

void dfs(int x, int p){
	for(int i=1; i<=15; i++){
		par[x][i] = par[par[x][i-1]][i-1];
	}
	for(auto &i : graph[x]){
		if(i != p){
			par[i][0] = x;
			dep[i] = dep[x] + 1;
			dfs(i, x);
		}
	}
}

int dx[50005];

int lca(int s, int e){
	if(dep[s] < dep[e]) swap(s, e);
	int dx = dep[s] - dep[e];
	for(int i=0; i<=15; i++){
		if((dx >> i) & 1) s = par[s][i];
	}
	for(int i=15; i>=0; i--){
		if(par[s][i] != par[e][i]){
			s = par[s][i];
			e = par[e][i];
		}
	}
	if(s != e) return par[s][0];
	return s;
}

void dfs2(int x, int p){
	for(auto &i : graph[x]){
		if(i != p) dfs2(i, x), dx[x] += dx[i];
	}
}

int main(){
	freopen("maxflow.in","r",stdin);
	freopen("maxflow.out","w",stdout);
	scanf("%d %d",&n,&k);
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		graph[s].push_back(e);
		graph[e].push_back(s);
	}
	dfs(1, 0);
	while(k--){
		int s, e;
		scanf("%d %d",&s,&e);
		int l = lca(s, e);
		dx[s]++;
		dx[e]++;
		dx[l]--;
		dx[par[l][0]]--;
	}
	dfs2(1, 0);
	cout << *max_element(dx + 1, dx + n + 1);
}