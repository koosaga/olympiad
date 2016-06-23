#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

struct seg{
	lint tree[33000], lim = 16384;
	void init(lint *dp){
		memset(tree, 0x3f, sizeof(tree));
		for(int i=0; i<=10000; i++){
			tree[i + lim] = dp[i];
		}
		for(int i=lim-1; i; i--){
			tree[i] = min(tree[2*i], tree[2*i+1]);
		}
	}
	lint query(int s, int e){
		s += lim;
		e += lim;
		lint ret = 1e18;
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1; e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}seg;

int k, e, n;
vector<pi> foods[505];
lint dp[10005];

int main(){
	memset(dp, 0x3f, sizeof(dp));
	dp[0] = 0;
	cin >> k >> e >> n;
	for(int i=0; i<n; i++){
		int x, f, c;
		cin >> x >> f >> c;
		foods[x].push_back({f, c});
	}
	for(int i=1; i<=e; i++){
		for(int j=0; j<=k; j++){
			dp[j] += j * j;
		}
		seg.init(dp);
		int tmp = k;
		for(auto &k : foods[i]){
			for(int j=0; j<=tmp; j++){
				dp[j] -= 1ll * j * k.second;
			}
			seg.init(dp);
			for(int j=0; j<=tmp; j++){
				dp[j] += 1ll * j * k.second;
			}
			for(int j=0; j<=tmp; j++){
				dp[j] = min(dp[j], seg.query(max(j - k.first, 0), j-1) + 1ll * j * k.second);
			}
		}
	}
	cout << dp[k];
}
