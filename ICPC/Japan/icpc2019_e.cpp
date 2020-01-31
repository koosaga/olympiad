#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 5005;
const int mod = 1e9 + 7;

int n, m, a[MAXN];
int dp[MAXN], ndp[MAXN];

int main(){
	scanf("%d %d",&n,&m);
	vector<int> lds;
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		auto l = lower_bound(all(lds), -a[i]);
		if(l != lds.end()) *l = -a[i];
		else lds.push_back(-a[i]);
	}
	if(sz(lds) > 2){
		puts("0");
		return 0;
	}
	vector<int> bp = {0};
	int cur_max = 0;
	for(int i=1; i<=n; i++){
		cur_max = max(cur_max, a[i]);
		if(cur_max == i){
			bp.push_back(i);
		}
	}
	dp[0] = 1;
	for(int i=1; i<sz(bp); i++){
		int L = 0, R = 0;
		for(int j=bp[i-1]+1; j<=bp[i]; j++){
			if(a[j] >= j) L++;
			else R++;
		}
		memset(ndp, 0, sizeof(ndp));
			for(int k=n; k >= 0; k--){
				if(k >= L) ndp[k] = (ndp[k] + dp[k - L]) % mod;
				if(k >= R) ndp[k] = (ndp[k] + dp[k - R]) % mod;
			}
			memcpy(dp, ndp, sizeof(dp));
	}
	lint ans = 0;
	for(int i=0; i<=n; i++){
		if(max(n - i, i) <= m) ans += dp[i];
	}
	cout << ans % mod << endl;
}
