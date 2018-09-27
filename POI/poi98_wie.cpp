#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 2005;

int n, a[MAXN][MAXN];
int opt[MAXN / 2][MAXN / 2];
int dp[MAXN / 2][MAXN / 2];

int main(){
	cin >> n;
	auto up = [&](int s, int e){
		if(s > e) swap(s, e);
		s++; e++;
		if(e - s == 1) return;
		if(s == 1 && e == n) return;
		a[s][e]++;
		a[e][s+n]++;
		a[s+n][e+n]++;
	};
	for(int i=0; i<n-2; i++){
		int s, e, x; cin >> s >> e >> x;
		up(s, e); up(e, x); up(s, x);
	}
	for(int i=2*n; i; i--){
		for(int j=1; j<=2*n; j++){
			a[i][j] += a[i+1][j] + a[i][j-1] - a[i+1][j-1];
		}
	}
	for(int i=1; i<=2*n; i++){
		for(int j=1; j<=2*n; j++){
			a[i][j] /= 2;
		}
	}
	for(int i=1; i<=n-2; i++){
		opt[i][i + 2] = i + 1;
		dp[i][i + 2] = a[i][i+1] + a[i+1][i+2];
	}
	for(int i=3; i<n; i++){
		for(int j=1; j+i<=n; j++){
			dp[j][j+i] = 1e9;
			for(int k=opt[j][j+i-1]; k<=opt[j+1][j+i]; k++){
				if(dp[j][j+i] > a[j][k] + a[k][j+i]){
					dp[j][j+i] = a[j][k] + a[k][j+i];
					opt[j][j+i] = k;
				}
			}
		}
	}
	int ans = 1e9;
	for(int i=1; i<=n; i++){
		for(int j=i+2; j<=n; j++){
			ans = min(ans, dp[i][j] + a[j][i+n]);
		}
	}
	cout << n - 2 - ans << endl;
}
