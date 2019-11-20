#include <bits/stdc++.h>
using namespace std;
using lint = long long;
const int MAXN = 105;
const lint inf = 3e18;

lint f[MAXN];
lint k, n;
lint dp[MAXN][MAXN];
int chk[MAXN];

void dfs(int x, int y, lint k){
	if(x == 0) return;
	if(x == 1){
		if(k == 2) chk[x] = 1;
		return;
	}
	if(dp[x-1][y] >= k){
		dfs(x - 1, y, k);
	}
	else{
		chk[x] = 1;
		dfs(x - 2, y - 1, k - dp[x-1][y]);
	}
}

int main(){
	f[1] = 1;
	f[2] = 2;
	for(int i=3; i<MAXN; i++) f[i] = min(inf, f[i-1] + f[i-2]);
	k = min(k, MAXN - 1ll);
	fill(dp[0], dp[0] + MAXN, 1);
	cin >> k >> n;
	n += k - 1;
	for(int i=1; i<MAXN; i++){
		for(int j=0; j<=k; j++){
			dp[i][j] = dp[i-1][j]; 
			if(j > 0) dp[i][j] += dp[max(0, i-2)][j-1]; // checked last, or not checked last
			dp[i][j] = min(dp[i][j], inf);
		}
	}
	if(dp[MAXN-1][k] < n + 1){
		puts("NIE");
		return 0;
	}
	dfs(MAXN - 1, k, n + 1);
	lint ret = 0;
	for(int i=1; i<MAXN; i++){
		if(chk[i]) ret = min(inf, ret + f[i]);
	}
	if(ret > 1000000ll * 1000000ll * 1000000ll){
		puts("NIE");
		return 0;
	}
	cout << ret << endl;
}
