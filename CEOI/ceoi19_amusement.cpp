#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 18;
const int mod = 998244353;
#define has(msk, v) (((msk) >> (v)) & 1)

int n, m, adj[MAXN][MAXN];
int dp[1 << MAXN];
int cnt[1 << MAXN], sgn[1 << MAXN];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		s--, e--;
		adj[s][e] = 1;
	}
	sgn[0] = -1;
	for(int i=1; i<(1<<n); i++){
		cnt[i] = 1;
		sgn[i] = -sgn[i - (i & -i)];
		for(int j=0; j<n; j++){
			for(int k=0; k<n; k++){
				if(has(i, j) && has(i, k) && adj[j][k]) cnt[i] = 0;
			}
		}
	}
	dp[0] = 1;
	for(int i=1; i<(1<<n); i++){
		for(int j=i; j>0; j=(j-1)&i){
			if(cnt[j]){
				if(sgn[j] > 0) dp[i] += dp[i ^ j];
				else dp[i] += mod - dp[i ^ j];
				if(dp[i] >= mod) dp[i] -= mod;
			}
		}
	}
	lint coeff = 1ll * m * (mod + 1) / 2;
	coeff %= mod;
	cout << dp[(1 << n) - 1] * coeff % mod << endl;
}
