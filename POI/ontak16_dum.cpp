#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

int n, q;

struct bit{
	lint tree[100005];
	void add(int x, lint v){
		while(x <= n){
			tree[x] += v;
			x += x & -x;
		}
	}
	lint query(int x){
		lint ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
	lint query(int s, int e){
		return query(e) - query(s-1);
	}
	void upd(int x, lint v){
		add(x, v - query(x, x));
	}
}bit1, bit2, bit3;

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		int x;
		scanf("%d",&x);
		bit1.upd(i, x);
		bit2.upd(i, 1ll * i * x);
		bit3.upd(i, 1ll * i * i * x);
	}
	scanf("%d",&q);
	while(q--){
		int t;
		scanf("%d",&t);
		if(t < 0){
			int x;
			scanf("%d",&x);
			t = -t;
			bit1.upd(t, x);
			bit2.upd(t, 1ll * t * x);
			bit3.upd(t, 1ll * t * t * x);
		}
		else{
			int s, e;
			scanf("%d %d",&s,&e);
			lint ret = 0;
			if(t == 0) ret = bit1.query(s, e);
			if(t == 1) ret = bit2.query(s, e) - (s - 1) * bit1.query(s, e);
			if(t == 2) ret = bit3.query(s, e) - (2 * s - 2) * bit2.query(s, e) 
				+ 1ll * (s - 1) * (s - 1) * bit1.query(s, e);
			printf("%lld\n", ret);
		}
	}
}
