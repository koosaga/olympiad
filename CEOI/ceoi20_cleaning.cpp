#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;
const int MAXT = 270000;
const int mod = 1e9 + 7;

int n, q;

struct seg{
	struct node{
		int sum, lazy;
	}tree[MAXT];
	void rev(int p, int ps, int pe){
		tree[p].sum = pe - ps + 1 - tree[p].sum;
		tree[p].lazy ^= 1;
	}
	void lazydown(int p, int ps, int pe){
		int pm = (ps + pe) / 2;
		if(tree[p].lazy){
			tree[p].lazy = 0;
			rev(2*p, ps, pm);
			rev(2*p+1, pm+1, pe);
		}
	}
	void upd(int s, int e, int ps = 1, int pe = n, int p = 1){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			rev(p, ps, pe);
			return;
		}
		lazydown(p, ps, pe);
		int pm = (ps + pe) / 2;
		upd(s, e, ps, pm, 2*p);
		upd(s, e, pm+1, pe, 2*p+1);
		tree[p].sum = tree[2*p].sum + tree[2*p+1].sum;
	}
	int query(int s, int e, int ps = 1, int pe = n, int p = 1){
		if(e < ps || pe < s) return 0;
		if(s <= ps && pe <= e) return tree[p].sum;	
		lazydown(p, ps, pe);
		int pm = (ps + pe) / 2;
		return query(s, e, ps, pm, 2*p) + query(s, e, pm+1, pe, 2*p+1);
	}
}seg;

vector<int> gph[MAXN];
int din[MAXN], dout[MAXN], sz[MAXN], piv;
int par[MAXN], chn[MAXN];
 
lint query(){
	if(seg.query(1, 1)) return -1;
	int ret = 2 * n - 2 - seg.query(2, n);
	return ret;
}
 
void add(int x, int v){
	while(x){
		int st = din[chn[x]];
		int ed = din[x];
		seg.upd(st, ed);
		x = par[chn[x]];
	}
}
 
void dfs(int x, int p = -1){
	sz[x] = 1;
	for(auto &i : gph[x]){
		gph[i].erase(find(all(gph[i]), x));
		par[i] = x;
		dfs(i);
		sz[x] += sz[i];
	}
	dout[x] = piv;
}

void hld(int x){
	din[x] = ++piv;
	if(sz(gph[x])){
		sort(all(gph[x]), [&](int x, int y){
			return sz[x] > sz[y];
		});
		chn[gph[x][0]] = chn[x];
		hld(gph[x][0]);
		for(int i=1; i<sz(gph[x]); i++){
			chn[gph[x][i]] = gph[x][i];
			hld(gph[x][i]);
		}
	}
}

int leaf[MAXN];

int main(){
	scanf("%d %d",&n,&q);
	for(int i=0; i<n-1; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	for(int i=1; i<=n; i++) leaf[i] = (sz(gph[i]) == 1);
	dfs(1);
	chn[1] = 1;
	hld(1);
	for(int i=1; i<=n; i++) if(leaf[i]) add(i, 1);
	while(q--){
		int k;
		set<int> s;
		vector<int> v;
		scanf("%d",&k);
		for(int i=0; i<k; i++){
			int x; scanf("%d",&x);
			if(!(leaf[x] && s.find(x) == s.end())){
				v.push_back(x);
			}
			s.insert(x);
		}
		for(auto &i : v) add(i, +1);
		lint q = query();
		if(q == -1) printf("-1\n");
		else printf("%lld\n", q + k);
		for(auto &i : v) add(i, -1);
	}
}

