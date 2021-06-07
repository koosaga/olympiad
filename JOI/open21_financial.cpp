#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 300005;
const int MAXT = 1050000;

int n, d, a[MAXN], dp[MAXN];

struct seg{
	int lim;
	int tree[MAXT];
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void upd(int x, int v){
		for(int i = x+lim; i; i >>= 1){
			tree[i] = max(tree[i], v);
		}
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		int ret = 0;
		while(s < e){
			if(s%2 == 1) ret = max(ret, tree[s++]);
			if(e%2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, tree[s]);
		return ret;
	}
}seg;

struct cons{
	struct node{
		int l, r, v, sz;
		node(): l(0), r(0), v(0), sz(0) {}
		node(int x): l(x), r(x), v(x), sz(1) {}
		node operator+(const node &nd)const{
			node ret;
			ret.l = l + (l == sz ? nd.l : 0);
			ret.r = nd.r + (nd.r == nd.sz ? r : 0);
			ret.v = max({v, nd.v, r + nd.l});
			ret.sz = sz + nd.sz;
			return ret;
		}
	}tree[MAXT];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		for(int i = 0; i < n; i++){
			tree[i + lim] = node(1);
		}
		for(int i = lim-1; i; i--) tree[i] = tree[2*i] + tree[2*i+1];
	}
	void upd(int x){
		tree[x + lim] = node(0);
		for(int i = x+lim; i > 1; ){
			i >>= 1;
			tree[i] = tree[2*i] + tree[2*i+1];
		}
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		node L, R;
		while(s < e){
			if(s%2 == 1) L = L + tree[s++];
			if(e%2 == 0) R = tree[e--] + R;
			s >>= 1;
			e >>= 1;
		}
		if(s == e) L = L + tree[s];
		return (L + R).v;
	}
}cons;

#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int main(){
	scanf("%d %d",&n,&d);
	for(int i = 1; i <= n; i++) scanf("%d",&a[i]);
	vector<int> ord(n);
	iota(all(ord), 1);
	sort(all(ord), [&](int x, int y){
		if(a[x] != a[y]) return a[x] < a[y];
		return x > y;
	});
	seg.init(n);
	cons.init(n);
	for(auto &i : ord){
		cons.upd(i);
		int s = 1, e = i;
		while(s != e){
			int m = (s + e) / 2;
			if(cons.query(m, i) >= d) s = m + 1;
			else e = m;
		}
		dp[i] = seg.query(s, i) + 1;
		seg.upd(i, dp[i]);
	}
	cout << seg.query(1, n) << endl;
}
