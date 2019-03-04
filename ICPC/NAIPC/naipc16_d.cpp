#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
const int mod = 1e9 + 7;
typedef pair<int, int> pi;

int k, n, s[2505], p[2505], sz[2505];
vector<int> gph[2505];
double dp[2505][2505], a[2505];

void dfs(int x, int p){
	sz[x] = 0;
	dp[x][0] = 0;
	for(auto &i : gph[x]){
		if(i == p) continue;
		dfs(i, x);
		double nxt[2505] = {};
		fill(nxt, nxt + sz[x] + sz[i] + 1, -1e9);
		for(int j=0; j<=sz[i]; j++){
			for(int k=0; k<=sz[x]; k++){
				nxt[j + k] = max(dp[i][j] + dp[x][k], nxt[j + k]);
			}
		}
		sz[x] += sz[i];
		for(int j=0; j<=sz[x]; j++) dp[x][j] = nxt[j];
	}
	for(int j=sz[x] + 1; j; j--) dp[x][j] = dp[x][j-1] + a[x];
	dp[x][0] = 0;
	sz[x]++;
}

bool trial(double t){
	for(int i=0; i<=n; i++){
		a[i] = p[i] - t * s[i];
	}
	dfs(0, -1);
	return dp[0][k+1] >= 0;
}

int main(){
	cin >> k >> n;
	for(int i=1; i<=n; i++){
		int x;
		scanf("%d %d %d",&s[i],&p[i],&x);
		gph[x].push_back(i);
	}
	double s = 0, e = 1e5;
	for(int i=0; i<60; i++){
		double m = (s+e)/2;
		if(trial(m)) s = m;
		else e = m;
	}
	printf("%.3f\n", s);
}

