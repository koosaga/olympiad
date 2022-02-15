#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;
const int MAXT = 270000;

pi a[18][MAXN];

pi merge(pi a, pi b){
	return pi(min(a.first, b.first), max(a.second, b.second));
}

struct seg{
	pi tree[MAXT];
	int lim;
	void init(pi *a, int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + MAXT, pi(1e9, -1e9));
		for(int i = 0; i < n; i++){
			tree[i + lim] = a[i];
		}
		for(int i = lim-1; i; i--){
			tree[i] = merge(tree[2*i], tree[2*i+1]);
		}
	}
	pi query(pi i){
		int s = i.first + lim;
		int e = i.second + lim;
		pi ret(1e9, -1e9);
		while(s < e){
			if(s%2 == 1) ret = merge(ret, tree[s++]);
			if(e%2 == 0) ret = merge(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = merge(ret, tree[s]);
		return ret;
	}
}tree[17];

struct seg2{
	int tree[MAXT];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + MAXT, -1e9);
	}
	void spread(int s, int e, int v){
		auto upd = [&](int x, int v){
			tree[x] = max(tree[x], v);
		};
		s += lim;
		e += lim;
		while(s < e){
			if(s%2 == 1) upd(s++, v);
			if(e%2 == 0) upd(e--, v);
			s >>= 1; e >>= 1;
		}
		if(s == e) upd(s, v);
	}
	int query(int x){
		int ret = -1e9;
		for(int i = x + lim; i; i >>= 1) ret = max(ret, tree[i]);
		return ret;
	}
}seg1, seg2;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k, m;
	cin >> n >> k >> m;
	for(int i = 0; i < n; i++) a[0][i] = pi(i, i);
	seg1.init(n);
	seg2.init(n);
	for(int i = 0; i < m; i++){
		int s, e; cin >> s >> e;
		s--; e--;
		if(s < e){
			seg1.spread(s, min(e, s + k - 1), e);
		}
		else{
			seg2.spread(max(e, s - k + 1), s, -e);
		}
	}
	for(int i = 0; i < n; i++){
		a[0][i].first = min(a[0][i].first, -seg2.query(i));
		a[0][i].second = max(a[0][i].second, seg1.query(i));
	}
	for(int i = 1; i <= 17; i++){
		tree[i-1].init(a[i-1], n);
		for(int j = 0; j < n; j++){
			a[i][j] = tree[i-1].query(a[i-1][j]);
		}
	}
	int q; cin >> q;
	while(q--){
		int s, e; cin >> s >> e; s--; e--;
		if(e < a[17][s].first || a[17][s].second < e){
			cout << "-1\n";
			continue;
		}
		pi cur(s, s);
		int ans = 0;
		for(int i = 16; i >= 0; i--){
			auto nxt = tree[i].query(cur);
			if(e < nxt.first || nxt.second < e){
				cur = nxt;
				ans += (1<<i);
			}
		}
		cout << ans + 1 << "\n";
	}
}
