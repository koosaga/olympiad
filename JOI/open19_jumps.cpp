#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXT = 1050005;

struct node{
	int l, r, opt;
	node operator+(const node &x)const{
		return (node){max(l, x.l), max(r, x.r), max({opt, x.opt, l + x.r})};
	}
};

struct seg{
	node tree[MAXT];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void upd(int x, int p, int q){
		x += lim;
		tree[x] = {p, q, 0};
		while(x > 1){
			x >>= 1;
			tree[x] = tree[2*x] + tree[2*x+1];
		}
	}
	node query(int s, int e){
		s += lim;
		e += lim;
		node L = {0, 0, 0}, R = {0, 0, 0};
		while(s < e){
			if(s%2 == 1) L = L + tree[s++];
			if(e%2 == 0) R = tree[e--] + R;
			s >>= 1;
			e >>= 1;
		}
		if(s == e) L = L + tree[s];
		return L + R;
	}
}seg;

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int n; cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++) cin >> a[i];
	vector<int> stk;
	vector<pi> v;
	for(int i = 0; i < n; i++){
		while(sz(stk) && a[stk.back()] < a[i]){
			v.emplace_back(stk.back(), i);
			stk.pop_back();
		}
		if(sz(stk)) v.emplace_back(stk.back(), i);
		stk.push_back(i);
	}
	int q; cin >> q;
	vector<vector<pi>> queries(n);
	for(int i = 0; i < q; i++){
		int l, r; cin >> l >> r;
		l--; r--;
		queries[l].emplace_back(r, i);
	}
	sort(all(v));
	reverse(all(v));
	vector<int> F(n), ret(q);
	int p = 0;
	seg.init(n);
	for(int i = 0; i < n; i++) seg.upd(i, 0, a[i]);
	for(int i = n - 1; i >= 0; i--){
		while(p < sz(v) && v[p].first == i){
			int z = v[p].second * 2 - v[p].first - 1;
			if(z + 1 < n){
				F[z] = max(F[z], a[v[p].first] + a[v[p].second]);
				seg.upd(z, F[z], a[z]);
			}
			p++;
		}
		for(auto &[j, idx] : queries[i]){
			ret[idx] = seg.query(i, j).opt;
		}
	}
	for(auto &i : ret) cout << i << "\n";
}
