#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
const int MAXN = 105;

struct disj{
	int pa[MAXN], comp;
	void init(int n){
		iota(pa, pa + n + 1, 0);
		comp = n;
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p); q = find(q);
		if(p == q) return 0;
		comp--;
		pa[q] = p; return 1;
	}
}uf[2];

namespace spfa{
	vector<pi> gph[MAXN];
	int dist[MAXN], par[MAXN];
	void clear(){
		for(int i=0; i<MAXN; i++) gph[i].clear();
	}
	void add_edge(int s, int e, int x){
		gph[s].emplace_back(x, e);
	}
	vector<int> find_path(int s, int e){
		memset(dist, 0x3f, sizeof(dist));
		bool inq[MAXN] = {};
		dist[s] = 0; 
		queue<int> que; que.push(s); inq[s] = 1;
		while(sz(que)){
			int x = que.front();
			que.pop();
			inq[x] = 0;
			for(auto &i : gph[x]){
				if(dist[i.second] > dist[x] + i.first){
					dist[i.second] = dist[x] + i.first;
					par[i.second] = x;
					if(!inq[i.second]){
						inq[i.second] = 1;
						que.push(i.second);
					}
				}
			}
		}
		if(dist[e] > 1e8) return {};
		vector<int> v;
		for(int j=e; j!=s; j=par[j]){
			v.push_back(par[j]);
		}
		reverse(v.begin(), v.end());
		return v;
	}
}

int n, m;
struct edge{
	int s, e, cost, color;
}edg[MAXN];
bool indep[MAXN];

int aug(){
	spfa::clear();
	auto add_edge = [&](int s, int e){
		int cost = (indep[e] ? -edg[e].cost : edg[e].cost);
		spfa::add_edge(s, e, -cost * 1024 + 1);
	};
	for(int i=0; i<m; i++){
		if(indep[i]) continue;
		uf[0].init(n);
		uf[1].init(n);
		for(int j=0; j<m; j++){
			if(i != j && !indep[j]){
				if(edg[j].color & 1) uf[0].uni(edg[j].s, edg[j].e);
				if(edg[j].color & 2) uf[1].uni(edg[j].s, edg[j].e);
			}
		}
		if(uf[0].comp == 1) add_edge(m, i);
		else{
			for(int j=0; j<m; j++){
				if(indep[j] && (edg[j].color & 1) && uf[0].find(edg[j].s) != uf[0].find(edg[j].e)){
					add_edge(j, i);
				}
			}
		}
		if(uf[1].comp == 1) add_edge(i, m + 1);
		else{
			for(int j=0; j<m; j++){
				if(indep[j] && (edg[j].color & 2) && uf[1].find(edg[j].s) != uf[1].find(edg[j].e)){
					add_edge(i, j);
				}
			}
		}
	}
	auto ans = spfa::find_path(m, m+1);
	if(sz(ans) == 0) return -1.1e9;
	int ret = spfa::dist[m+1] >> 10;
	for(int i=1; i<sz(ans); i++){
		indep[ans[i]] ^= 1;
	}
	return -ret;
}

int main(){
	scanf("%d %d",&n,&m);
	auto val = [&](char c){
		if(c == 'R') return 1;
		if(c == 'B') return 2;
		return 3;
	};
	uf[0].init(n);
	uf[1].init(n);
	lint ret = 0;
	for(int i=0; i<m; i++){
		int a, b, w;
		char st[5];
		scanf("%d %d %d",&a,&b,&w);
		scanf("%s", st);
		edg[i] = {a, b, w, val(st[0])};
		if(edg[i].color & 1) uf[0].uni(edg[i].s, edg[i].e);
		if(edg[i].color & 2) uf[1].uni(edg[i].s, edg[i].e);
		ret += w;
	}
	if(uf[0].comp != 1 || uf[1].comp != 1){
		while(m--) puts("-1");
		return 0;
	}
	vector<int> v;
	for(int i=0; i<m; i++){
		if(ret < 1e9) v.push_back(ret);
		else v.push_back(-1);
		ret -= aug();
	}
	reverse(v.begin(), v.end());
	for(auto &i : v) cout << i << endl;
}
