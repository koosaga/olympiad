#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

vector<pi> gph[1005];
int s[100005], e[100005], x[100005];
int typ[200005], val[200005];
int n, m, q;

int dp[1005][1005];

int main(){
	freopen("evacuation.in", "r", stdin);
	freopen("evacuation.out", "w", stdout);
	memset(x, 0x3f, sizeof(x));
	scanf("%d %d %d",&n,&m,&q);
	for(int i=1; i<=m; i++){
		scanf("%d %d",&s[i],&e[i]);
	}
	for(int i=0; i<q; i++){
		char t[5];
		scanf("%s",t);
		if(*t == 'U'){
			typ[i] = 1;
			scanf("%d",&val[i]);
			x[val[i]] = i;
		}
		else{
			typ[i] = 2;
			scanf("%d",&val[i]);
		}
	}
	fill(dp[0] + 1, dp[0] + n + 1, -1e9);
	dp[0][1] = 1e9;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			dp[i][j] = dp[i-1][j];
		}
		for(int j=1; j<=m; j++){
			dp[i][e[j]] = max(min(dp[i-1][s[j]], x[j]), dp[i][e[j]]);
		}
	}
	for(int i=0; i<q; i++){
		if(typ[i] == 2){
			int s = 0, e = n;
			while(s != e){
				int m = (s+e)/2;
				if(dp[m][val[i]] >= i) e = m;
				else s = m+1;
			}
			if(s == n) puts("-1");
			else printf("%d\n", s);
		}
	}
}