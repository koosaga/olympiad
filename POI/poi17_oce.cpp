#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
const int MAXT = 2100000;
const int mod = 998244353;
using pi = pair<int, int>;
using lint = long long;

int n, q, a[MAXN];

pi operator+(pi a, pi b){
	if(a > b) swap(a, b);
	if(a.first == b.first) a.second += b.second;
	return a;
}

struct seg{
	pi tree[MAXT];
	int lazy[MAXT];
	void lazydown(int p){
		for(int j=2*p; j<2*p+2; j++){
			tree[j].first += lazy[p];
			lazy[j] += lazy[p];
		}
		lazy[p] = 0;
	}
	void init(int s = 1, int e = n - 1, int p = 1){
		if(s == e){
			tree[p] = pi(0, 1);
			return;
		}
		int m = (s+e)/2;
		init(s, m, 2*p);
		init(m + 1, e, 2*p+1);
		tree[p] = tree[2*p] + tree[2*p+1];
	}
	void upd(int s, int e, int v, int ps = 1, int pe = n - 1, int p = 1){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p].first += v;
			lazy[p] += v;
			return;
		}
		int pm = (ps+pe)/2;
		lazydown(p);
		upd(s, e, v, ps, pm, 2*p);
		upd(s, e, v, pm+1, pe, 2*p+1);
		tree[p] = tree[2*p] + tree[2*p+1];
	}
}seg;

void upd(int x, int v){
	if(a[x] > a[x + 1]) seg.upd(a[x + 1], a[x] - 1, v);
}

int query(){
	auto ans = seg.tree[1];
	if(ans.first == 0) return ans.second + 1;
	return 1;
}

int main(){
	scanf("%d %d",&n,&q);
	if(n == 1){
		while(q--) puts("1");
		return 0;
	}
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	seg.init();
	for(int i=1; i<n; i++) upd(i, 1);
	printf("%d\n", query());
	while(--q){
		int x, y; scanf("%d %d",&x,&y);
		int v = a[x], u = a[y];
		if(x > 1) upd(x - 1, -1);
		if(x < n) upd(x, -1);
		a[x] = u;
		if(x > 1) upd(x - 1, 1);
		if(x < n) upd(x, 1);	
		if(y > 1) upd(y - 1, -1);
		if(y < n) upd(y, -1);
		a[y] = v;
		if(y > 1) upd(y - 1, 1);
		if(y < n) upd(y, 1);
		printf("%d\n", query());
	}
}
