#include <bits/stdc++.h>
using namespace std;
const int MAXN = 205;
const int mod = 1e9 + 7;
using lint = long long;

int n, m, t;
int adj[MAXN][MAXN];
int ppl[MAXN][MAXN];
double dp[1005][MAXN];
double upMax[MAXN];

int main(){
	scanf("%d %d %d",&n,&m,&t);
	fill(upMax, upMax + MAXN, -1e9);
	for(int i=0; i<m; i++){
		int s, e, x, y; scanf("%d %d %d %d",&s,&e,&x,&y);
		adj[s][e] = adj[e][s] = x;
		ppl[s][e] = ppl[e][s] = y;
		upMax[s] = max(upMax[s], 1.0 * y / x);
		upMax[e] = max(upMax[e], 1.0 * y / x);
	}
	for(int i=0; i<1005; i++) fill(dp[i], dp[i] + MAXN, -1e9);
	dp[0][1] = 0;
	for(int i=0; i<t; i++){
		for(int j=1; j<=n; j++){
			dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + upMax[j]);
			for(int k=1; k<=n; k++){
				if(!adj[j][k] || i + adj[j][k] > t) continue;
				dp[i + adj[j][k]][k] = max(dp[i + adj[j][k]][k], dp[i][j] + ppl[j][k]);
			}
		}
	}
	printf("%.10f\n", dp[t][1]);
}
