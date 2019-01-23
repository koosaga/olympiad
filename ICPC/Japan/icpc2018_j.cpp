#include <bits/stdc++.h>
using namespace std;
using lint = long long;
const int MAXN = 100005;

vector<int> gph[MAXN];
set<int> s[MAXN];

int n, c[MAXN];
int dfn[MAXN], rev[MAXN], piv;
int par[17][MAXN], dep[MAXN];
int ans[MAXN];

int dist(int x, int y){
	int ret = dep[x] + dep[y];
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
	if(x != y) x = par[0][x];
	ret -= 2 * dep[x];
	return ret;
}

void upload(int x, int v){
	s[x].insert(dfn[v]);
	if(s[x].size() > 1){
		auto l = s[x].upper_bound(dfn[v]);
		auto r = s[x].lower_bound(dfn[v]);
		if(l == s[x].end()) l = s[x].begin();
		if(r == s[x].begin()) r = --s[x].end();
		else r = prev(r);
		ans[x] -= dist(rev[*l], rev[*r]);
		ans[x] += dist(rev[*l], v);
		ans[x] += dist(v, rev[*r]);
	}
}

void download(int x, int v){
	if(s[x].size() > 1){
		auto l = s[x].upper_bound(dfn[v]);
		auto r = s[x].lower_bound(dfn[v]);
		if(l == s[x].end()) l = s[x].begin();
		if(r == s[x].begin()) r = --s[x].end();
		else r = prev(r);
		ans[x] += dist(rev[*l], rev[*r]);
		ans[x] -= dist(rev[*l], v);
		ans[x] -= dist(v, rev[*r]);
	}
	s[x].erase(dfn[v]);
}

void dfs(int x, int p){
	dfn[x] = ++piv;
	rev[dfn[x]] = x;
	for(auto &i : gph[x]){
		if(i != p){
			par[0][i] = x;
			dep[i] = dep[x] + 1;
			dfs(i, x);
		}
	}
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n-1; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, 0);
	for(int i=1; i<17; i++){
		for(int j=1; j<=n; j++) par[i][j] = par[i-1][par[i-1][j]];
	}
	for(int i=1; i<=n; i++){
		scanf("%d",&c[i]);
		upload(c[i], i);
	}
	int q; scanf("%d",&q);
	char ss[5];
	while(q--){
		scanf("%s", ss);
		if(*ss == 'Q'){
			int p; scanf("%d",&p);
			if(s[p].empty()){
				puts("-1");
			}
			else printf("%d\n", ans[p] / 2);
		}
		else{
			int x, y; scanf("%d %d",&x,&y);
			download(c[x], x);
			c[x] = y;
			upload(c[x], x);
		}
	}
}

