#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, p, a[305], b[305];
int dp[305][305];

int f(int x, int y){
	if(x == n) return 0;
	if(~dp[x][y]) return dp[x][y];
	int ret = 1e9;
	for(int i=y; i<=n; i++){
		if(a[i] - a[y] + b[y] - b[x] <= p){
			if(pi(x, y) != pi(y, i)) ret = min(ret, f(y, i) + 1);
		}
	}
	return dp[x][y] = ret;
}

int main(){
	cin >> p >> n;
	for(int i=1; i<=n; i++){
		cin >> a[i] >> b[i];
		a[i] += a[i-1];
		b[i] += b[i-1];
	}
	memset(dp, -1, sizeof(dp));
	cout << f(0, 0);
}

