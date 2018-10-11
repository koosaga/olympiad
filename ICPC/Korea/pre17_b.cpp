#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 1005;
const int mod = 1e9 + 7;

int dp[MAXN][MAXN];
vector<pi> gph[MAXN];

bool cmp(pi a, pi b){
	return 1ll * a.first * b.second < 1ll * b.first * a.second;
}

int gcd(int x, int y){
	return y? gcd(y, x%y) : x;
}

int main(){
	int n, m; cin >> n >> m;
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[e].push_back(pi(x, s));
	}
	for(int i=1; i<=n; i++){
		memset(dp[i], 0x3f, sizeof(dp[i]));
		for(int j=0; j<n; j++){
			for(auto &k : gph[j]){
				dp[i][j] = min(dp[i][j], dp[i-1][k.second] + k.first);
			}
		}
	}
	pi ret(1e9, 1);
	for(int i=0; i<n; i++){
		pi tmp(0, 1);
		for(int j=0; j<n; j++){
			tmp = max(tmp, pi(dp[n][i] - dp[j][i], n - j), cmp);
		}
		ret = min(ret, tmp, cmp);
	}
	if(ret.first > 987654321){
		puts("0 0");
		return 0;
	}
	int g = gcd(ret.first, ret.second);
	ret.first /= g;
	ret.second /= g;
	cout << ret.first << " " << ret.second;
}
