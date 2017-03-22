#include <bits/stdc++.h>
typedef long long lint;
typedef long double llf;
using namespace std;
typedef pair<int, int> pi;

int n, k;
int a[20][20];
int dp[20][20];

int solve(int msk, int k){
	int arr[20][20] = {};
	int p = 0;
	for(int i=1; i<=n; i++){
		int cur = 0;
		p = 0;
		for(int j=0; j<n; j++){
			cur += a[i][j];
			if((msk >> j) % 2 == 1|| j == n-1){
				arr[i][p++] = cur;
				cur = 0;
			}
		}
	}
	for(int i=0; i<p; i++){
		for(int j=1; j<=n; j++){
			arr[j][i] += arr[j-1][i];
		}
	}
	auto cost = [&](int s, int e){
		int ret = 0;
		for(int i=0; i<p; i++){
			ret = max(ret, arr[e][i] - arr[s-1][i]);
		}
		return ret;
	};
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;
	k++;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=k; j++){
			for(int l=0; l<=i; l++){
				dp[i][j] = min(dp[i][j], max(dp[l][j-1],cost(l+1, i)));
			}
		}
	}
	return dp[n][k];
}

int main(){
	cin >> n >> k;
	for(int i=1; i<=n; i++){
		for(int j=0; j<n; j++){
			cin >> a[i][j];
		}
	}
	int ret = 1e9;
	for(int i=0; i<(1<<(n-1)); i++){
		int cnt = 0;
		for(int j=0; j<n-1; j++){
			if((i >> j) & 1) cnt++;
		}
		if(cnt <= k) ret = min(ret, solve(i, min(n-1, k - cnt)));
	}
	cout << ret;
}

