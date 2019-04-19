#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int MAXT = 270000;
using lint = long long;

struct seg{
	int tree[MAXT], lazy[MAXT];
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
		int pm = (ps+pe)/2;
		lazydown(p);
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = min(tree[2*p], tree[2*p+1]);
	}
	int query(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return 1e9;
		if(s <= ps && pe <= e) return tree[p];
		lazydown(p);
		int pm = (ps+pe)/2;
		return min(query(s, e, ps, pm, 2*p), query(s, e, pm+1, pe, 2*p+1));
	}
}seg;

int n, q;
int a[3][MAXN], rev[3][MAXN];
int mtch[3][MAXN];

int main(){
	scanf("%d %d",&n,&q);
	for(int i=0; i<3; i++){
		for(int j=1; j<=n; j++){
			scanf("%d",&a[i][j]);
			rev[i][a[i][j]] = j;
		}
	}
	auto Upload = [&](int x, int v){
		int st = min({rev[0][x], rev[1][x], rev[2][x]});
		int ed = max({rev[0][x], rev[1][x], rev[2][x]});
		seg.add(st, ed - 1, 1, n - 1, 1, v);
	};
	for(int i=1; i<=n; i++) Upload(i, +1);
	while(q--){
		int t; scanf("%d",&t);
		if(t == 1){
			scanf("%d",&t);
			int ans = min({rev[0][t], rev[1][t], rev[2][t]});
			puts(seg.query(1, ans - 1, 1, n - 1, 1) ? "DA" : "NE");
		}
		else{
			int p, x, y; scanf("%d %d %d",&p,&x,&y);
			Upload(x, -1);
			Upload(y, -1);
			p--;
			swap(rev[p][x], rev[p][y]);
			Upload(x, +1);
			Upload(y, +1);
		}
	}
}
