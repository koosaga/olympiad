#include<bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 2505;
const int mod = 1e8;

int dp[13][13][1<<12];
int n, m, a[12][12];

int f(int x, int y, int msk){
	if(x == n) return 1;
	if(y == m) return f(x+1, 0, msk);
	if(~dp[x][y][msk]) return dp[x][y][msk];
	if((msk >> y) & 1) return dp[x][y][msk] = f(x, y+1, msk ^ (1<<y));
	int ret = f(x, y+1, msk);
	if(a[x][y] && ((msk >> (y-1)) & 1) == 0){
		ret += f(x, y+1, msk | (1<<y));
	}
	return dp[x][y][msk] = ret % mod;
}

int main(){
	memset(dp, -1, sizeof(dp));
	cin >> n >> m;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			cin >> a[i][j];
		}
	}
	cout << f(0, 0, 0);
}
