#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
using word = unsigned long long;
const int MAXN = 300005;
const int mod = 998244353;
typedef complex<double> base;

// NTT sucks!
void fft(vector<base> &a, bool inv){
	int n = a.size(), j = 0;
	vector<base> roots(n/2);
	for(int i=1; i<n; i++){
		int bit = (n >> 1);
		while(j >= bit){
			j -= bit;
			bit >>= 1;
		}
		j += bit;
		if(i < j) swap(a[i], a[j]);
	}
	double ang = 2 * acos(-1) / n * (inv ? -1 : 1);
	for(int i=0; i<n/2; i++){
		roots[i] = base(cos(ang * i), sin(ang * i));
	}
	for(int i=2; i<=n; i<<=1){
		int step = n / i;
		for(int j=0; j<n; j+=i){
			for(int k=0; k<i/2; k++){
				base u = a[j+k], v = a[j+k+i/2] * roots[step * k];
				a[j+k] = u+v;
				a[j+k+i/2] = u-v;
			}
		}
	}
	if(inv) for(int i=0; i<n; i++) a[i] /= n; // skip for OR convolution.
}

vector<lint> multiply(vector<lint> &v, vector<lint> &w){
	vector<base> fv(v.begin(), v.end()), fw(w.begin(), w.end());
	int n = 2; while(n < v.size() + w.size()) n <<= 1;
	fv.resize(n); fw.resize(n);
	fft(fv, 0); fft(fw, 0);
	for(int i=0; i<n; i++) fv[i] *= fw[i];
	fft(fv, 1);
	vector<lint> ret(n);
	for(int i=0; i<n; i++) ret[i] = (lint)round(fv[i].real());
	return ret;
}
vector<lint> multiply(vector<lint> &v, vector<lint> &w, lint mod){
	int n = 2; while(n < v.size() + w.size()) n <<= 1;
	vector<base> v1(n), v2(n), r1(n), r2(n);
	for(int i=0; i<v.size(); i++){
		v1[i] = base(v[i] >> 15, v[i] & 32767);
	}
	for(int i=0; i<w.size(); i++){
		v2[i] = base(w[i] >> 15, w[i] & 32767);
	}
	fft(v1, 0);
	fft(v2, 0);
	for(int i=0; i<n; i++){
		int j = (i ? (n - i) : i);
		base ans1 = (v1[i] + conj(v1[j])) * base(0.5, 0);
		base ans2 = (v1[i] - conj(v1[j])) * base(0, -0.5);
		base ans3 = (v2[i] + conj(v2[j])) * base(0.5, 0);
		base ans4 = (v2[i] - conj(v2[j])) * base(0, -0.5);
		r1[i] = (ans1 * ans3) + (ans1 * ans4) * base(0, 1);
		r2[i] = (ans2 * ans3) + (ans2 * ans4) * base(0, 1);
	}
	fft(r1, 1);
	fft(r2, 1);
	vector<lint> ret(n);
	for(int i=0; i<n; i++){
		lint av = (lint)round(r1[i].real());
		lint bv = (lint)round(r1[i].imag()) + (lint)round(r2[i].real());
		lint cv = (lint)round(r2[i].imag());
		av %= mod, bv %= mod, cv %= mod;
		ret[i] = (av << 30) + (bv << 15) + cv;
		ret[i] %= mod;
		ret[i] += mod;
		ret[i] %= mod;
	}
	return ret;
}

int n, k, a[MAXN];
vector<int> gph[MAXN];

lint ipow(int x, int p){
	lint ret = 1, piv = x;
	for(; p; p >>= 1){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
	}
	return ret;
}

namespace dcmp{
	vector<int> dfn;
	int vis[MAXN], siz[MAXN], msz[MAXN];
	void dfs(int x, int p){
		siz[x] = 1;
		msz[x] = 0;
		dfn.push_back(x);
		for(auto &i : gph[x]){
			if(!vis[i] && i != p){
				dfs(i, x);
				siz[x] += siz[i];
				msz[x] = max(msz[x], siz[i]);
			}
		}
	}
	int get_center(int x){
		dfn.clear();
		dfs(x, -1);
		pi ret(1e9, 1e9);
		for(auto &i : dfn){
			int val = max(msz[i], sz(dfn) - siz[i]);
			ret = min(ret, pi(val, i));
		}
		return ret.second;
	}
	int dist[19][MAXN];
	int par[MAXN], pae[MAXN], dep[MAXN];
	vector<int> ds[2 * MAXN];
	int piv;
	void dfs1(int x, int p, int *ptr, vector<int> &ds, int d = 0){
		if(ptr != NULL) ptr[x] = d;
		if(sz(ds) <= d + 1) ds.resize(d + 2);
		ds[d + 1]++;
		for(auto &i : gph[x]){
			if(i != p && !vis[i]){
				dfs1(i, x, ptr, ds, d + 1);
			}
		}
	}
	void add(int x, int v, vector<int> &tree){
		for(int i=x+1; i<sz(tree); i+=i&-i){
			tree[i] += v;
		}
	}
	int query(int x, vector<int> &tree){
		if(x < 0) return 0;
		int ret = 0;
		for(int i=min(x + 1, sz(tree) - 1); i; i-=i&-i){
			ret += tree[i];
		}
		return ret;
	}
	void mark(int v){
		int pedge = -1;
		for(int i=v; i; i = par[i]){
			add(dist[dep[i]][v], -1, ds[i]);
			if(~pedge) add(dist[dep[i]][v], -1, ds[pedge]);
			pedge = pae[i];
		}
	}
	int query(int v){
		int pedge = -1;
		int ret = 0;
		for(int i=v; i; i = par[i]){
			int new_dist = k - dist[dep[i]][v];
			ret += query(new_dist, ds[i]);
			if(~pedge) ret -= query(new_dist, ds[pedge]);
			pedge = pae[i];
		}
		return ret;
	}
	void make_fenwick(vector<int> &v){
		for(int i=1; i<sz(v); i++){
			if(i + (i & -i) >= sz(v)) continue;
			v[i + (i & -i)] += v[i];
		}
	}
	void init(int x = 1, int p = 0, int q = 0){
		x = get_center(x);
		if(p){
			par[x] = p;
			pae[x] = q;
			dep[x] = dep[p] + 1;
		}
		dfs1(x, -1, dist[dep[x]], ds[x]);
		make_fenwick(ds[x]);
		vis[x] = 1;
		vector<pi> v;
		for(auto &i : gph[x]){
			if(vis[i]) continue;
			piv++;
			dfs1(i, x, NULL, ds[piv + n], 1);
			v.emplace_back(i, piv + n);
			make_fenwick(ds[piv + n]);
		}
		for(auto &[p, q] : v){
			init(p, x, q);
		}
	}
}

lint fact[MAXN], invf[MAXN];

void solve(){
	fact[0] = invf[0] = 1;
	for(int i=1; i<=n; i++){
		fact[i] = fact[i-1] * i % mod;
		invf[i] = ipow(fact[i], mod - 2);
	}
	vector<lint> poly1(n + 1);
	vector<lint> poly2(n + 1);
	for(int i=0; i<=n; i++) poly1[i] = a[i] * fact[i] % mod;
	for(int i=0; i<=n; i++) poly2[i] = invf[n-i];
	auto pwr = multiply(poly1, poly2, mod);
	for(int i=0; i<n; i++){
		printf("%lld ", pwr[n + i] * invf[i] % mod);
	}
}

int vis[MAXN];

int main(){
	scanf("%d %d",&n,&k);
	for(int i=1; i<n; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	vector<int> ord;
	queue<int> que;
	que.push(1);
	vis[1] = 1;
	while(sz(que)){
		int x = que.front(); que.pop();
		ord.push_back(x);
		for(auto &i : gph[x]){
			if(!vis[i]){
				vis[i] = 1;
				que.push(i);
			}
		}
	}
	reverse(all(ord));
	dcmp::init();
	for(int i=0; i<n; i++){
		dcmp::mark(ord[i]);
		a[dcmp::query(ord[i])]++;
	}
	solve();
}
