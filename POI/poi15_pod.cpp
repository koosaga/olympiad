#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)((v).size()))
const int MAXN = 1000005;
const int MAXT = 2100000;

int n, m, a[MAXN];

struct seg{
	pi tree[MAXT];
	int lazy[MAXT];
	void lazydown(int p){
		for(int j = 2*p; j < 2*p+2; j++){
			tree[j].first += lazy[p];
			lazy[j] += lazy[p];
		}
		lazy[p] = 0;
	}
	pi merge(pi x, pi y){
		if(x < y) swap(x, y);
		if(x.first == y.first) x.second += y.second;
		return x;
	}
	void init(int s, int e, int p){
		if(s == e) tree[p] = pi(0, 1);
		else{
			int m = (s+e)/2;
			init(s, m, 2*p); init(m+1, e, 2*p+1);
			tree[p] = merge(tree[2*p], tree[2*p+1]);
		}
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
		tree[p] = merge(tree[2*p], tree[2*p+1]);
	}
	pi query(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return pi(0, 0);
		if(s <= ps && pe <= e) return tree[p];
		int pm = (ps+pe)/2;
		lazydown(p);
		return merge(query(s, e, ps, pm, 2*p), query(s, e, pm+1, pe, 2*p+1));
	}
	pi left_search(int pos, int ps, int pe, int p){
		if(ps == pe) return pi(tree[p].first, ps);
		lazydown(p);
		int pm = (ps + pe) / 2;
		if(ps >= pos){
			if(tree[p].first != m) return pi(-1, 1e9);
			if(tree[2*p].first == m) return left_search(pos, ps, pm, 2*p);
			return left_search(pos, pm + 1, pe, 2*p+1);
		}
		if(pm >= pos){
			auto x = left_search(pos, ps, pm, 2*p);
			if(x.first == m) return x;
		}
		return left_search(pos, pm + 1, pe, 2*p + 1);
	}
	pi right_search(int pos, int ps, int pe, int p){
		if(ps == pe) return pi(tree[p].first, ps);
		lazydown(p);
		int pm = (ps + pe) / 2;
		if(pe <= pos){
			if(tree[p].first != m) return pi(-1, 1e9);
			if(tree[2*p+1].first == m) return right_search(pos, pm+1, pe, 2*p+1);
			else return right_search(pos, ps, pm, 2*p);
		}
		if(pm < pos){
			auto x = right_search(pos, pm + 1, pe, 2 * p + 1);
			if(x.first == m) return x;
		}
		return right_search(pos, ps, pm, 2 * p);
	}
}seg;

struct event{
	int s, e, x;
};

vector<int> intv[MAXN];
vector<event> evt[MAXN];

void add_rect(int sx, int ex, int sy, int ey){
	ex = min(ex, n - 2);
	ey = min(ey, n - 2);
	if(sx <= ex && sy <= ey){
		evt[sx].push_back({sy, ey, +1});
		if(ex + 1 <= ey) evt[ex + 1].push_back({sy, ey, -1});
	}
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
		intv[a[i]].push_back(i);
	}
	if(count(a, a + n, a[0]) == n){
		printf("%lld %d\n", 1ll * n * (n - 1) / 2, n % 2);
		return 0;
	}
	for(int i=1; i<=m; i++){
		assert(!intv[i].empty());
		for(int j=1; j<sz(intv[i]); j++){
			int l = intv[i][j - 1];
			int r = intv[i][j];
			add_rect(l + 1, r - 1, 0, r - 1);
		}
		add_rect(intv[i].back() + 1, n - 1, 0, n - 1);
		add_rect(0, intv[i].front() - 1, 0, intv[i].front() - 1);
		add_rect(0, intv[i].front(), intv[i].back(), n - 1);
	}
	lint tot = 0;
	int ret = 1e9;
	seg.init(0, n - 2, 1);
	for(int i=0; i<n-1; i++){
		for(auto &j : evt[i]){
			seg.add(j.s, j.e, 0, n - 2, 1, j.x);
		}
		if(seg.tree[1].first == m){
			tot += seg.tree[1].second;
			if(i <= n / 2 + 5 || i + (n - ret) < n){
				int midpos = min(n - 2, i + n / 2 - 1);
				auto quer1 = seg.right_search(midpos, 0, n - 2, 1);
				if(quer1.first == m){
					ret = min(ret, n - quer1.second + i - 1);
				}
				if(midpos + 1 <= n - 2){
					auto quer2 = seg.left_search(midpos + 1, 0, n - 2, 1);
					if(quer2.first == m) ret = min(ret, quer2.second - i + 1);
				}
			}
		}
		seg.add(i, i, 0, n - 2, 1, -69696969);
	}
	ret = 2 * ret - n;
	if(ret > 1e8) ret = -1;
	printf("%lld %d\n", tot, ret);
}

