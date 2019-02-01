#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

vector<int> gph[200005];
vector<int> dfn;

bool vis[200005];
int n, m, sz[200005], msz[200005];

void dfs1(int x, int p){
	vis[x] = 1;
	dfn.push_back(x);
	sz[x] = 1;
	msz[x] = 0;
	for(auto &i : gph[x]){
		if(i == p) continue;
		dfs1(i, x);
		sz[x] += sz[i];
		msz[x] = max(msz[x], sz[i]);
	}
}

lint dfs2(int x, int p){
	sz[x] = 1;
	lint ret = 0;
	for(auto &i : gph[x]){
		if(i == p) continue;
		ret += dfs2(i, x);
		ret += 1ll * (n - sz[i]) * sz[i];
		sz[x] += sz[i];
	}
	return ret;
}

pi solve(int r){
	dfn.clear();
	dfs1(r, -1);
	int ret = 1e9, pos = -1;
	for(auto &i : dfn){
		msz[i] = max(msz[i], (int)dfn.size() - sz[i]);
		if(ret > msz[i]){
			ret = msz[i];
			pos = i;
		}
	}
	return pi((int)dfn.size(), pos);
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	vector<pi> v;
	for(int i=1; i<=n; i++){
		if(!vis[i]){
			v.push_back(solve(i)); // size, cen
		}
	}
	sort(v.begin(), v.end());
	for(int i=0; i+1<v.size(); i++){
		gph[v[i].second].push_back(v.back().second);
		gph[v.back().second].push_back(v[i].second);
	}
	cout << dfs2(1, -1);
}

