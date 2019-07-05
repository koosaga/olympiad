#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using lint = long long;
using pi = pair<lint, int>;

int n, m, k;
int a[MAXN], b[MAXN], dp[MAXN];

int main(){
	cin >> n >> m >> k;
	for(int i=1; i<=n; i++){
		cin >> a[i];
		if(a[i] < k){
			puts("Impossible");
			return 0;
		}
	}
	for(int i=1; i<=m; i++) cin >> b[i];
	fill(dp + 1, dp + MAXN, -1e9);
	dp[0] = 0;
	for(int i=1; i<=m; i++){
		for(int j=MAXN-1; j>=b[i]; j--){
			dp[j] = max(dp[j-b[i]] + min(b[i], n), dp[j]);
		}
	}
	int accm = accumulate(a + 1, a + n + 1, 0);
	int ret = 1e9;
	for(int i = accm; i < MAXN; i++){
		if(dp[i] >= n * k){
			cout << i - accm << endl;
			return 0;
		}
	}
	puts("Impossible");
}
