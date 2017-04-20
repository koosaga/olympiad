#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n;
vector<int> gph[1000005];
int sz[1000005], par[1000005];

void dfs(int x, int p){
	par[x] = p;
	sz[x] = 1;
	for(auto &i : gph[x]){
		if(i == p) continue;
		dfs(i, x);
		sz[x] += sz[i];
	}
}

lint solve(int x, int p, int d){
	lint ret = 2 * d;
	for(auto &i : gph[x]){
		if(i == p) continue;
		ret += solve(i, x, d+1);
	}
	return ret;
}

int dfs2(int x, int p){
	int ret = 0;
	for(auto &i : gph[x]){
		if(i == p) continue;
		ret = max(ret, dfs2(i, x) + 1);
	}
	return ret;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, 0);
	for(int i=1; i<=n; i++){
		int szmx = 0, szmn = 1e9;
		for(auto &j : gph[i]){
			if(par[i] == j){
				szmx = max(szmx, n - sz[i]);
			}
			else{
				szmx = max(szmx, sz[j]);
			}
		}
		if(n - szmx < szmx) puts("-1");
		else{
			lint ret = solve(i, 0, 0);
			int dmax = 0;
			for(auto &j : gph[i]){
				if(par[i] == j){
					if(n - sz[i] == szmx) dmax = max(dmax, dfs2(j, i) + 1);
				}
				else{
					if(sz[j] == szmx) dmax = max(dmax, dfs2(j, i) + 1);
				}
			}
			if(szmx != n - szmx){
				for(auto &j : gph[i]){
					dmax = max(dmax, dfs2(j, i) + 1);
				}
			}
			printf("%lld\n", ret - dmax);
		}
	}
}