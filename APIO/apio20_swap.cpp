#include "swap.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;
const int mod = 1e9 + 7;

struct disj{
	struct node{
		int pa, max_deg, cycle, updated;
		bool operator<(const node &n)const{
			return updated < n.updated;
		}
	};
	// persistent
	vector<node> nodes[MAXN];

	// only used in creation
	vector<int> memb[MAXN];
	int deg[MAXN];
	void init(int n){
		for(int i=0; i<n; i++){
			memb[i].push_back(i);
			nodes[i].push_back({i, 0, 0, -1});
		}
	}
	int find(int x){
		return nodes[x].back().pa;
	}
	void add_edge(int x, int y, int i){
		deg[x]++; deg[y]++;
		int new_deg = max(deg[x], deg[y]);
		x = find(x); y = find(y);
		if(x != y){
			if(sz(memb[x]) < sz(memb[y])) swap(x, y);
			for(auto &v : memb[y]){
				node prv = nodes[v].back();
				prv.pa = x;
				prv.updated = i;
				nodes[v].push_back(prv);
				memb[x].push_back(v);
			}
			node prv = nodes[x].back();
			prv.max_deg = max(prv.max_deg, nodes[y].back().max_deg);
			prv.cycle |= nodes[y].back().cycle;
			prv.updated = i;
			nodes[x].push_back(prv);
			memb[y].clear();
		}
		node prv = nodes[x].back();
		if(x == y) prv.cycle = 1;
		prv.max_deg = max(prv.max_deg, new_deg);
		prv.updated = i;
		nodes[x].push_back(prv);
	}
	node get_node(int x, int t){
		return *--upper_bound(all(nodes[x]), (node){-1, -1, 0, t});
	}
}disj;

bool isGood(int u, int v, int m){
	auto gnx = disj.get_node(u, m);
	auto gny = disj.get_node(v, m);
	if(gnx.pa != gny.pa) return 0;
	auto val = disj.get_node(gnx.pa, m);
	return val.max_deg >= 3 || val.cycle;
}

int n, m;

struct edg{
	int s, e, x;
}a[MAXN];

void init(int N, int M,
		std::vector<int> U, std::vector<int> V, std::vector<int> W) {
	n = N; m = M;
	disj.init(n);
	for(int i=0; i<M; i++) a[i] = {U[i], V[i], W[i]};
	sort(a, a + M, [&](const edg &a, const edg &b){
		return a.x < b.x;
	});
	for(int i=0; i<M; i++) disj.add_edge(a[i].s, a[i].e, i);
}

int getMinimumFuelCapacity(int X, int Y) {
	int s = 0, e = m;
	while(s != e){
		int m = (s + e) / 2;
		if(isGood(X, Y, m)) e = m;
		else s = m + 1;
	}
	if(s == m) return -1;
	return a[s].x;
}
