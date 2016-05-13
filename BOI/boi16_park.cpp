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

int n, m, w, h;
int x[2005], y[2005], r[2005];
int adj[2005][2005];
int dst[2005][2005], ret[4][4];

vector<int> gph[2005];

struct edg{int s, e, x;};
vector<edg> v;

void dfs(int x, int p, int s, int v){
	dst[s][x] = v;
	for(auto &i : gph[x]){
		if(i == p) continue;
		dfs(i, x, s, max(v, adj[x][i]));
	}
}

struct disj{
	int pa[2055];
	void init(int n){
		for(int i=0; i<=n; i++) pa[i] = i;
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p), q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int main(){
	cin >> n >> m >> w >> h;
	for(int i=0; i<n; i++){
		scanf("%d %d %d",&x[i],&y[i],&r[i]);
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			if(i == j) continue;
			double dist = hypot(x[j] - x[i], y[j] - y[i]) - r[i] - r[j];
			adj[i][j] = adj[j][i] = (int)floor(dist / 2 + 1e-10);
		}
	}
	for(int i=0; i<n; i++){
		adj[i][n] = adj[n][i] = (y[i] - r[i]) / 2;
		adj[i][n+1] = adj[n+1][i] = (x[i] - r[i]) / 2;
		adj[i][n+2] = adj[n+2][i] = (w - r[i] - x[i]) / 2;
		adj[i][n+3] = adj[n+3][i] = (h - r[i] - y[i]) / 2;
	}
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			if(i != j) adj[n+i][n+j] = 1e9;
		}
	}
	for(int i=0; i<n+4; i++){
		for(int j=0; j<i; j++){
			v.push_back({i, j, adj[i][j]});
		}
	}
	sort(v.begin(), v.end(), [&](const edg &a, const edg &b){
		return a.x < b.x;
	});
	disj.init(n+4);
	for(auto &i : v){
		if(disj.uni(i.s, i.e)){
			gph[i.s].push_back(i.e);
			gph[i.e].push_back(i.s);
		}
	}
	for(int i=n; i<n+4; i++){
		dfs(i, -1, i, 0);
	}
	ret[0][0] = ret[1][1] = ret[2][2] = ret[3][3] = 1e9;
	ret[0][1] = ret[1][0] = min(dst[n][n+1], min(dst[n][n+2], dst[n][n+3]));
	ret[0][2] = ret[2][0] = min(min(dst[n][n+1], dst[n][n+3]), min(dst[n+2][n+1], dst[n+2][n+3]));
	ret[0][3] = ret[3][0] = min(dst[n+1][n], min(dst[n+1][n+2], dst[n+1][n+3]));
	ret[1][2] = ret[2][1] = min(dst[n+2][n], min(dst[n+2][n+1], dst[n+2][n+3]));
	ret[1][3] = ret[3][1] = min(min(dst[n][n+2], dst[n][n+3]), min(dst[n+1][n+2], dst[n+1][n+3]));
	ret[2][3] = ret[3][2] = min(dst[n+3][n], min(dst[n+3][n+1], dst[n+3][n+2]));
	while(m--){
		int s, d;
		scanf("%d %d",&d, &s);
		for(int i=0; i<4; i++){
			if(ret[s-1][i] >= d){
				putchar(i + '1');
			}
		}
		puts("");
	}
}