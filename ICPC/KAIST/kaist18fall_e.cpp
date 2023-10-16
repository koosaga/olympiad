#include <bits/stdc++.h>
using namespace std;
const int MAXN = 250005;
using lint = long long;

int n, s;
lint arr[MAXN], dp[2][10][10][3];

int main(){
    scanf("%d %d",&n,&s);
	for(int i=0; i<n; i++) scanf("%lld",&arr[i]);
	if(n == 1){ 
	    cout << arr[0] << endl;
	    return 0;
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0][0][1] = 0;
	auto upd = [&](lint &a, lint b){ a = min(a, b); };
	for(int i=0; i<n; i++){
		auto cur = dp[i%2], nxt = dp[(i+1)%2];
		memset(dp[(i+1)%2], 0x3f, sizeof(dp[(i+1)%2]));
		for(int j=0; j<=s; j++){
			for(int k=0; k<=s; k++){
				for(int l=0; l<3; l++){
					if(j < s) upd(nxt[j+1][k][2], cur[j][k][l]);
					upd(nxt[j][k][2], cur[j][k][l] + arr[i]);
					if(k < s && l != 0) upd(nxt[j][k+1][l-1], cur[j][k][l] + arr[i]);
					if(l != 0) upd(nxt[j][k][l-1], cur[j][k][l]);
				}
			}
		}
	}
	lint ans = 1e18;
	for(int i=0; i<=s; i++) ans = min({ans, dp[n%2][i][i][1], dp[n%2][i][i][2]});
	cout << ans << endl;
}
