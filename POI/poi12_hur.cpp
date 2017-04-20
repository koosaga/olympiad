#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n;
lint a[250005];
vector<pi> query;

struct seg{
	lint tree[530000], lazy[530000];
	void init(int s, int e, int p, lint *a){
		if(s == e){
			tree[p] = a[s];
			return;
		}
		int m = (s+e)/2;
		init(s, m, 2*p, a);
		init(m+1, e, 2*p+1, a);
		tree[p] = min(tree[2*p], tree[2*p+1]);
	}
	void lazydown(int p){
		lazy[2*p] += lazy[p];
		lazy[2*p+1] += lazy[p];
		tree[2*p] += lazy[p];
		tree[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
	lint query(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return 1e18;
		if(s <= ps && pe <= e) return tree[p];
		int pm = (ps+pe)/2;
		lazydown(p);
		return min(query(s, e, ps, pm, 2*p), query(s, e, pm+1, pe, 2*p+1));
	}
	void add(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p] += v;
			lazy[p] += v;
			return;
		}
		int pm = (ps+pe)/2;
		lazydown(p);
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = min(tree[2*p], tree[2*p+1]);
	}
}seg;

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%lld",&a[i]);
		a[i] += a[i-1];
	}
	seg.init(1, n, 1, a);
	for(int i=0; i<n; i++){
		int t;
		scanf("%d",&t);
		query.push_back(pi(t, i+1));
	}
	sort(query.begin(), query.end(), [&](const pi &a, const pi &b){
		return pi(a.first, -a.second) < pi(b.first, -b.second);
	});
	vector<int> ans;
	for(auto &i : query){
		if(seg.query(i.second, n, 1, n, 1) >= i.first){
			seg.add(i.second, n, 1, n, 1, -i.first);
			ans.push_back(i.second);
		}
	}
	sort(ans.begin(), ans.end());
	cout << ans.size() << endl;
	for(auto &i : ans) printf("%d ", i);
}
