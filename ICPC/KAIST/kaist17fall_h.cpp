#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct seg{
	lint tree[2100000];
	int lim;
	void init(int n){
		fill(tree, tree + 2100000, 1e18);
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void add(int x, lint v){
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	lint query(int s, int e){
		s += lim;
		e += lim;
		lint ret = 1e18;
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}seg;

int n;
lint a[1000005], b[1000005];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%lld", &a[i]);
		a[i+n] = a[i];
	}
	for(int i=1; i<=n; i++){
		scanf("%lld", &b[i]);
		b[i+n] = b[i];
	}
	for(int i=1; i<=2*n; i++){
		b[i] += b[i-1];
		a[i] += a[i-1];
		seg.add(i, a[i] - b[i]);
	}
	int ret = 0;
	for(int i=1; i<=n; i++){
		if(a[i-1] - b[i-1] > seg.query(i, i+n-1)) continue;
		ret++;
	}
	cout <<ret;
}