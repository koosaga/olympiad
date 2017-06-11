#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;

int n, m, k;
int b[105][1005], s[105][1005];
int adj[105][105], dx[105][105];
llf gph[105][105];

bool trial(llf t){
	// TotalProfit - t * TotalTime > 0
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(adj[i][j] > 1e9 + 10) gph[i][j] = -1e12;
			else gph[i][j] = dx[i][j] - t * adj[i][j];
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			for(int k=1; k<=n; k++){
				gph[j][k] = max(gph[j][k], gph[j][i] + gph[i][k]);
			}
		}
	}
	for(int i=1; i<=n; i++){
		if(gph[i][i] >= 0) return 1;
	}
	return 0;
}

int main(){
	scanf("%d %d %d",&n,&m,&k);
	for(int i=1; i<=n; i++){
		for(int j=0; j<k; j++) scanf("%d %d",&b[i][j],&s[i][j]);
	}
	memset(adj, 0x3f, sizeof(adj));
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		adj[s][e] = x;
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			for(int k=1; k<=n; k++){
				adj[j][k] = min(adj[j][i] + adj[i][k], adj[j][k]);
			}
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			for(int l=0; l<k; l++){
				if(~s[j][l] && ~b[i][l]) dx[i][j] = max(dx[i][j], s[j][l] - b[i][l]);
			}
		}
	}
	llf s = 0, e = 2e9;
	for(int i=0; i<100; i++){
		llf m = (s+e)/2;
		if(trial(m)) s = m;
		else e = m;
	}
	printf("%lld",(lint)floor(e));
}

