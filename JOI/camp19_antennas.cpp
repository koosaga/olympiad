#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 200005;
const int MAXT = 530000;
const int inf = 1e9 + 100;

struct node{
	int rangeMin;
	int kappaMax;
	int opt;
}tree[MAXT];

void init(int s, int e, int p){
	tree[p] = {inf, -inf, -inf};
	if(s == e){
		return;
	}
	int m = (s + e) / 2;
	init(s, m, 2*p);
	init(m + 1, e, 2*p+1);
}

void lazydown(int p){
	for(int i = 2 * p; i < 2 * p + 2; i++){
		tree[i].kappaMax = max(tree[i].kappaMax, tree[p].kappaMax);
		tree[i].opt = max(tree[i].opt, tree[p].kappaMax - tree[i].rangeMin);
	}
	tree[p].kappaMax = -inf;
}

void update(int pos, int s, int e, int p, int v){
	if(s == e){
		tree[p].rangeMin = v;
		return;
	}
	int m = (s + e) / 2;
	lazydown(p);
	if(pos <= m) update(pos, s, m, 2*p, v);
	else update(pos, m+1, e, 2*p+1, v);
	tree[p].rangeMin = min(tree[2*p].rangeMin, tree[2*p+1].rangeMin);
	tree[p].opt = max(tree[2*p].opt, tree[2*p+1].opt);
}

int query(int s, int e, int ps, int pe, int p){
	if(e < ps || pe < s) return -inf;
	if(s <= ps && pe <= e) return tree[p].opt;
	lazydown(p);
	int pm = (ps+pe)/2;
	return max(query(s, e, ps, pm, 2*p), query(s, e, pm+1, pe, 2*p+1));
}

void setKappa(int s, int e, int ps, int pe, int p, int v){
	if(e < ps || pe < s) return;
	if(s <= ps && pe <= e){
		tree[p].kappaMax = max(tree[p].kappaMax, v);
		tree[p].opt = max(tree[p].opt, v - tree[p].rangeMin);
		return;
	}
	lazydown(p);
	int pm = (ps+pe)/2;
	setKappa(s, e, ps, pm, 2*p, v);
	setKappa(s, e, pm+1, pe, 2*p+1, v);
	tree[p].opt = max(tree[2*p].opt, tree[2*p+1].opt);
}

vector<int> solve(vector<int> a, vector<pi> b, vector<pi> q){
	int n = sz(a);
	vector<int> ds(n, inf);
	vector<int> hist(n, -2 * inf);
	vector<vector<pi>> swp(n);
	init(0, n - 1, 1);
	for(int i = 0; i < n; i++){
		int l = i - b[i].second;
		int r = i - b[i].first;
		l = max(l, 0);
		r = min(r, i - 1);
		if(l <= r){
			if(l > 0) swp[l - 1].emplace_back(inf, i);
			swp[r].emplace_back(a[i], i); 
		}
	}
	vector<int> ret(sz(q));
	vector<vector<pi>> pos(n);
	for(int i = 0; i < sz(q); i++){
		pos[q[i].first].emplace_back(i, q[i].second);
	}
	for(int i = n - 1; i >= 0; i--){
		for(auto &[v, idx] : swp[i]) update(idx, 0, n - 1, 1, v);
		int l = i + b[i].first, r = min(n - 1, i + b[i].second);
		if(l <= r){
			setKappa(l, r, 0, n - 1, 1, a[i]);
		}
		for(auto &[idx, j] : pos[i]){
			ret[idx] = query(i, j, 0, n - 1, 1);
		}
	}
	return ret;
} 

int main(){	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n; cin >> n;
	vector<int> a(n);
	vector<pi> b(n);
	for(int i = 0; i < n; i++){
		cin >> a[i] >> b[i].first >> b[i].second;
	}
	int q; cin >> q;
	vector<pi> Q(q);
	for(auto &[x, y] : Q){
		cin >> x >> y;
		x--; y--;
	}
	auto ans1 = solve(a, b, Q);
	for(auto &x : a) x = 1e9 + 1 -x;
	auto ans2 = solve(a, b, Q);
	for(int i = 0; i < q; i++){
		int dap = max({ans1[i], ans2[i], -1});
		cout << dap << "\n";
	}
}
