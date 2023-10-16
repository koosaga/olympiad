#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 250005;
const int MAXT = 530000;

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		while(x < MAXN){
			tree[x] = max(tree[x], v);
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret = max(ret, tree[x]);
			x -= x & -x;
		}
		return ret;
	}
	void clear(){ memset(tree, 0, sizeof(tree)); }
}bit;

struct seg{
	pi tree[MAXT];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 2 * lim, pi(1e9, 1e9));
	}
	void upd(int x, pi v){
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(1e9, 1e9);
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}seg;

int n, a[MAXN], ans[MAXN];
int dp[MAXN];
int par[18][MAXN], dep[MAXN];
vector<int> pos[MAXN];

int lca(int x, int y){
	if(dep[x] > dep[y]) swap(x, y);
	int dx = dep[y] - dep[x];
	for(int i=0; i<18; i++){
		if((dx >> i) & 1) y = par[i][y];
	}
	for(int i=17; i>=0; i--){
		if(par[i][x] != par[i][y]){
			x = par[i][x];
			y = par[i][y];
		}
	}
	if(x != y) return par[0][x];
	return x;
}

void solve(){
	bit.clear();
	for(int i=0; i<MAXN; i++) pos[i].clear();
	for(int i=1; i<=n; i++){
		dp[i] = bit.query(a[i] - 1) + 1;
		bit.add(a[i], dp[i]);
	}
	for(int i=0; i<=n; i++){
		pos[dp[i]].push_back(i);
	}
	int len = *max_element(dp + 1, dp + n + 1);
	for(int i=1; i<=len; i++){
		seg.init(pos[i-1].size());
		for(int j=1; j<pos[i-1].size(); j++){
			auto qry = lca(pos[i-1][j-1], pos[i-1][j]);
			seg.upd(j, pi(dep[qry], qry));
		}
		int l = 0, r = 0;
		for(auto &j : pos[i]){
			while(l < pos[i-1].size() && a[pos[i-1][l]] > a[j]) l++;
			while(r < pos[i-1].size() && pos[i-1][r] < j) r++;
			if(l + 1 == r) par[0][j] = pos[i-1][l];
			else par[0][j] = seg.query(l + 1, r - 1).second;
			dep[j] = dep[par[0][j]] + 1;
			for(int k=1; k<18; k++) par[k][j] = par[k-1][par[k-1][j]];
		}
	}
	for(int i=1; i<=n; i++) ans[i] += dep[i] - 1;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	solve();
	reverse(a + 1, a + n + 1);
	for(int i=1; i<=n; i++) a[i] = n + 1 - a[i];
	reverse(ans + 1, ans + n + 1);
	solve();
	reverse(ans + 1, ans + n + 1);
	for(int i=1; i<=n; i++) printf("%d ", ans[i]);
}
