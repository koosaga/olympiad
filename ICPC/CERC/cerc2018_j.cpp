#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
using lint = long long;

int n, m;
char str[MAXN][MAXN];
int dp[MAXN][MAXN];

int solve(){
	int ret = 0;
	for(int i=1; i<n; i++){
		for(int j=1; j<m; j++){
			dp[i][j] = 1e9;
			if(str[i-1][j] == str[i][j]){
				dp[i][j] = min(dp[i][j], dp[i-1][j] + 1);
			}
			else dp[i][j] = 0;
			if(str[i][j-1] == str[i][j]){
				dp[i][j] = min(dp[i][j], dp[i][j-1] + 1);
			}
			else dp[i][j] = 0; 
			ret += dp[i][j];
		}
	}
	return ret;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++) scanf("%s",str[i]);
	lint ret = solve();
	for(int i=0; i<n; i++) reverse(str[i], str[i] + m);
	ret += solve();
	for(int i=0; i<n-1-i; i++){
		for(int j=0; j<m; j++) swap(str[i][j], str[n-1-i][j]);
	}
	ret += solve();
	for(int i=0; i<n; i++) reverse(str[i], str[i] + m);
	ret += solve();
	cout << ret << endl;
}
