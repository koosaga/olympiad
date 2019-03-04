#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
const int mod = 1e9 + 7;
typedef long long lint;
typedef pair<int, int> pi;

int n, m, chk[MAXN];
vector<int> gph[MAXN];
int din[MAXN], dout[MAXN], piv;
lint dp[2][MAXN];
pi nxt[MAXN];

void dfs(int x){
	din[x] = piv;
	for(auto &i : gph[x]) dfs(i);
	dout[x] = ++piv;
	nxt[dout[x]] = pi(din[x], chk[x]);
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=2; i<=n; i++){
		int p;
		scanf("%d",&p);
		gph[p].push_back(i);
	}
	for(int i=0; i<m; i++){
		int x;
		scanf("%d",&x);
		chk[x] = 1;
	}
	dfs(1);
	for(int i=0; i<=m; i++){
		memset(dp[i%2], 0, sizeof(dp[i%2]));
		if(i == 0) dp[0][0] = 1;
		for(int j=1; j<=n; j++){
			dp[i&1][j] = dp[i&1][j-1];
			if(nxt[j].second){
				if(i) dp[i&1][j] += dp[(i+1)&1][nxt[j].first];
			}
			else dp[i&1][j] += dp[i&1][nxt[j].first];
			if(dp[i&1][j] >= mod) dp[i&1][j] -= mod;
		}
		cout << dp[i%2][n] << endl;
	}
}
