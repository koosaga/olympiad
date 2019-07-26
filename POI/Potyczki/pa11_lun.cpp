#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 105;

int n, m, r;
int dp[MAXN][1<<10], a[MAXN], b[MAXN];
int L[MAXN][MAXN], R[MAXN][MAXN];

int Count(int s, int e){
	return upper_bound(a + 1, a + n + 1, e) - lower_bound(a + 1, a + n + 1, s);
}

int main(){
	for(int i=0; i<MAXN; i++) fill(dp[i], dp[i] + 1024, 1e9);
	cin >> n >> m >> r;
	for(int i=1; i<=n; i++) cin >> a[i];
	for(int i=0; i<m; i++) cin >> b[i];
	for(int i=1; i<=n; i++){
		for(int j=0; j<m; j++){
			L[i][j] = Count(a[i], a[i] + b[j] - 1);
			R[i][j] = Count(a[i] - b[j] + 1, a[i]);
		}
	}
	dp[0][0] = -1e9;
	for(int i=0; i<n; i++){
		for(int j=0; j<(1<<m); j++){
			if(dp[i][j] > 5e8) continue;
			int curTime = dp[i][j] + r;
			for(int k=0; k<m; k++){
				if((j >> k) & 1) continue;
				for(int l=1; l<=n; l++){
					if(a[l] >= curTime){
						int nxt = L[l][k];
						if(nxt > 0) dp[i + nxt][j | (1 << k)] = min(dp[i + nxt][j | (1<<k)], a[l] + b[k]);
					}
					if(a[l] - b[k] + 1 >= curTime){
						int nxt = R[l][k];
						if(nxt > 0) dp[i + nxt][j | (1 << k)] = min(dp[i + nxt][j | (1<<k)], a[l] + 1);
					}
				}
				int nxt = Count(curTime, curTime + b[k] - 1);
				if(nxt > 0) dp[i + nxt][j | (1<<k)] = min(dp[i + nxt][j | (1<<k)], curTime + b[k]);
			}
		}
	}
	for(int j=n; j>=0; j--){
		if(*min_element(dp[j], dp[j] + 1024) <= 5e8){
			cout << j << endl;
			return 0;
		}
	}
}
