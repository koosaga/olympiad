#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
int mod;
const int MAXN = 200005;
const int MAXT = 530000;

int conv[256];
char buf[MAXN];

vector<int> get_seq(int n){
	scanf("%s", buf);
	vector<int> ret;
	for(int i = 0; i < n; i++){
		ret.push_back(conv[buf[i]]);
	}
	return ret;
}

int triadd(int x, int y){
	int ret = 0, pwr = 1;
	for(int i = 0; i < 3; i++){
		int qq = (x%3 + y%3) * 2;
		ret += (qq % 3) * pwr;
		pwr *= 3;
		x /= 3; y /= 3;
	}
	return ret;
}

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

mint pwr[MAXT], sum[MAXT];

struct seg{
	struct node{
		int lazy;
		int sz;
		mint sum;
		node(){
			lazy = -1;
			sz = 0;
			sum = mint(0);
		}
		node(int x){
			lazy = -1;
			sz = 1;
			sum = mint(x);
		}
		node operator+(const node &n)const{
			node ret;
			ret.sz = sz + n.sz;
			ret.sum = sum + pwr[sz] * n.sum;
			return ret;
		}
	}tree[MAXT];
	void init(int s, int e, vector<int> &v, int p = 1){
		if(s == e){
			tree[p] = node(v[s]);
			return;
		}
		int m = (s+e)/2;
		init(s, m, v, 2*p);
		init(m+1, e, v, 2*p+1);
		tree[p] = tree[2*p] + tree[2*p+1];
	}
	void applazy(node &nd, int x){
		nd.lazy = x;
		nd.sum = mint(x) * sum[nd.sz];
	}
	void lazydown(int p){
		if(tree[p].lazy != -1){
			applazy(tree[2*p], tree[p].lazy);
			applazy(tree[2*p+1], tree[p].lazy);
		}
		tree[p].lazy = -1;
	}
	int get(){ return tree[1].sum; };
	void set(int s, int e, int ps, int pe, int v, int p = 1){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			applazy(tree[p], v);
			return;
		}
		lazydown(p);
		int pm = (ps+pe)/2;
		set(s, e, ps, pm, v, 2*p);
		set(s, e, pm+1, pe, v, 2*p+1);
		tree[p] = tree[2*p] + tree[2*p+1];
	}

}seg;

int main(){
	int chk[27] = {};
	chk[1] = chk[3] = chk[9] = 1;
	for(int i = 0; i < 10000; i++){
		for(int j = 0; j < 27; j++){
			for(int k = 0; k < 27; k++){
				if(!chk[j] || !chk[k]) continue;
				chk[triadd(j, k)] = 1;
			}
		}
	}
	conv['J'] = 0;
	conv['O'] = 1;
	conv['I'] = 2;
	int n; scanf("%d",&n);
	vector<int> seq[3];
	for(int i = 0; i < 3; i++){
		seq[i] = get_seq(n);
	}
	vector<vector<int>> v;
	for(int i = 0; i< 27; i++){
		if(!chk[i]) continue;
		vector<int> newseq(n);
		int cur = i;
		for(int j = 0; j < 3; j++){
			for(int k = 0; k < n; k++){
				newseq[k] += seq[j][k] * (cur % 3);
			}
			cur /= 3;
		}
		for(auto &q : newseq) q %= 3;
		reverse(all(newseq));
		v.push_back(newseq);
	}
	int q; scanf("%d",&q); 
	vector<int> qr = get_seq(n);
	vector<tuple<int, int, int>> mutate(q);
	for(auto &[x, y, z] : mutate){
		scanf("%d %d",&x,&y);
		x--; y--;
		z = get_seq(1)[0];
	}
	vector<int> ans(q + 1);
	fill(all(ans), 1);

	for(auto &MOD : {int(1e9) + 696969, 993244853}){
		mod = MOD;
		pwr[0] = 1;
		for(int i = 1; i < MAXT; i++){
			pwr[i] = pwr[i-1] * mint(257);
			sum[i] = sum[i-1] + pwr[i-1];
		}
		vector<lint> vhash;
		for(auto &i : v){
			mint val = 0;
			for(auto &j : i){
				val = val * mint(257) + mint(j);
			}
			vhash.push_back(val);
		}
		sort(all(vhash));
		seg.init(0, n - 1, qr);
		int idx = 0;
		auto Do = [&](){
			if(!binary_search(all(vhash), seg.get())) ans[idx] = 0;
			idx++;
		};
		Do();
		for(auto &[x, y, z] : mutate){
			seg.set(x, y, 0, n - 1, z);
			Do();
		}
	}
	for(auto &i : ans){
		puts(i ? "Yes" : "No");
	}
}
