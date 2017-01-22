#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, a[55];
int dp[55][55][55][55];

int f(int s, int e, int c1, int c2){
	if(c1 > c2) return -1e9;
	if(~dp[s][e][c1][c2]) return dp[s][e][c1][c2];
	int ret = 0;
	for(int i=s+1; i<e; i++){
		if(c1 <= a[i]){
			ret = max(ret, f(i, e, a[i], c2) + 1);
		}
		if(a[i] <= c2){
			ret = max(ret, f(s, i, c1, a[i]) + 1);
		}
	}
	for(int i=s+1; i<e; i++){
		for(int j=i+1; j<e; j++){
			if(c1 <= a[j]){
				ret = max(ret, f(i, j, a[j], c2) + 1);
			}
			if(a[i] <= c2){
				ret = max(ret, f(i, j, c1, a[i]) + 1);
			}
			if(c1 <= a[j] && a[i] <= c2){
				ret = max(ret, f(i, j, a[j], a[i]) + 2);
			}
		}
	}
	return dp[s][e][c1][c2] = ret;
}

int main(){
	freopen("subrev.in", "r", stdin);
	freopen("subrev.out", "w", stdout);
	cin >> n;
	for(int i=1; i<=n; i++) cin >> a[i];
	memset(dp, -1, sizeof(dp));
	cout << f(0, n+1, 0, 50);
}

