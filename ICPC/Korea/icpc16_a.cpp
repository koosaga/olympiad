#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
const int MAXN = 600005;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<int, int>;

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int n, m, mark[MAXN];
vector<pi> gph[MAXN];
vector<int> tr[MAXN];

pi dfs(int x, int p){
	pi ans(0, 0);
	if(!mark[x]) ans.second++;
	for(auto &i : tr[x]){
		if(i == p) continue;
		if(!mark[i] && !mark[x]){
			auto nxt = dfs(i, x);
			ans.first += nxt.second;
			ans.second += min(nxt.first, nxt.second);
		}
		else{
			auto nxt = dfs(i, x);
			ans.first += min(nxt.first, nxt.second);
			ans.second += min(nxt.first, nxt.second);
		}
	}
	return ans;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		if(s > e) swap(s, e);
		if(s + 1 == e) mark[s] = 1;
		if(s == 0 && e == n - 1) mark[n - 1] = 1;
		gph[s].emplace_back(2*i, e);
		gph[e].emplace_back(2*i+1, s);
	}
	int idx = m;
	for(int i=0; i<n; i++){
		if(!mark[i]){
			gph[i].emplace_back(2*idx, (i+1)%n);
			gph[(i+1)%n].emplace_back(2*idx+1, i);
			idx++;
		}
	}
	disj.init(2*idx);
	for(int i=0; i<n; i++){
		sort(gph[i].begin(), gph[i].end(), [&](const pi &a, const pi &b){
			return (a.second - i + n) % n < (b.second - i + n) % n;
		});
		for(int j=0; j<sz(gph[i]); j++){
			disj.uni(gph[i][j].first ^ 1, gph[i][(j+1)%sz(gph[i])].first);
		}
	}
	if(idx == m){
		puts("0");
		return 0;
	}
	int outer_edge = disj.find(2 * m);
	fill(mark, mark + MAXN, 1);
	for(int i=m; i<idx; i++){
		mark[disj.find(2*i+1)] = 0;
	}
	int ret = 0;
	vector<pi> edg;
	for(int i=0; i<m; i++){
		int l = disj.find(2*i), r = disj.find(2*i+1);
		if(l > r) swap(l, r);
		if(l != outer_edge && r != outer_edge){
			edg.emplace_back(l, r);
		}
		else{
			int pos = l + r - outer_edge;
			if(!mark[pos]) mark[pos] = 1, ret++;
		}
	}
	sort(edg.begin(), edg.end());
	edg.resize(unique(edg.begin(), edg.end()) - edg.begin());
	for(auto &i : edg){
		tr[i.first].push_back(i.second);
		tr[i.second].push_back(i.first);
	}
	auto ans = dfs(disj.find(2*m+1), -1);
	ret += min(ans.first, ans.second);
	cout << ret << endl;
}
