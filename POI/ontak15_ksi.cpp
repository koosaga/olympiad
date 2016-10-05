#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

int n, a[500005];

struct seg{
	int lim;
	int tree[4200000];
	void init(){
		lim = (1<<21);
		for(int i=1; i<2*lim; i++){
			tree[i] = 1;
		}
	}
	void update(int x){
		x += lim;
		tree[x]++;
		while(x > 1){
			x >>= 1;
			tree[x] = 1ll * tree[2*x] * tree[2*x+1] % mod;
		}
	}
	lint query(int s, int e){
		s += lim;
		e += lim;
		lint ret = 1;
		while(s < e){
			if(s%2 == 1) ret = (ret * tree[s++]) % mod;
			if(e%2 == 0) ret = (ret * tree[e--]) % mod;
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = (ret * tree[s]) % mod;
		return ret;
	}
}seg;

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
	}
	seg.init();
	int dap = 0, mx = -1;
	for(int i=0; i<n; i++){
		seg.update(a[i]);
		mx = max(mx, a[i]);
		if(mx == a[i]) continue;
		dap += seg.query(0, a[i] - 1);
		dap %= mod;
	}
	cout << dap;
}
