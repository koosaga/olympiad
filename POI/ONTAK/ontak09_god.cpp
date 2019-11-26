#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;

struct scc{
	vector<int> gph[MAXN];
	vector<int> rev[MAXN];
	vector<int> imp;

	vector<int> dfn;
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
		reverse(all(dfn));
		for(auto &i : dfn){
			if(!comp[i]) rdfs(i, ++piv);
		}
	}
}scc;

struct disj{
	int pa[MAXN], cnt[MAXN];
	int zero;
	void init(int n){
		zero = n;
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	void add(int x, int v){
		x = find(x);
		if(cnt[x] == 0) zero--;
		cnt[x] += v;
		if(cnt[x] == 0) zero++;
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; 
		if(cnt[q] == 0) zero--;
		add(p, cnt[q]);
		return 1;
	}
}disj;

int n, m, ans[MAXN];
vector<pi> edg;

void solve(int s, int e, vector<int> &v){
	if(s == e){
		disj.add(edg[s].second, +1);
		for(auto &i : v){
			disj.add(edg[i].second, -1);
			disj.uni(edg[i].first, edg[i].second);
		}
		ans[s] = disj.zero;
		return;
	}
	int m = (s+e)/2;
	scc.clear();
	for(auto &i : v){
		int l = disj.find(edg[i].first);
		int r = disj.find(edg[i].second);
		if(i <= m){
			scc.add_edge(l, r);
		}
		scc.imp.push_back(l);
		scc.imp.push_back(r);
	}
	scc.get_scc();
	vector<int> l, r;
	for(auto &i : v){
		int ll = disj.find(edg[i].first);
		int rr = disj.find(edg[i].second);
		if(scc.comp[ll] == scc.comp[rr] && i <= m){
			l.push_back(i);
		}
		else{
			r.push_back(i);
		}
	}
	solve(s, m, l);
	solve(m + 1, e, r);
}

int main(){
	scanf("%d %d",&n,&m);
	vector<pi> tmp(m);
	vector<int> ord(m);
	for(auto &i : tmp) scanf("%d %d",&i.first,&i.second);
	int q; scanf("%d",&q);
	for(int i=0; i<q; i++){
		int x; scanf("%d",&x);
		ord[x - 1] = m - i;
	}
	int cur = m - q;
	for(int i=0; i<m; i++){
		if(!ord[i]) ord[i] = cur--;
	}
	edg.resize(m);
	for(int i=0; i<m; i++) edg[ord[i] - 1] = tmp[i];
	vector<int> elist(m);
	iota(elist.begin(), elist.end(), 0);
	disj.init(n);
	solve(0, m - 1, elist);
	for(int i=m-2; i>=m-q-1; i--){
		if(i >= 0) printf("%d\n", ans[i]);
		else printf("%d\n", n);
	}
}
