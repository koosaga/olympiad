#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;
const int MAXT = 270000;

struct seg{
	lint tree[MAXT];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		memset(tree, 0x3f, sizeof(tree));
	}
	void add(int x, lint v){
		x += lim;
		tree[x] = min(tree[x], v);
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
}seg1, seg2;

int n, l;
pi a[MAXN];
lint c[MAXN], psum[MAXN];

int main(){
	scanf("%d %d",&n,&l);
	for(int i=1; i<=n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
		if(a[i].first >= l){
			puts("1");
			return 0;
		}
		a[i].second = min(a[i].second, a[i].first);
	}
	for(int i=1; i<=n; i++){
		int x; scanf("%d",&x); 
		c[i] = c[i-1] + x;
	}
	sort(a+1, a+n+1, [&](const pi &a, const pi &b){
		return a.first - a.second > b.first - b.second;
	});
	seg1.init(n);
	seg2.init(n);
	for(int i=1; i<=n; i++){
		psum[i] = psum[i-1] + a[i].first - a[i].second;
		seg1.add(i, psum[i] - c[i]);
		seg2.add(i, psum[i] - c[i-1]);
	}
	int dap = 1e9;
	for(int i=1; i<=n; i++){
		bool fuck = 0;
		int ret = 1e9;
		if(psum[i-1] + a[i].first >= l){
			int j = lower_bound(psum + 1, psum + n + 1, l - a[i].first) - psum;
			ret = j;
		}
		else{
			int j = lower_bound(psum + 1, psum + n + 1, l - a[i].first + (a[i].first - a[i].second)) - psum;
			assert(j > i);
			if(j <= n) ret = j;
		}
		if(seg1.query(1, min(i-1, ret)) <= 0) fuck = true;
		if(seg2.query(i + 1, min(n, ret)) <= a[i].first - a[i].second) fuck = true;

		if(ret > i) ret--;
		if(!fuck) dap = min(dap, ret + 1);
	}
	if(dap > 1e8) dap = -1;
	cout << dap << endl;
}
