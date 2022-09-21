#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 1500005;
const int MAXT = 8400000;
 
const int mod = 1e9 + 7;
 
struct mint {
    int val;
    mint() { val = 0; }
    mint(const lint& v) {
        val = (-mod <= v && v < mod) ? v : v % mod;
        if (val < 0) val += mod;
    }
 
    friend ostream& operator<<(ostream& os, const mint& a) { return os << a.val; }
    friend bool operator==(const mint& a, const mint& b) { return a.val == b.val; }
    friend bool operator!=(const mint& a, const mint& b) { return !(a == b); }
    friend bool operator<(const mint& a, const mint& b) { return a.val < b.val; }
 
    mint operator-() const { return mint(-val); }
    mint& operator+=(const mint& m) { if ((val += m.val) >= mod) val -= mod; return *this; }
    mint& operator-=(const mint& m) { if ((val -= m.val) < 0) val += mod; return *this; }
    mint& operator*=(const mint& m) { val = (lint)val*m.val%mod; return *this; }
    friend mint ipow(mint a, lint p) {
        mint ans = 1; for (; p; p /= 2, a *= a) if (p&1) ans *= a;
        return ans;
    }
    friend mint inv(const mint& a) { assert(a.val); return ipow(a, mod - 2); }
    mint& operator/=(const mint& m) { return (*this) *= inv(m); }
 
    friend mint operator+(mint a, const mint& b) { return a += b; }
    friend mint operator-(mint a, const mint& b) { return a -= b; }
    friend mint operator*(mint a, const mint& b) { return a *= b; }
    friend mint operator/(mint a, const mint& b) { return a /= b; }
    operator int64_t() const {return val; }
};
 
struct seg{
	mint tree[MAXT];
	int lim;
	void init(int n){
		fill(tree, tree + MAXT, mint(1));
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void upd(int s, int e, mint x){
		s += lim;
		e += lim;
		while(s < e){
			if(s%2 == 1) tree[s] *= x, s++;
			if(e%2 == 0) tree[e] *= x, e--;
			s >>= 1;
			e >>= 1;
		}
		if(s == e) tree[s] *= x;
	}
	mint query(int x){
		mint ret = 1;
		for(int i = x + lim; i; i >>= 1) ret *= tree[i];
		return ret;
	}
}seg;
 
vector<int> gph[MAXN];
int par[MAXN], dist[2][MAXN], h[MAXN], label[MAXN];
 
void dfs2(int x, int p, vector<int> &indiam){
	for(auto &y : gph[x]){
		if(indiam[y] || y == p) continue;
		label[y] = label[x];
		dfs2(y, x, indiam);
		h[x] = max(h[x], h[y] + 1);
	}
}
 
pi dfs(int x, int p, int c, int d = 0){
	dist[c][x] = d;
	pi ret(0, x);
	for(auto &y : gph[x]){
		if(y == p) continue;
		par[y] = x;
		auto [D, v] = dfs(y, x, c, d + 1);
		ret = max(ret, pi(D + 1, v));
	}
	return ret;
}
 
bool removed[MAXN];
 
mint dfs3(int x, int p, int t){
	mint ans = 1;
	for(auto &y : gph[x]){
		if(y != p && !removed[y]){
			ans *= dfs3(y, x, t - 1);
		}
	}
	if(t > 0) ans += mint(1);
	return ans;
}
 
struct node{
	int vtx;
	mint cnt;
};
 
int n, k;
 
int up(int x, int m){
	int y = m - x % k;
	if(y < 0) y += k;
	return x + y;
}
 
int down(int x, int m){
	int y = x % k - m;
	if(y < 0) y += k;
	return x - y;
}
 
int dfs4(int x, int p, vector<int> &cnt, int &tot){
	vector<int> v = {0};
	for(auto &y : gph[x]){
		if(y != p){
			int w = dfs4(y, x, cnt, tot);
			v.push_back(w + 1);
		}
	}
	sort(all(v));
	if(sz(v) >= 2 && v[sz(v) - 2] + v[sz(v) - 1] >= k - 1){
		tot++;
		vector<int> newCand;
		newCand.push_back(dist[0][label[x]] % k);
		if(k % 2 == 0) newCand.push_back((dist[0][label[x]] + k / 2) % k);
		for(auto &d : newCand){
			int cross = up(dist[0][x], d) - dist[0][x];
			if(cross == 0){
				cnt[d]++;
				continue;
			}
			int w1 = v[sz(v) - 2];
			int w2 = v[sz(v) - 1];
			bool Left = (cross <= w1);
			bool Right = (cross <= w2);
			if(!Left && !Right) continue;
			if(Left && Right){
				if(2 * cross <= k - 1) continue;
			}
			if(min(cross - 1, w1) + min(cross - 1, w2) >= k - 1) continue;
			cnt[d]++;
		}
	}
	return v.back();
}
 
int main(){	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	for(int i = 0; i < n - 1; i++){
		int u, v; cin >> u >> v;
		u--; v--;
		gph[u].push_back(v);
		gph[v].push_back(u);
	}
	int l = dfs(0, -1, 0).second;
	auto [d, r] = dfs(l, -1, 0);
	if(d < k - 1){
		cout << "YES\n" << ipow(mint(2), n) << "\n";
		return 0;
	}
	dfs(r, -1, 1);
	vector<int> v = {l};
	for(int i = l; i != r; i = par[i]) v.push_back(par[i]);
	vector<int> chk(n), indiam(n);
	vector<int> counts(k); int total = 0;
	for(auto &x : v) chk[x] = indiam[x] = 1;
	for(auto &x : v){
		label[x] = x;
		dfs2(x, -1, indiam);
		for(auto &y : gph[x]){
			if(!indiam[y]){
				dfs4(y, x, counts, total);
			}
		}
	}
	int pwr = 0;
	for(int i = 0; i < n; i++){
		if(!indiam[i] && max(dist[0][i], dist[1][i]) + h[i] < k - 1){
			removed[i] = 1;
			pwr++;
		}
		if(min(dist[0][i], dist[1][i]) + h[i] >= k - 1){
			chk[i] = 1;
		}
	}
	seg.init(k);
	for(int i = 0; i < n; i++){
		if(!removed[i] && !indiam[i] && !chk[i] && (indiam[par[i]] || chk[par[i]])){
			int t = k - 1 - max(dist[0][i], dist[1][i]);
			if(t < 0) continue;
			mint cnt = dfs3(i, par[i], t); 
			assert(dist[0][i] != dist[1][i]);
			if(dist[0][i] > dist[1][i]){
				seg.upd(dist[0][i], k - 1, cnt);
			}
			else{
				if(dist[1][i] >= k) continue;
				int window = k - dist[1][i];
				int pos = (dist[0][r] + 1) % k;
				seg.upd(pos, min(k - 1, pos + window - 1), cnt);
				if(pos + window > k){
					seg.upd(0, pos + window - k - 1, cnt);
				}
			}
		}
	}
	mint ans = 0;
	bool tak = false;
	for(int i = 0; i < n; i++){
		if(indiam[i] || removed[i]) continue;
		if(min(dist[0][i], dist[1][i]) + h[i] >= k - 1){
			int L = dist[0][i] % k;
			int R = (dist[0][label[i]] % k - (dist[1][i] - dist[1][label[i]])) % k + k;
			R %= k;
			if(L != R){
				counts[L]--; counts[R]--;
			}
		}
	}
	for(int i = 0; i < k; i++){
		if(counts[i] != total) continue;
		tak = true;
		ans += seg.query(i);
	}
	if(tak) cout << "YES\n" << ans * ipow(mint(2), pwr) << "\n";
	else cout << "NO\n0\n";
}
 
