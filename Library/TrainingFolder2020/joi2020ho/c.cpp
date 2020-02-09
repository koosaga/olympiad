#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 404;

int n, l;
pi a[MAXN];

lint dp[MAXN][MAXN][MAXN / 2][2];

lint dist(int x, int y){ return abs(a[x].first - a[y].first); }

int main(){
	cin >> n >> l;
	for(int i=1; i<=n; i++) cin >> a[i+n].first;
	for(int i=1; i<=n; i++) cin >> a[i+n].second;
	for(int i=0; i<n; i++) a[i] = pi(a[i+n+1].first - l, a[i+n+1].second);
	a[n] = pi(0, 0);
	memset(dp, 0x3f, sizeof(dp));
	dp[n][n][0][0] = dp[n][n][0][1] = 0;
	int dap = 0;
	for(int i=1; i<=n; i++){
		for(int j=0; j+i<=2*n; j++){
			for(int k=0; k<=i; k++){
				dp[j][j + i][k][0] = min(dp[j+1][j+i][k][0] + dist(j+1, j), dp[j+1][j+i][k][1] + dist(j+i, j));
				if(k > 0 && dp[j + 1][j + i][k - 1][0] + dist(j+1, j) <= a[j].second){
					dp[j][j + i][k][0] = min(dp[j][j + i][k][0], dp[j+1][j+i][k-1][0] + dist(j+1, j));
				}
				if(k > 0 && dp[j + 1][j + i][k - 1][1] + dist(j+i, j) <= a[j].second){
					dp[j][j + i][k][0] = min(dp[j][j + i][k][0], dp[j+1][j+i][k-1][1] + dist(j+i, j));
				}
				dp[j][j + i][k][1] = min(dp[j][j+i-1][k][1] + dist(j+i-1, j+i), dp[j][j+i-1][k][0] + dist(j+i, j));
				if(k > 0 && dp[j][j+i-1][k-1][0] + dist(j+i, j) <= a[j+i].second){
					dp[j][j + i][k][1] = min(dp[j][j + i][k][1], dp[j][j+i-1][k-1][0] + dist(j+i, j));
				}
				if(k > 0 && dp[j][j+i-1][k-1][1] + dist(j+i, j+i-1) <= a[j+i].second){
					dp[j][j + i][k][1] = min(dp[j][j + i][k][1], dp[j][j+i-1][k-1][1] + dist(j+i, j+i-1));
				}
				if(dp[j][j+i][k][0] <= 1e10 + 100) dap = max(dap, k);
				if(dp[j][j+i][k][1] <= 1e10 + 100) dap = max(dap, k);
			}
		}
	}
	cout << dap << endl;
}
