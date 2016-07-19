#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
 
int n, q;
int x[200005], d[200005], l[200005];
 
struct seg{
	lint tree[530000], lazy[530000];
	void init(int s, int e, int p){
		if(s == e){
			tree[p] = s;
			return;
		}
		int m = (s+e)/2;
		init(s, m, 2*p);
		init(m+1, e, 2*p+1);
		tree[p] = max(tree[2*p], tree[2*p+1]);
	}
	void lazydown(int p){
		tree[2*p] += lazy[p];
		tree[2*p+1] += lazy[p];
		lazy[2*p] += lazy[p];
		lazy[2*p+1] += lazy[p];
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
		tree[p] = max(tree[2*p], tree[2*p+1]);
	}
	int lbnd(int p, int s, int e, lint v){
		if(s == e){
			if(tree[p] >= v) return s;
			return s+1;
		}
		lazydown(p);
		int m = (s+e)/2;
		if(tree[2*p] < v) return lbnd(2*p+1, m+1, e, v);
		return lbnd(2*p, s, m, v);
	}
	lint get(int pos, int s, int e, int p){
		if(s == e) return tree[p];
		lazydown(p);
		int m = (s+e)/2;
		if(pos <= m) return get(pos, s, m, 2*p);
		return get(pos, m+1, e, 2*p+1);
	}
}segx, segy;
 
int main(){
	scanf("%d %d",&n,&q);
	for(int i=q-1; i>=0; i--){
		scanf("%d %d %d",&x[i],&d[i],&l[i]);
	}
	segx.init(1, n, 1);
	segy.init(1, n, 1);
	for(int j=0; j<q; j++){
		if(d[j] == 1){
			int p = segx.lbnd(1, 1, n, x[j] + 1) - 1;
			segy.add(1, p, 1, n, 1, -2 * l[j]);
		}
		else{
			int p = segy.lbnd(1, 1, n, x[j] + 1);
			segx.add(p, n, 1, n, 1, 2 * l[j]);
		}
	}
	for(int i=1; i<=n; i++){
		lint dx = abs(segy.get(i, 1, n, 1) - i) + abs(segx.get(i, 1, n, 1) - i);
		printf("%lld\n", dx / 2);
	}
}