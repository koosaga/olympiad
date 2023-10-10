#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 10005;
using pi = pair<int, int>;

int n;
char str[MAXN];
bool dp[MAXN][MAXN];

int main(){
	string s;
	cin >> n >> s;
	n = 0;
	int ans = 0;
	for(auto &i : s){
		if(i == '-'){
			for(int j=0; j<n; j++){
				ans -= dp[j][n-1];
			}
			n--;
		}
		else{
			str[n++] = i;
			dp[n-1][n-1] = 1;
			ans++;
			for(int j=n-2; j>=0; j--){
				if(j == n - 2) dp[n-2][n-1] = (str[n-2] == str[n-1]);
				else dp[j][n-1] = (str[j] == str[n-1] && dp[j+1][n-2]);
				ans += dp[j][n-1];
			}
		}
		printf("%d ", ans);
	}
}
