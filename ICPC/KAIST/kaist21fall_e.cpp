#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 1000005;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, -1, 0, 1};

lint n, m, p;
pi a[1005];
pi dp[2][1005][1005];

int main(){
	cin >> n >> m >> p;
	for(int i = 0; i < n; i++){
		cin >> a[i].first >> a[i].second;
	}
	for(int i = n-1; i; i--){
		a[i].first /= a[i-1].first;
	}
	if(p % a[0].first != 0){
		puts("-1");
		return 0;
	}
	p /= a[0].first;
	for(int i = 0; i <= m; i++){
		for(int j = 0; j <= m; j++){
			dp[0][i][j] = pi(0, -1);
		}
	}
	dp[0][0][0] = pi(0, 0);
	for(int i = 0; i < n - 1; i++){
		for(int j = 0; j <= m; j++){
			for(int k = 0; k <= m; k++){
				dp[(i+1)%2][j][k] = pi(5e18, -5e18);
			}
		}
		for(int k = 0; k <= m; k++){
			lint must_use = (p - k) % a[i + 1].first;
			if(must_use < 0) must_use += a[i + 1].first;
			lint base_promo = (k + must_use) / a[i + 1].first;
			if(base_promo > m) continue;
			int nxtk = base_promo;
			for(int j = 0; j + must_use <= m; j++){
				if(dp[i%2][k][j].first > dp[i%2][k][j].second) continue;
				int nxtj = j + must_use;
				dp[(i+1)%2][nxtk][nxtj].first = 
					min(dp[(i+1)%2][nxtk][nxtj].first,
							dp[i%2][k][j].first + must_use * a[i].second);

				dp[(i+1)%2][nxtk][nxtj].second = 
					max(dp[(i+1)%2][nxtk][nxtj].second,
							dp[i%2][k][j].second + must_use * a[i].second);
			}
		}
		for(int j = 1; j <= m; j++){
			for(lint k = a[i+1].first; k <= m; k++){
				dp[(i+1)%2][j][k].first = min(dp[(i+1)%2][j][k].first, dp[(i+1)%2][j-1][k-a[i+1].first].first + a[i].second * a[i+1].first);
				dp[(i+1)%2][j][k].second = max(dp[(i+1)%2][j][k].second, dp[(i+1)%2][j-1][k-a[i+1].first].second + a[i].second * a[i+1].first);
			}
		}
		p /= a[i + 1].first;
	}
	lint dmax = -5e18, dmin = 5e18;
	for(int j = 0; j <= m; j++){
		for(int k = 0; k <= m; k++){
			pi x = dp[(n-1)%2][j][k];
			if(x.first > x.second) continue;
			if(p - j != m - k) continue;
			x.first += (p - j) * a[n-1].second;
			x.second += (p - j) * a[n-1].second;
			dmin = min(dmin, x.first);
			dmax = max(dmax, x.second);
		}
	}
	if(dmin <= dmax) printf("%lld %lld\n", dmin, dmax);
	else puts("-1");
}
