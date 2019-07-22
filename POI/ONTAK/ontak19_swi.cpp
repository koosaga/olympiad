#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;

int n, q;

struct disj{
	int pa[MAXN], cmp;
	void init(int n){
		iota(pa, pa + n + 1, 0);
		cmp = n;
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p); q = find(q);
		if(p == q) return 0;
		pa[q] = p; cmp--; return 1;
	}
}disj[20];

void solve(int s, int e, int x){
	if(disj[x].uni(s, e)){
		if(x > 0) solve(s, e, x - 1);
		if(x > 0) solve(s + (1<<(x-1)), e + (1<<(x-1)), x - 1);
	}
}

int lg[MAXN];

int main(){
	scanf("%d %d",&n,&q);
	for(int i=1; i<=n; i++){
		lg[i] = lg[i-1];
		while((2 << lg[i]) <= i) lg[i]++;
	}
	for(int i=0; i<20; i++) disj[i].init(n);
	for(int i=1; i<=q; i++){
		int s, e, x; scanf("%d %d %d",&s,&e,&x);
		int p = disj[0].cmp;
		s = (s + p) % n + 1;
		e = (e + 1ll * p * i) % n + 1;
		x = (x % (n - max(s, e) + 1)) + 1;
		int l = lg[x];
		solve(s, e, l);
		solve(s + x - (1 << l), e + x - (1 << l), l);
		printf("%d\n", disj[0].cmp);
	}
}
