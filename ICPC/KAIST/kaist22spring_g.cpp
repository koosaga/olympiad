#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 500005;
const int MAXT = 1050000;
const int mod = 998244353;

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

using func = pair<mint, mint>;
func operator+(func a, func b){
	return func(a.first + b.first, a.second + b.second);
}

struct poly{
	mint xy, x, y, c;
	poly operator+(const poly &p)const{
		return (poly){p.xy + xy, p.x + x, p.y + y, p.c + c};
	}
};

poly make(func b, func a){
	return (poly){a.first * b.first, a.second * b.first, b.second * a.first, a.second * b.second};
}

struct seg{
	struct node{
		func asum, bsum;
		poly sum;
		node operator+(const node &nd)const{
			return (node){asum + nd.asum, bsum + nd.bsum, sum + nd.sum + make(nd.asum, bsum)};
		}
	}tree[MAXT];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void add(int pos, int p, mint x, mint y){
		pos += lim;
		if(p == 0) tree[pos].asum = tree[pos].asum + func(x, y);
		else tree[pos].bsum = tree[pos].bsum + func(x, y);
		tree[pos].sum = make(tree[pos].asum, tree[pos].bsum);
		while(pos > 1){
			pos >>= 1;
			tree[pos] = tree[2*pos] + tree[2*pos+1];
		}
	}
}seg;

void add(int pos, int p, lint a, lint b){
	seg.add(pos, p, a, b);
}

mint query(int posa, int posb){
	auto nd = seg.tree[1].sum;
	return nd.xy * mint(posa) * mint(posb) + nd.x * mint(posa) + nd.y * mint(posb) + nd.c;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int q; cin >> q;
	vector<pi> seqs(q + 2);
	cin >> seqs[0].second; seqs[0].first = 0;
	cin >> seqs[1].second; seqs[1].first = 2;
	for(int i = 2; i < sz(seqs); i++){
		cin >> seqs[i].first >> seqs[i].second;
	}
	vector<int> v;
	for(auto &i : seqs){
		if(i.first & 2) i.second *= -1;
		v.push_back(i.second);
	}
	sort(all(v));
	v.resize(unique(all(v)) - v.begin());
	for(auto &i : seqs){
		i.second = lower_bound(all(v), i.second) - v.begin();
	}
	seg.init(sz(v));
	vector<int> a, b;
	vector<int> stka = {-1};
	vector<int> stkb = {-1};
	auto insertA = [&](int v){
		a.push_back(v);
		int idx = sz(a) - 1;
		while(sz(stka) > 1 && a[stka.back()] >= a[idx]){
			int l = idx - stka.back();
			int r = stka.back() - stka[sz(stka) - 2];
			add(a[stka.back()], 0, -r, 1ll * r * stka.back());
			add(a[stka.back()], 0, 0, 1ll * l * r);
			stka.pop_back();
		}
		int space = idx - stka.back();
		stka.push_back(idx);
		add(a[idx], 0, space, -1ll * space * idx);
	};
	auto insertB = [&](int v){
		b.push_back(v);
		int idx = sz(b) - 1;
		while(sz(stkb) > 1 && b[stkb.back()] <= b[idx]){
			int l = idx - stkb.back();
			int r = stkb.back() - stkb[sz(stkb) - 2];
			add(b[stkb.back()], 1, -r, 1ll * r * stkb.back());
			add(b[stkb.back()], 1, 0, 1ll * l * r);
			stkb.pop_back();
		}
		int space = idx - stkb.back();
		stkb.push_back(idx);
		add(b[idx], 1, space, -1ll * space * idx);
	};
	for(auto &[t, v] : seqs){
		if(t & 2) insertB(v);
		else insertA(v);
		if(t & 1) cout << query(sz(a), sz(b)) << "\n";
	}
}
