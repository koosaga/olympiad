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
typedef pair<lint, int> pi;

vector<int> gph[30005];
int dep[30005], par[15][30005];
int n;

void dfs(int x, int p){
	for(auto &i : gph[x]){
		if(i == p) continue;
		dep[i] = dep[x] + 1;
		par[0][i] = x;
		dfs(i, x);
	}
}

int lca(int s, int e){
	if(dep[s] < dep[e]) swap(s, e);
	int dx = dep[s] - dep[e];
	for(int i=0; i<15; i++){
		if((dx >> i) & 1) s = par[i][s];
	}
	for(int i=14; i>=0; i--){
		if(par[i][s] != par[i][e]){
			s = par[i][s];
			e = par[i][e];
		}
	}
	if(s == e) return s;
	return par[0][s];
}

int main(){
	cin >> n;
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, 0);
	for(int i=1; i<15; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	int q, c;
	cin >> q >> c;
	int ret = 0;
	for(int i=1; i<q; i++){
		int x;
		scanf("%d",&x);
		ret += dep[x] + dep[c] - 2 * dep[lca(x, c)];
		c = x;
	}
	cout << ret;
}
