#include <bits/stdc++.h>
using namespace std;

int n, m, chk[105];
int dp[105][105];

int f(int x, int c){
	if(x > n) return 0;
	if(~dp[x][c]) return dp[x][c];
	int ret = 1e9;
	if(chk[x]) ret = min(ret, f(x+1, c));
	ret = min(ret, f(x+1, c) + 10000);
	ret = min(ret, f(x+3, c+1) + 25000);
	ret = min(ret, f(x+5, c+2) + 37000);
	if(c > 2) ret = min(ret, f(x+1, c-3));
	return dp[x][c] = ret;
}

int main(){
	memset(dp, -1, sizeof(dp));
	cin >> n >> m;
	while(m--){
		int x;
		cin >> x;
		chk[x] = 1;
	}
	cout << f(1, 0);
}

