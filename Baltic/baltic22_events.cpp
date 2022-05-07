#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 100005;
const int MAXT = 530000;

struct seg{
	pi tree[MAXT];
	int lim;
	void init(int n){
		fill(tree, tree + MAXT, pi(1e9, 1e9));
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void upd(int x, pi v){
		x += lim;
		while(x){
			tree[x] = min(tree[x], v);
			x >>= 1;
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

struct intv{
	int s, e, idx;
};

int nxt[18][MAXN];
int gau[18][MAXN];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q; cin >> n >> q;
	vector<intv> a(n);
	vector<int> v;
	for(int i = 0; i < n; i++){
		cin >> a[i].s >> a[i].e;
		a[i].idx = i+1;
		v.push_back(a[i].s);
		v.push_back(a[i].e);
	}
	sort(all(v));
	v.resize(unique(all(v)) - v.begin());
	for(int i = 0; i < n; i++){
		a[i].s = lower_bound(all(v), a[i].s) - v.begin();
		a[i].e = lower_bound(all(v), a[i].e) - v.begin();
	}
	sort(all(a), [&](const intv &a, const intv &b){
		return pi(a.s, a.e) < pi(b.s, b.e);
	});
	vector<pi> maxStart(sz(v), pi(-1e9, -1e9));
	for(int i = 0; i < sz(a); i++){
		maxStart[a[i].s] = max(maxStart[a[i].s], pi(a[i].e, i));
	}
	for(int i = 1; i < sz(maxStart); i++) maxStart[i] = max(maxStart[i], maxStart[i-1]);
	vector<int> rev(n + 1);
	seg.init(sz(v));
	for(int i = 0; i < n; i++){
		rev[a[i].idx] = i;
		seg.upd(a[i].e, pi(a[i].s, i));
		nxt[0][i] = maxStart[a[i].e].second;
		if(a[nxt[0][i]].e <= a[i].e) nxt[0][i] = i;
	}
	for(int i = 1; i < 18; i++){
		for(int j = 0; j < n; j++){
			nxt[i][j] = nxt[i-1][nxt[i-1][j]];
		}
	}
	for(int i = 0; i < n; i++){
		gau[0][i] = seg.query(a[i].s, a[i].e).second;
	}
	for(int i = 1; i < 18; i++){
		for(int j = 0; j < n; j++){
			nxt[i][j] = nxt[i-1][nxt[i-1][j]];
			gau[i][j] = gau[i-1][gau[i-1][j]];
		}
	}
	while(q--){
		int s, e; cin >> s >> e;
		s = rev[s];
		e = rev[e];
		if(s == e){
			cout << "0\n";
			continue;
		}
		if(a[s].e > a[e].e){
			cout << "impossible\n";
			continue;
		}
		if(a[s].e >= a[e].s){
			cout << "1\n";
			continue;
		}
		int ret = 0;
		for(int i = 17; i >= 0; i--){
			if(a[nxt[i][s]].e < a[e].s){
				s = nxt[i][s];
				ret += (1<<i);
			}
		}
		ret += 1;
		for(int i = 17; i >= 0; i--){
			if(a[s].e < a[gau[i][e]].s){
				e = gau[i][e];
				ret += (1 << i);
			}
		}
		if(a[s].e < a[gau[0][e]].s) ret = 1e9;
		else ret += 1;
		if(ret > n){
			cout << "impossible\n";
			continue;
		}
		else cout << ret << "\n";
	}
}
