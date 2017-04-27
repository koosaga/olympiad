#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

vector<int> gph[100005];
int n, m, k, s[100005], e[100005];
int dfn[100005], par[17][100005], dep[100005], piv;
int cnt[100005];

void dfs(int x, int p){
	dfn[x] = ++piv;
	for(auto &i : gph[x]){
		if(i != p){
			dep[i] = dep[x] + 1;
			par[0][i] = x;
			dfs(i, x);
		}
	}
}

int lca(int s, int e){
	if(dep[s] < dep[e]) swap(s, e);
	int dx = dep[s] - dep[e];
	for(int i=0; i<17; i++){
		if((dx >> i) & 1) s = par[i][s];
	}
	for(int i=16; i>=0; i--){
		if(par[i][s] != par[i][e]){
			s = par[i][s];
			e = par[i][e];
		}
	}
	if(s == e) return s;
	return par[0][s];
}

void upd(int s, int e){
	int l = lca(s, e);
	cnt[s]++;
	cnt[e]++;
	cnt[l]-=2;
}

void dfs2(int x, int p){
	for(auto &i : gph[x]){
		if(i != p){
			dfs2(i, x);
			cnt[x] += cnt[i];
		}
	}
}

int main(){
	scanf("%d %d %d",&n,&m,&k);
	for(int i=0; i<n-1; i++){
		scanf("%d %d",&s[i],&e[i]);
		gph[s[i]].push_back(e[i]);
		gph[e[i]].push_back(s[i]);
	}
	dfs(1, -1);
	for(int i=1; i<17; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	for(int i=0; i<m; i++){
		int t;
		scanf("%d",&t);
		vector<int> v(t);
		for(auto &j : v) scanf("%d",&j);
		sort(v.begin(), v.end(), [&](const int &a, const int &b){
			return dfn[a] < dfn[b];
		});
		for(int i=0; i<v.size(); i++){
			upd(v[i], v[(i+1)%v.size()]);
		}
	}
	dfs2(1, -1);
	vector<int> v;
	for(int i=0; i<n-1; i++){
		if(dfn[s[i]] > dfn[e[i]]) swap(s[i], e[i]);
		if(cnt[e[i]] >= 2 * k) v.push_back(i+1);
	}
	cout << v.size() << endl;
	for(auto &i : v) printf("%d ", i);
}
