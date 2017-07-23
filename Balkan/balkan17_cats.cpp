#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, a[5005], c1, c2, c3;
int dp[5005][2][2][3];

int main(){
	int tc;
	cin >> tc;
	while(tc--){
		cin >> n;
		for(int i=1; i<=n; i++) cin >> a[i];
	 	c1 = count(a+1, a+n+1, 0);
		c2 = count(a+1, a+n+1, 1);
		c3 = count(a+1, a+n+1, 2);
		if(c3 == 0){
			if(c1 > 0 && c2 > 0) puts("-1");
			else puts("0");
			continue;
		}
		if(c1 == 0 || c2 == 0){
			puts("0");
			continue;
		}
		int ans = 0;
		memset(dp, 0, sizeof(dp));
		for(int i=0; i<2; i++){
			dp[c3][0][0][i] = dp[c3][0][1][i] = dp[c3][1][0][i] = -1e9;
		}
		for(int i=0; i<=c3; i++){
			dp[i][0][0][1] = dp[i][0][1][1] = dp[i][0][0][0] = dp[i][1][0][0] = -1e9;
		}
		for(int i=n; i; i--){
			if(a[i] == 2){
				ans = max(ans, dp[1][1][1][2] + 1);
			}
			else{
				ans = max(ans, dp[0][a[i] == 1][a[i] == 0][a[i]] + 1);
			}
			for(int j=0; j<=c3; j++){
				for(int ot02 = 0; ot02 < 2; ot02++){
					for(int ot12 = 0; ot12 < 2; ot12++){
						auto solve = [&](int prv){
							int cur = -1e9;
							if(ot02 == 0 && prv == 1) return; //cur = 1e9;
							if(ot12 == 0 && prv == 0) return; // cur = 1e9;
							if(prv + a[i] == 1){
								if(j < c3) cur = max(cur, dp[j+1][1][1][a[i]]);
							}
							else if(a[i] == 2){
								if(j < c3) cur = max(cur, dp[j+1][ot02|(prv!=0)][ot12|(prv!=1)][a[i]]);
							}
							else if(prv == 2){
								cur = max(cur, dp[j][ot02|(a[i]!=0)][ot12|(a[i]!=1)][a[i]]);
							}
							else{
								cur = max(cur, dp[j][ot02][ot12][a[i]]);
							}
							dp[j][ot02][ot12][prv] = max(dp[j][ot02][ot12][prv], cur + 1);
						};
						for(int prv = 0; prv < 3; prv++){
							if(prv == a[i]) continue;
							solve(prv);
						}
						solve(a[i]);
					}
				}
			}
		}
		printf("%d\n", n - ans);
	}
}
