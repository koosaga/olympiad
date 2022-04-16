#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 300005;
const int MAXT = 1050000;

int n, k, a[MAXN], b[MAXN];
char buf[MAXN];
int dp[MAXN], trk[MAXN];

struct seg{
	pi tree[MAXT];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + MAXT, pi(-1e9, -1e9));
	}
	void add(int x, pi v){
		x += lim;
		tree[x] = max(tree[x], v);
		while(x > 1){
			x >>= 1;
			tree[x] = max(tree[2*x], tree[2*x+1]);
		}
	}
	pi query(int s, int e){
		 s += lim;
		 e += lim;
		 pi ret(-1e9, -1e9);
		 while(s < e){
		 	 if(s%2 == 1) ret = max(ret, tree[s++]);
		 	 if(e%2 == 0) ret = max(ret, tree[e--]);
		 	 s >>= 1;
		 	 e >>= 1;
		 }
		 if(s == e) ret = max(ret, tree[s]);
		 return ret;
	}
}seg1, seg3;

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
	}
	seg1.init(n);
	seg3.init(n);
	scanf("%s", buf);
	for(int i=0; i<n-1; i++){
		if(buf[i] == 'U') b[i+1] = 1;
		if(buf[i] == 'D') b[i+1] = -1;
	}
	for(int i=0; i<n; i++){
		auto t1 = seg3.query(1, a[i] - 1);
		auto t3 = seg1.query(a[i] + 1, n);
		tie(dp[i], trk[i]) = max({t1, t3});
		dp[i] = max(dp[i], 0);
		dp[i]++;
		if(b[dp[i]] == -1) seg1.add(a[i], pi(dp[i], i));
		if(b[dp[i]] == 1) seg3.add(a[i], pi(dp[i], i));
	}
	int k = max_element(dp, dp + n) - dp;
	int ans = dp[k];
	printf("%d\n", ans - 1);
}

