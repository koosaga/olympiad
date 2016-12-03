#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

struct seg{
	pi tree[2100000];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 2 * lim, pi(1e9, 1e9));
	}
	void update(int x, int v){
		x += lim;
		tree[x] = pi(v, x-lim);
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(1e9, 1e9);
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s/=2, e/=2;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}seg;

int n, q, a[1000005];

int main(){
	while(1){
		scanf("%d %d",&n,&q);
		if(n + q == 0) break;
		map<int, int> mp;
		seg.init(n);
		for(int i=1; i<=n; i++){
			scanf("%d",&a[i]);
			if(mp.find(a[i]) != mp.end()){
				seg.update(mp[a[i]], i);
			}
			mp[a[i]] = i;
		}
		while(q--){
			int s, e;
			scanf("%d %d",&s,&e);
			auto w = seg.query(s, e);
			if(w.first > e) puts("OK");
			else printf("%d\n", a[w.first]);
		}
		puts("");
	}
}
