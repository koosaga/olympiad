#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, t[200005], a[200005];

struct seg{
	lint tree[530000], lazy[530000];
	void lazydown(int p){
		lazy[2*p] += lazy[p];
		lazy[2*p+1] += lazy[p];
		tree[2*p] += lazy[p];
		tree[2*p+1] += lazy[p];
		lazy[p] = 0;
	}
	void add(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p] += v;
			lazy[p] += v;
			return;
		}
		lazydown(p);
		int pm = (ps+pe)/2;
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = min(tree[2*p], tree[2*p+1]);
	}
	lint query(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return 1e18;
		if(s <= ps && pe <= e) return tree[p];
		lazydown(p);
		int pm = (ps+pe)/2;
		return min(query(s, e, ps, pm, 2*p), query(s, e, pm+1, pe, 2*p+1));
	}
}seg;

int main(){
	scanf("%d",&n);
	int ans = 0;
	vector<pi> v;
	for(int i=0; i<n; i++){
		scanf("%d %d",&t[i],&a[i]);
		if(t[i] == 1 && a[i] <= 0){
			a[i] *= -1;
			t[i] = 0;
			ans++;
		}
		if(t[i] == 1){
			v.push_back(pi(a[i], i));
		}
	}
	for(int i=0; i<n; i++){
		if(t[i] == 0) seg.add(i, n-1, 0, n-1, 1, a[i]);
	}
	if(seg.tree[1] < 0){
		puts("-1");
		return 0;
	}
	sort(v.begin(), v.end(), [&](const pi &a, const pi &b){
		return pi(a.first, -a.second) < pi(b.first, -b.second);
	});
	for(auto &i : v){
		if(seg.query(i.second, n-1, 0, n-1, 1) >= i.first){
			seg.add(i.second, n-1, 0, n-1, 1, -i.first);
			ans++;
		}
	}
	printf("%d", ans);
}
