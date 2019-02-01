#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
#define sz(v) int((v).size())

vector<pi> perc[105];
int dp[11][105][105];
pi tr[11][105][105];
int n, k, m, a[12];

bool ok(int l, int r){
	bitset<105> dp[11][105];
	dp[0][0][0] = 1;
	for(int i=0; i<m; i++){
		for(int j=0; j<=100; j++){
			for(auto &k : perc[a[i]]){
				if(k.first < l || k.first > r) continue;
				if(j >= k.first){
					dp[i+1][j] |= (dp[i][j-k.first] << k.second);
				}
			}
		}
	}
	return dp[m][n][k];
}

int main(){
	for(int i=1; i<=100; i++){
		for(int j=0; j<=i; j++){
			int val = (100 * j) / i;
			int modv = (100 * j) % i;
			if(modv >= (i + 1) / 2){
				// round up
				val++;
			}
			if(i % 2 == 0 && modv == i / 2 && val % 2 == 1){
				val--;
			}
			assert(val >= 0 && val <= 100);
			perc[val].emplace_back(i, j);
		}
	}
	cin >> k>> n >> m;
	for(int i=0; i<m; i++) cin >> a[i];
	int r = 0;
	pi ans(1e9, -1);
	for(int i=0; i<=100; i++){
		while(r <= 100 && !ok(i, r)) r++;
		if(r == 101) break;
		ans = min(ans, pi(r - i, i));
	}
	int st = ans.second;
	int ed = ans.first + ans.second;
	dp[0][0][0] = 1;
	for(int i=0; i<m; i++){
		for(int j=0; j<=100; j++){
			for(int k=0; k<=j; k++){
				if(!dp[i][j][k]) continue;
				for(auto &l : perc[a[i]]){
					if(l.first < st || l.first > ed) continue;
					if(j + l.first <= 100){
						dp[i+1][j+l.first][k+l.second] = 1;
						tr[i+1][j+l.first][k+l.second] = l;
					}
				}
			}
		}
	}
	assert(dp[m][n][k]);
	pi ret[11];
	for(int i=m; i; i--){
		ret[i] = tr[i][n][k];
		n -= ret[i].first;
		k -= ret[i].second;
	}
	for(int i=1; i<=m; i++) printf("%d %d\n", ret[i].first - ret[i].second, ret[i].first);
}
