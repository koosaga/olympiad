#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
const int MAXN = 250005;
const int MAXT = 530005;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<int, int>;

int n, q, a[MAXN];

struct seg{
	double tree[MAXT];
	double lazy[MAXT];
	void init(int s, int e, int p, int *x){
		lazy[p] = -1;
		if(s == e){
			tree[p] = x[s];
			return;
		}
		int m = (s+e)/2;
		init(s, m, 2*p, x);
		init(m+1, e, 2*p+1, x);
		tree[p] = tree[2*p] + tree[2*p+1];
	}
	void lazydown(int p, int s, int e){
		int m = (s+e)/2;
		if(lazy[p] >= -0.5){
			lazy[2*p] = lazy[p];
			tree[2*p] = (m - s + 1) * lazy[p];
			lazy[2*p+1] = lazy[p];
			tree[2*p+1] = (e - m) * lazy[p];
		}
		lazy[p] = -1;
	}
	double query(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return 0;
		if(s <= ps && pe <= e) return tree[p];
		lazydown(p, ps, pe);
		int pm = (ps+pe)/2;
		return query(s, e, ps, pm, 2*p) + query(s, e, pm+1, pe, 2*p+1);
	}
	void upd(int s, int e, int ps, int pe, int p, double v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p] = (pe - ps + 1) * v;
			lazy[p] = v;
			return;
		}
		lazydown(p, ps, pe);
		int pm = (ps+pe)/2;
		upd(s, e, ps, pm, 2*p, v);
		upd(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = tree[2*p] + tree[2*p+1];
	}
}seg;

char buf[69];
int main(){
	scanf("%d %d",&n,&q);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	seg.init(1, n, 1, a);
	while(q--){
		scanf("%s", buf);
		if(*buf == 'g'){
			int i; scanf("%d",&i);
			printf("%.10f\n", seg.query(i, i, 1, n, 1));
		}
		else{
			int s, e; scanf("%d %d",&s,&e);
			double ans = seg.query(s, e, 1, n, 1);
			seg.upd(s, e, 1, n, 1, ans / (e - s + 1));
		}
	}
}
