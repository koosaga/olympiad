#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXT = 270000;

struct seg{
	pi tree[MAXT];
	int lazy[MAXT];
	void init(int s, int e, int p){
		if(s == e){
			tree[p] = pi(-1e9, s);
			return;
		}
		int m = (s+e)/2;
		init(s, m, 2*p);
		init(m+1, e, 2*p+1);
		tree[p] = min(tree[2*p], tree[2*p+1]);
	}
	void lazydown(int p){
		for(int i = 2*p; i < 2*p+2; i++){
			tree[i].first += lazy[p];
			lazy[i] += lazy[p];
		}
		lazy[p] = 0;
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
	void upd(int pos, int ps, int pe, int p, int v){
		if(ps == pe){
			tree[p].first = v;
			return;
		}
		int pm = (ps+pe)/2;
		lazydown(p);
		if(pos <= pm) upd(pos, ps, pm, 2*p, v);
		else upd(pos, pm+1, pe, 2*p+1, v);
		tree[p] = min(tree[2*p], tree[2*p+1]);
	}
}seg;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<pi> a(n);
	for(int i = 0; i < n; i++){
		cin >> a[i].first;
		a[i].second = i;
	}
	vector<pi> sa = a;
	sort(all(sa));
	seg.init(0, n-1, 1);
	for(int i = n - 1; i >= 0; i--){
		int js = lower_bound(all(sa), pi(a[i].first - k, -1)) - sa.begin();
		int je = lower_bound(all(sa), pi(a[i].first + k + 1, -1)) - sa.begin();
		seg.add(0, js-1, 0, n-1, 1, +1);
		seg.add(je, n-1, 0, n-1, 1, +1);
		int pos = lower_bound(all(sa), pi(a[i].first, a[i].second)) - sa.begin();
		seg.upd(pos, 0, n-1, 1, 0);
	}
	for(int i = 0; i < n; i++){
		int j = seg.tree[1].second;
		cout << sa[j].first << "\n";
		seg.upd(j, 0, n-1, 1, 1e9);
		int js = lower_bound(all(sa), pi(sa[j].first - k, -1)) - sa.begin();
		int je = lower_bound(all(sa), pi(sa[j].first + k + 1, -1)) - sa.begin();
		seg.add(0, js-1, 0, n-1, 1, -1);
		seg.add(je, n-1, 0, n-1, 1, -1);
	}
}

