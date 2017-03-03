#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

int n, m, mod;
pi a[1205], b[20005];
bool adj[605][605];
int dp[605][605];

int main(){
	cin >> n >> m >> mod;
	for(int i=n-1; i>=0; i--){
		scanf("%d %d",&a[i].first, &a[i].second);
		a[i+n] = a[i];
	}
	for(int i=0; i<m; i++){
		scanf("%d %d",&b[i].first, &b[i].second);
	}
	for(int i=0; i<n; i++){
		sort(b, b+m, [&](const pi &p, const pi &q){
			return ccw(a[i], p, q) > 0;
		});
		int p = 0;
		for(int j=i+2; j<i+n-1; j++){
			while(p < m && ccw(a[i], b[p], a[j]) > 0) p++;
			if(p != m && ccw(a[i], b[p], a[j]) == 0){
				continue;
			}
			if(p % 2 == 0) adj[i%n][j%n] = 1;
		}
		adj[i][(i+1)%n] = 1;
		adj[i][(i+n-1)%n] = 1;
	}
	for(int i=0; i<n-1; i++){
		dp[i][i+1] = 1;
	}
	for(int i=2; i<n; i++){
		for(int j=0; j+i<n; j++){
			for(int k=j+1; k<j+i; k++){
				dp[j][j+i] += dp[j][k] * dp[k][j+i] % mod;
				dp[j][j+i] %= mod;
			}
			if(adj[j][j+i] == 0) dp[j][j+i] = 0;
		}
	}
	int ret = 0;
	for(int i=1; i<n-1; i++){
		if(adj[0][i] && adj[i][n-1]){
			ret += dp[0][i] * dp[i][n-1] % mod;
			ret %= mod;
		}
	}
	cout << ret;
}
