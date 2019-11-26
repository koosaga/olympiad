#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 300005;

struct strongly_connected{
	vector<int> gph[MAXN];
	vector<int> rev[MAXN];
	vector<int> dfn;
	vector<int> imp;
	int comp[MAXN], piv;
	bool vis[MAXN];

	void clear(){
		for(auto &i : imp){
			gph[i].clear();
			rev[i].clear();
		}
		imp.clear();
	}

	void add_edge(int s, int e){
		gph[s].push_back(e);
		rev[e].push_back(s);
	}

	void dfs(int x){
		vis[x] = 1;
		for(auto &i : gph[x]){
			if(!vis[i]) dfs(i);
		}
		dfn.push_back(x);
	}

	void rdfs(int x, int p){
		comp[x] = p;
		for(auto &i : rev[x]){
			if(!comp[i]) rdfs(i, p);
		}
	}

	void get_scc(){
		dfn.clear();
		for(auto &i : imp) comp[i] = vis[i] = 0;
		piv = 0;
		for(auto &i : imp){
			if(!vis[i]) dfs(i);
		}
		reverse(dfn.begin(), dfn.end());
		for(auto &i : dfn){
			if(!comp[i]) rdfs(i, ++piv);
		}
	}
}scc;

struct disj{
	int pa[MAXN];
	int conn;
	void init(int n){
		iota(pa, pa + n + 1, 0);
		conn = n;
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p); q = find(q);
		if(p == q) return 0;
		pa[q] = p;
		conn--;
		return 1;
	}
}disj;

int n, m;
pi e[MAXN];

void solve(int l, int r, vector<int> v){
	if(l == r){
		for(auto &i : v) disj.uni(e[i].first, e[i].second);
		if(l < m) printf("%d ", disj.conn);
		return;
	}
	scc.clear();
	int m = (l+r)/2;
	for(auto &i : v){
		e[i].first = disj.find(e[i].first);
		e[i].second = disj.find(e[i].second);
		scc.imp.push_back(e[i].first);
		scc.imp.push_back(e[i].second);
		if(i <= m){
			scc.add_edge(e[i].first, e[i].second);
		}
	}
	scc.get_scc();
	vector<int> L, R;
	for(auto &i : v){
		if(scc.comp[e[i].first] == scc.comp[e[i].second] && i <= m) L.push_back(i);
		else R.push_back(i);
	}
	solve(l, m, L);
	solve(m + 1, r, R);
}

int main(){
	scanf("%d %d",&n,&m);
	disj.init(n);
	for(int i=0; i<m; i++) scanf("%d %d",&e[i].first,&e[i].second);
	vector<int> idx(m);
	iota(all(idx), 0);
	solve(0, m, idx);
}
