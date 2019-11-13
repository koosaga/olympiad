#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using lint = long long;
using pi = pair<int, int>;

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p); q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

struct tlwpdus{
	int tl, wp, dus;
	bool operator<(const tlwpdus &t)const{
		return pi(tl, wp) < pi(t.tl, t.wp);
	}
}a[MAXN];

int n, q;

int main(){
	scanf("%d %d",&n,&q);
	assert(1 <= n && n <= 100000);
	assert(1 <= q && q <= 100000);
	disj.init(n);
	for(int i=0; i<n; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		assert(0 <= s && s < e && e <= 1000000000);
		assert(0 <= x && x <= 1000000000);
		a[i] = {s, e, i};
	}
	sort(a, a + n);
	int emax = -1;
	for(int i=0; i<n; i++){
		if(emax >= a[i].tl){
			disj.uni(a[i-1].dus, a[i].dus);
		}
		emax = max(emax, a[i].wp);
	}
	while(q--){
		int l, r; scanf("%d %d",&l,&r);
		assert(1 <= l && l <= n);
		assert(1 <= r && r <= n);
		assert(l != r);
		l--, r--;
		puts(disj.find(l) == disj.find(r) ? "1": "0");
	}
}

