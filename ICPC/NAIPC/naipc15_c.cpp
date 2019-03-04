#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
typedef long long lint;

int n, m, dp[MAXN][MAXN], a[MAXN][MAXN];

lint Fuck(int x, int y){
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			if(!a[i][j]) continue;
			if(i % 2 != j % 2 && a[i][j] % 2 != (x ^ (i % 2))){
				return 1e18;
			}
			if(i % 2 == j % 2 && a[i][j] % 2 != (y ^ (i % 2))){
				return 1e18;
			}
		}
	}
	memset(dp, 0, sizeof(dp));
	lint ans = 0;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + 1;
			if(i % 2 != j % 2 && dp[i][j] % 2 != (x ^ (i % 2))){
				dp[i][j]++;
			}
			if(i % 2 == j % 2 && dp[i][j] % 2 != (y ^ (i % 2))){
				dp[i][j]++;
			}
			if(a[i][j] && dp[i][j] > a[i][j]) return 1e18;
			dp[i][j] = max(dp[i][j], a[i][j]);
			ans += dp[i][j];
		}
	}
	return ans;

}

int solve(vector<int> v){
	v[0] = max(v[0], 1);
	for(int i=1; i<v.size(); i++){
		if(v[i-1] >= v[i] && v[i]){
			return -1;
		}
		v[i] = max(v[i], v[i-1] + 1);
	}
	return accumulate(v.begin(), v.end(), 0);
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			scanf("%d",&a[i][j]);
		}
	}
	if(m == 1){
		vector<int> v;
		for(int i=1; i<=n; i++){
			v.push_back(a[i][1]);
		}
		cout << solve(v) << endl;
		return 0;
	}
	if(n == 1){
		vector<int> v;
		for(int i=1; i<=m; i++){
			v.push_back(a[1][i]);
		}
		cout << solve(v) << endl;
		return 0;
	}
	lint ans = min({Fuck(0, 0), Fuck(0, 1), Fuck(1, 0), Fuck(1, 1)});
	if(ans > 1e11) ans = -1;
	cout << ans << endl;
}
