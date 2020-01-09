#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 305;
const int MAXK = 50000;

int mod;

int n, k;
lint dp[MAXN][MAXK];
lint rdp[MAXN][MAXK];
lint dap[MAXN];

int main(){
	cin >> n >> k >> mod;
	dp[0][0] = 1;
	for(int i=1; i<=n; i++){
		lint foo = 0;
		for(int j=0; j<MAXK; j++){
			foo += dp[i-1][j];
			if(j - i >= 0) foo += mod - dp[i-1][j-i];
			dp[i][j] = foo % mod;
		}
	}
	rdp[n][0] = 1;
	for(int i=n-1; i>=0; i--){
		lint foo = 0;
		for(int j=0; j<MAXK; j++){
			foo += rdp[i+1][j];
			if(j - i - 1 >= 0) foo += mod - rdp[i+1][j-i-1];
			rdp[i][j] = foo % mod;
		}
	}
	auto func = [&](int i, int j){
		lint tot = 0;
		for(int x = 0; x <= k; x++){
			int l = j - i + 1;
			lint inner = dp[l][x];
			int rem_inv = k - x - (j < n ? (j-i+1) : 0);
			if(i > 1) l++;
			if(j < n) l++;
			int r = j;
			if(j < n) r++;
			if(rem_inv >= 0) tot += rdp[l][rem_inv] * inner % mod;
			if(i > 1 && j < n){
				rem_inv--;
				if(rem_inv >= 0) tot += rdp[l][rem_inv] * inner % mod;
			}
		}
		return tot % mod;
	};
	for(int i=1; i<=n; i++){
		vector<lint> v;
		for(int j=1; j+i-1<=n; j++){
			if(j+i-1 == n || sz(v) <= 1){
				v.push_back(func(j, j+i-1));
			}
			else v.push_back(v.back());
		}
		for(int j=1; j+i-1<=n; j++){
			dap[j] += v[j-1];
			dap[j + i] += mod - v[j-1];
		}
	}
	for(int i=1; i<=n; i++) dap[i] = (dap[i] + dap[i-1]) % mod;
	for(int i=1; i<=n; i++) printf("%lld ", dap[i] % mod);
	cout << endl;
}
