#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;

int n, k, a[500005], b[500005];
char buf[3];
int dp[500005], trk[500005];

struct seg{
	pi tree[2100000];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 2100000, pi(-1e9, -1e9));
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
}seg1, seg2, seg3;

int main(){
	scanf("%d %d",&n,&k);
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
	}
	seg1.init(1000000);
	seg2.init(1000000);
	seg3.init(1000000);
	for(int i=1; i<=k; i++){
		scanf("%s", buf);
		if(*buf == '<') b[i] = 1;
		if(*buf == '>') b[i] = -1;
	}
	for(int i=k+1; i<=n; i++){
		b[i] = b[i-k];
	}
	for(int i=0; i<n; i++){
		dp[i] = 1;
		auto t1 = seg3.query(1, a[i] - 1);
		auto t2 = seg2.query(a[i], a[i]);
		auto t3 = seg1.query(a[i] + 1, 1000000);
		tie(dp[i], trk[i]) = max({t1, t2, t3});
		dp[i] = max(dp[i], 0);
		dp[i]++;
		if(b[dp[i]] == -1) seg1.add(a[i], pi(dp[i], i));
		if(b[dp[i]] == 0) seg2.add(a[i], pi(dp[i], i));
		if(b[dp[i]] == 1) seg3.add(a[i], pi(dp[i], i));
	}
	int k = max_element(dp, dp + n) - dp;
	int ans = dp[k];
	printf("%d\n", ans);
	vector<int> ret;
	for(int i=0; i<ans; i++){
		ret.push_back(a[k]);
		k = trk[k];
	}
	reverse(ret.begin(), ret.end());
	for(auto &i : ret) printf("%d ", i);
}
