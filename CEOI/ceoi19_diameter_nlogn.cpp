#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
const int MAXT = 530000;
using lint = long long;
using pi = pair<lint, lint>;

int n, q;

struct node{
	lint adj[4][4];
	lint lazy;
};

node merge(node x, node y){
	node ret;
	ret.lazy = 0;
	for(int i=0; i<4; i++){
		for(int j=i; j<4; j++){
			ret.adj[i][j] = -1e18;
			for(int k=i; k<=j; k++){
				ret.adj[i][j] = max(ret.adj[i][j], x.adj[i][k] + y.adj[k][j]);
			}
		}
	}
	return ret;
}

struct seg{
	node tree[MAXT];
	void Apply(int p, lint v){
		tree[p].lazy += v;
		tree[p].adj[0][1] += v;
		tree[p].adj[0][2] -= v;
		tree[p].adj[1][2] -= 2 * v;
		tree[p].adj[1][3] -= v;
		tree[p].adj[2][3] += v;
	}
	void upd(int s, int e, int ps, int pe, int p, lint v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			Apply(p, v);
			return;
		}
		if(tree[p].lazy){
			Apply(2 * p, tree[p].lazy);
			Apply(2 * p + 1, tree[p].lazy);
			tree[p].lazy = 0;
		}
		int pm = (ps + pe) / 2;
		upd(s, e, ps, pm, 2*p, v);
		upd(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = merge(tree[2*p], tree[2*p+1]);
	}
}seg;

int par[MAXN], piv;
lint pae[MAXN];
vector<pi> gph[MAXN];
map<pi, int> mp;

void dfs(int x, int p){
	for(auto &i : gph[x]){
		if(i.second == p) continue;
		par[i.second] = x;
		pae[i.second] = i.first;
		seg.upd(++piv, n, 0, n, 1, i.first);
		mp[pi(x, i.second)] = piv;
		dfs(i.second, x);
		seg.upd(++piv, n, 0, n, 1, -i.first);
		mp[pi(i.second, x)] = piv;
	}
}

int S[MAXN], E[MAXN];
lint X[MAXN];

int main(){
	lint w;
	scanf("%d %d %lld",&n,&q,&w);
	for(int i=0; i<n-1; i++){
		int s, e; lint x; 
		scanf("%d %d %lld",&s,&e,&x);
		gph[s].emplace_back(x, e);
		gph[e].emplace_back(x, s);
		S[i] = s;
		E[i] = e;
		X[i] = x;
	}
	n = 2*n-2;
	dfs(1, 0);
	lint last = 0;
	while(q--){
		lint d, e; scanf("%lld %lld",&d,&e);
		d = (d + last) % (n / 2);
		e = (e + last) % w;
		int p1 = mp[pi(S[d], E[d])];
		int p2 = mp[pi(E[d], S[d])];
		if(p1 > p2) swap(p1, p2);
		seg.upd(p1, n, 0, n, 1, e - X[d]);
		seg.upd(p2, n, 0, n, 1, -e + X[d]);
		X[d] = e;
		last = seg.tree[1].adj[0][3];
		printf("%lld\n", last);
	}
}
