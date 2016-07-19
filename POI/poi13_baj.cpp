#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
typedef vector<int> vi;
 
int n, a[1000005];
 
int dp[1000005][3];
int cst[3][3][3];
 
int cost(int s, int e, int x){
	return cst[s+1][e+1][x+1];
}
 
int f(int x, int d){
	if(x == n) return 0;
	if(~dp[x][d]) return dp[x][d];
	int ret = 1e9;
	for(int j=d; j<3; j++){
		ret = min(ret, f(x+1, j) + cst[d][j][a[x+1]+1]);
	}
	return dp[x][d] = ret;
}
 
int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	for(int i=-1; i<=1; i++){
		for(int j=-1; j<=1; j++){
			for(int k=-1; k<=1; k++){
				int l = 0;
				while(l <= 5){
					if(k + i * l == j) break;
					l++;
				}
				cst[i+1][j+1][k+1] = (l > 5 ? 987654321 : l);
			}
		}
	}
	memset(dp, -1, sizeof(dp));
	int prnt = f(1, a[1] + 1);
	if(prnt > 1e8) puts("BRAK");
	else printf("%d\n", prnt);
}