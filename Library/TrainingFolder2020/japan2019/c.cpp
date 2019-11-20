#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 600005;
const int MAXT = 2100000;

struct seg{
	lint tree[MAXT];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + MAXT, -1e18);
	}
	void upd(int s, int e, lint x){
		auto upd = [&](int x, lint y){
			tree[x] = max(tree[x], y);
		};
		s += lim;
		e += lim;
		while(s < e){
			if(s%2 == 1) upd(s++, x);
			if(e%2 == 0) upd(e--, x);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) upd(s, x);
	}
	lint query(int x){
		lint ret = -1e18;
		for(int i=x+lim; i; i>>=1) ret = max(ret, tree[i]);
		return ret;
	}
}seg[4][2];

struct interval{
	int s, e;
	int color;
	lint cost;
	bool operator<(const interval &i)const{
		return pi(s, e) < pi(i.s, i.e);
	}
};

vector<interval> a;
int n, m, x, y;
vector<int> v;
lint dp[MAXN];

int main(){
	scanf("%d %d %d %d",&n,&m,&x,&y);
	y += x;
	v.push_back(0);
	v.push_back(n);
	for(int i=0; i<m; i++){
		int c, l, r; scanf("%d %d %d",&c,&l,&r);
		v.push_back(l-1);
		v.push_back(r);
		a.push_back({l-1, r, c, 1ll * (r-l+1) * x});
	}
	sort(all(v));
	v.resize(unique(all(v)) - v.begin());
	for(int i=1; i<sz(v); i++){
		a.push_back({v[i-1], v[i], 0, 0});
	}
	for(auto &i : a){
		i.s = lower_bound(all(v), i.s) - v.begin();
		i.e = lower_bound(all(v), i.e) - v.begin();
	}
	sort(all(a));
	for(int i=0; i<8; i++) seg[i/2][i%2].init(sz(a));
	lint dap = 0;
	for(int i=sz(a)-1; i>=0; i--){
		dp[i] = max(dp[i], seg[a[i].color][0].query(a[i].e) - 1ll * v[a[i].e] * x);
		dp[i] = max(dp[i], seg[a[i].color][1].query(a[i].e) - 1ll * v[a[i].e] * (x + y));
		dp[i] += a[i].cost;
		dap = max(dap, dp[i]);
		for(int j=0; j<4; j++){
			if(a[i].color != j){
				seg[j][1].upd(a[i].s, a[i].e, dp[i] + 1ll * v[a[i].s] * (x + y));
			}
			else{
				seg[j][0].upd(a[i].s, a[i].e, dp[i] + 1ll * v[a[i].s] * x);
			}
		}
	}
	cout << dap << endl;
}
