#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;
const int MAXT = 270000;

int n, q, a[MAXN];
vector<pi> evt[MAXN];

struct seg{
	struct node{
		pi minv;
		int lazy;
	}tree[MAXT];
	void lazydown(int p){
		for(int j=2*p; j<2*p+2; j++){
			tree[j].minv.first += tree[p].lazy;
			tree[j].lazy += tree[p].lazy;
		}
		tree[p].lazy = 0;
	}
	void init(int s = 1, int e = n, int p = 1){
		if(s == e){
			tree[p].minv = pi(0, -s);
			return;
		}
		int m = (s+e)/2;
		init(s, m, 2*p);
		init(m+1, e, 2*p+1);
		tree[p].minv = min(tree[2*p].minv, tree[2*p+1].minv);
	}
	void add(int s, int e, int v, int ps = 1, int pe = n, int p = 1){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p].minv.first += v;
			tree[p].lazy += v;
			return;
		}
		int pm = (ps+pe)/2;
		lazydown(p);
		add(s, e, v, ps, pm, 2*p);
		add(s, e, v, pm+1, pe, 2*p+1);
		tree[p].minv = min(tree[2*p].minv, tree[2*p+1].minv);
	}
	pi query(int s, int e, int ps = 1, int pe = n, int p = 1){
		if(e < ps || pe < s) return pi(1e9, -1);
		if(s <= ps && pe <= e) return tree[p].minv;
		int pm = (ps+pe)/2;
		lazydown(p);
		return min(query(s, e, ps, pm, 2*p), query(s, e, pm+1, pe, 2*p+1));
	}
}seg;

pi ans[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	scanf("%d",&q);
	for(int i=0; i<q; i++){
		int s, e; scanf("%d %d",&s,&e);
		evt[e].emplace_back(s, i);
	}
	vector<int> sl, sr;
	priority_queue<pi> pq;
	seg.init();
	for(int i=1; i<=n; i++){
		for(auto &j : evt[i]) pq.push(j);
		while(sz(sl) && a[sl.back()] > a[i]){
			int r = sl.back(); sl.pop_back();
			int l = (sz(sl) ? sl.back() : 0);
			seg.add(l + 1, r, a[r] - a[i]);
		}
		sl.push_back(i);
		while(sz(sr) && a[sr.back()] < a[i]){
			int r = sr.back(); sr.pop_back();
			int l = (sz(sr) ? sr.back() : 0);
			seg.add(l + 1, r, a[i] - a[r]);
		}
		sr.push_back(i);
		seg.add(1, i - 1, -1);
		while(sz(pq)){
			pi tp = pq.top(); 
			auto qr = seg.query(1, tp.first);
			if(qr.first == 0){
				ans[tp.second] = pi(-qr.second, i);
				pq.pop();
			}
			else break;
		}
	}
	for(int i=0; i<q; i++) printf("%d %d\n", ans[i].first, ans[i].second);
}
