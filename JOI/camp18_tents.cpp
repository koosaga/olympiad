#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3005;
const int mod = 1e9 + 7;
typedef long long lint;

lint dp[MAXN][MAXN];

lint f(int x, int y){
	if(y < 0 || x < 0) return 0;
	if(x == 0) return 1;
	if(~dp[x][y]) return dp[x][y];
	lint ret = f(x-1, y);
	ret += f(x-1, y-2) * (y * (y - 1) / 2);
	ret += f(x-2, y-1) * y * (x - 1);
	ret += f(x-1, y-1) * 4 * y;
	return dp[x][y] = ret % mod;
}

int main(){
	int n, m;
	cin >> n >> m;
	memset(dp, -1, sizeof(dp));
	cout << (f(n, m) + mod - 1) % mod << endl;
}
