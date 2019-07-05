#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
const int MAXT = 2100000;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<int, int>;

struct pnt{
	int x, y;
	lint c;
	bool operator<(const pnt &p)const{
		return pi(x, y) < pi(p.x, p.y);
	}
};

struct seg{
	lint lazy[MAXT], tree[MAXT];
	void lazydown(int p){
		lazy[2*p] += lazy[p];
		lazy[2*p+1] += lazy[p];
		tree[2*p] += lazy[p];
		tree[2*p+1] += lazy[p];
		lazy[p] = 0;
		tree[2*p] = max(tree[2*p], tree[p]);
		tree[2*p+1] = max(tree[2*p+1], tree[p]);
		tree[p] = 0;
	}
	void add(int s, int e, int ps, int pe, int p, lint v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			lazy[p] += v;
			tree[p] += v;
			return;
		}
		int pm = (ps + pe) / 2;
		lazydown(p);
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm + 1, pe, 2*p + 1, v);
	}
	void upperize(int s, int e, int ps, int pe, int p, lint v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p] = max(tree[p], v);
			return;
		}
		int pm = (ps + pe) / 2;
		lazydown(p);
		upperize(s, e, ps, pm, 2*p, v);
		upperize(s, e, pm+1, pe, 2*p+1, v);
	}
	lint query(int pos, int s, int e, int p){
		if(s == e) return tree[p];
		int m = (s + e) / 2;
		lazydown(p);
		if(pos <= m) return query(pos, s, m, 2*p);
		return query(pos, m+1, e, 2*p+1);
	}
}seg;

int n, m;
lint a[MAXN], s[MAXN], p[MAXN];
lint b[MAXN], t[MAXN], q[MAXN];
int da[MAXN], db[MAXN];
lint dp[MAXN];
vector<pnt> v, w;

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		scanf("%lld %lld %lld",&a[i],&s[i],&p[i]);
		a[i] += a[i-1];
	}
	for(int i=1; i<=m; i++){
		scanf("%lld %lld %lld",&b[i],&t[i],&q[i]);
		b[i] += b[i-1];
	}
	lint ret = 0;
	v.push_back({0, 0, 0});
	for(int i=1; i<=n; i++){
		da[i] = upper_bound(b, b + m + 1, s[i] - a[i]) - b;
		if(da[i] > m){
			ret += p[i];
			continue;
		}
		if(da[i] > 0){
			if(p[i] > 0) v.push_back({i, da[i], p[i]});
			else w.push_back({i, da[i], -p[i]}), ret += p[i];
		}
	}
	for(int i=1; i<=m; i++){
		db[i] = upper_bound(a, a + n + 1, t[i] - b[i]) - a;
		if(db[i] > n){
			ret += q[i];
			continue;
		}
		if(db[i] > 0){
			if(q[i] > 0) w.push_back({db[i], i, q[i]});
			else v.push_back({db[i], i, -q[i]}), ret += q[i];
		}
	}
	sort(v.begin(), v.end());
	sort(w.begin(), w.end());
	v.push_back({n + 1, m + 1, 0});
	int pw = 0;
	for(int i=1; i<v.size(); ){
		int e = i;
		while(e < v.size() && v[e].x == v[i].x) e++;
		for(int j = i; j < e; j++){
			seg.add(0, v[j].y - 1, 0, m, 1, v[j].c);
		}
		while(pw < w.size() && w[pw].x <= v[i].x){
			seg.add(w[pw].y, m, 0, m, 1, w[pw].c);
			pw++;
		}
		if(v[i].x <= n){
			for(int j = i; j < e; j++){
				dp[j] = seg.query(v[j].y - 1, 0, m, 1);
			}
			for(int j = i; j < e; j++){
				seg.upperize(v[j].y - 1, m, 0, m, 1, dp[j]);
			}
		}
		i = e;
	}
	lint dap = -1e18;
	for(int i=0; i<=m; i++) dap = max(dap, seg.query(i, 0, m, 1));
	cout << ret + dap << endl;
}
