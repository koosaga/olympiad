#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;

int vis[2][1000005];
int n, a[2][1000005];
int mx[1000005], dp[1000005][3];

int f(int x, int y){
	if(x >= n) return 1e9;
	if(x == n-1 && y == 2) return 0;
	if((y == 0 || y == 1) && a[0][x] == a[1][x]) return f(x, 2);
	if(~dp[x][y]) return dp[x][y];
	int ret = 1e9;
	if(y == 0){
		ret = min(ret, f(x+1, 0) + (a[0][x] != a[0][x+1]) + (mx[a[1][x]] == x));
		ret = min(ret, f(x, 2) + (a[0][x] != a[1][x]));
	}
	if(y == 1){
		ret = min(ret, f(x+1, 1) + (a[1][x] != a[1][x+1]) + (mx[a[0][x]] == x));
		ret = min(ret, f(x, 2) + (a[0][x] != a[1][x]));
	}
	if(y == 2){
		ret = min(ret, f(x+1, 0) + (a[0][x] != a[0][x+1]));
		ret = min(ret, f(x+1, 1) + (a[1][x] != a[1][x+1]));
	}
	return dp[x][y] = ret;
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<2; i++){
		for(int j=0; j<n; j++){
			scanf("%d",&a[i][j]);
			mx[a[i][j]] = max(mx[a[i][j]], j);
		}
	}
	memset(dp, -1, sizeof(dp));
	cout << f(0, 0);
}
