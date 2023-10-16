#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 500005;
const int MAXT = 1050000;
const int inf = 2e9 + 696969;
 
struct query{
	int s, e, idx;
	bool operator<(const query &q)const{
		return pi(s, -idx) < pi(q.s, -q.idx);
	}
};
 
int n;
query a[MAXN];
vector<int> v;
 
struct bit{
	int tree[MAXN];
	void add(int x, int v){
		for(int i = x + 2; i < MAXN; i += i & -i) tree[i] += v;
	}
	int query(int x){
		int ret = 0;
		for(int i = x + 2; i; i -= i & -i) ret += tree[i];
		return ret;
	}
}seg_spot;
 
struct seg{
	pi tree[MAXT];
	int lazy[MAXT];
	void init(int n){
		fill(tree, tree + MAXT, pi(inf, inf));
	}
	void lazydown(int p){
		for(int i = 2*p; i < 2*p+2; i++){
			tree[i].first += lazy[p];
			lazy[i] += lazy[p];
		}
		lazy[p] = 0;
	}
	void upd(int pos, int ps, int pe, int p, pi v){
		if(ps == pe){
			tree[p] = v;
			return;
		}
		int pm = (ps+pe)/2;
		lazydown(p);
		if(pos <= pm) upd(pos, ps, pm, 2*p, v);
		else upd(pos, pm+1, pe, 2*p+1, v);
		tree[p] = min(tree[2*p], tree[2*p+1]);
	}
	void add(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p].first += v;
			lazy[p] += v;
			return;
		}
		int pm = (ps+pe)/2;
		lazydown(p);
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = min(tree[2*p], tree[2*p+1]);
	}
	void set(int v, pi p){
		upd(v, 0, n - 1, 1, p);
	}
	void add(int s, int e, int x){
		add(s, e, 0, n - 1, 1, x);
	}
	pi getmin(){
		return tree[1];
	}
}seg_pareto;
 
struct seg2{
	pi tree[MAXT];
	int lim;
	void init(int n){
		fill(tree, tree + MAXT, pi(inf, inf));
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void set(int v, pi p){
		v += lim;
		tree[v] = p;
		while(v > 1){
			v >>= 1;
			tree[v] = min(tree[2*v], tree[2*v+1]);
		}
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(inf, inf);
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}seg_recover;
 
int main(){
	scanf("%d",&n);
	for(int i = 0; i < n; i++){
		scanf("%d %d",&a[i].s,&a[i].e);
		v.push_back(a[i].s);
		v.push_back(a[i].e);
		a[i].idx = i + 1;
	}
	// coord comp
	sort(all(v));
	v.resize(unique(all(v)) - v.begin());
	sort(a, a + n);
	vector<int> rev(n + 1);
	for(int i = 0; i < n; i++){
		rev[a[i].idx] = i;
		a[i].s = lower_bound(all(v), a[i].s) - v.begin();
		a[i].e = lower_bound(all(v), a[i].e) - v.begin();
	}
	// initialize ds
	set<int> spot;
	set<pair<int, int>> pareto;
	auto activate = [&](int i){
		int sum = seg_spot.query(a[i].e) - seg_spot.query(a[i].s);
		seg_pareto.set(i, pi(sum, a[i].idx));
		pareto.insert(pi(a[i].e, i));
	};
	{
		for(int i = 0; i < sz(v) - 1; i++){
			seg_spot.add(i + 1, v[i+1] - v[i]);
			spot.insert(i);
		}
		seg_pareto.init(n);
		seg_recover.init(n);
		int curMin = inf;
		for(int i = n - 1; i >= 0; i--){
			seg_recover.set(i, pi(a[i].e, a[i].idx));
			if(curMin > a[i].e){
				curMin = a[i].e;
				activate(i);
			}
		}
	}
	for(int i = 0; i < n; i++){
		int pos = seg_pareto.getmin().second;
		printf("%d ", pos);
		pos = rev[pos];
		// Remove empty spots
		{
			auto it = spot.lower_bound(a[pos].s);
			while(it != spot.end() && *it < a[pos].e){
				int j = *it; 
				// intersects if a[i].s <= j < a[i].e
				auto it1 = pareto.lower_bound(pi(j + 1, -1)); // first index where j < a[i].e
				int it2 = lower_bound(a, a + n, (query){j + 1, 0, inf}) - a;
				if(it1 != pareto.end() && it1->second <= it2 - 1){
					seg_pareto.add(it1->second, it2 - 1, -(v[j+1] - v[j]));
				}
				seg_spot.add(j + 1, -(v[j+1] - v[j]));
				it = spot.erase(it);
			}
		}
		// Remove used interval
		{
			seg_pareto.set(pos, pi(inf, inf));
			seg_recover.set(pos, pi(inf, inf));
			pareto.erase(pi(a[pos].e, pos));
			auto it = pareto.lower_bound(pi(a[pos].e, pos));
			int prev_idx = (it == pareto.begin() ? -1 : prev(it)->second);
			int next_idx = (it == pareto.end() ? (inf - 420) : it->first);
			while(true){
				// minimum R, minimum index in case of tie 
				auto qr = seg_recover.query(prev_idx + 1, n - 1);
				if(qr.first >= next_idx) break;
				qr.second = rev[qr.second];
				activate(qr.second);
				prev_idx = qr.second;
			}
		}
	}
}
