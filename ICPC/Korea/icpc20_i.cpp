#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 2100005;
const int MAXT = 4200000;

struct fenw{
	lint tree[MAXT];
	int lim; 
	void init(int n){
		fill(tree, tree + MAXT, -1e18);
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void upd(int x, lint v){
		for(int i = x + lim; i; i >>= 1){
			tree[i] = max(tree[i], v);
		}
	}
	lint query(int s, int e){
		s += lim;
		e += lim;
		lint ret = -1e18;
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

struct gaps{
	int s, e; lint x;
	bool operator<(const gaps &g)const{
		return e < g.e;
	};
};

struct qry{
	int s, e; lint x;
	int idx;
	bool operator<(const qry &q)const{
		return e < q.e;
	}
}qr[MAXN];

int n, q;
lint a[2005];
lint ret[MAXN];

int main(){
	scanf("%d %d",&n,&q);
	for(int i=1; i<=n; i++){
		scanf("%lld",&a[i]);
		a[i] += a[i-1];
	}
	vector<lint> v;
	vector<gaps> gap;
	for(int i=1; i<=n; i++){
		for(int j=0; j<i; j++){
			gap.push_back({j + 1, i, a[i] - a[j]});
			v.push_back(a[i] - a[j]);
		}
	}
	sort(all(v));
	v.resize(unique(all(v)) - v.begin());
	for(int i=0; i<sz(gap); i++){
		gap[i].x = lower_bound(all(v), gap[i].x) - v.begin();
	}
	for(int i=0; i<q; i++){
		scanf("%d %d %lld",&qr[i].s,&qr[i].e,&qr[i].x);
		qr[i].idx = i;
	}
	sort(all(gap));
	sort(qr, qr + q);
	int ptr = 0;
	seg.init(sz(v));
	for(int i=0; i<q; i++){
		while(ptr < sz(gap) && gap[ptr].e <= qr[i].e){
			seg.upd(gap[ptr].x, gap[ptr].s);
			ptr++;
		}
		int pos = lower_bound(all(v), qr[i].x + 1) - v.begin();
		if(seg.query(0, pos - 1) < qr[i].s){
			ret[qr[i].idx] = 1e18;
		}
		else{
			int s = 0, e = pos - 1;
			while(s != e){
				int m = (s + e + 1) / 2;
				if(seg.query(m, pos - 1) >= qr[i].s) s = m;
				else e = m - 1;
			}
			ret[qr[i].idx] = v[s];
		}
	}
	for(int i=0; i<q; i++){
		if(ret[i] > 1e17) puts("NONE");
		else printf("%lld\n", ret[i]);
	}
}
