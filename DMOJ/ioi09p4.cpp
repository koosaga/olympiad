// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi09p4
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll INF = 1e16;
const ll MAXN = 51;
ll dp[MAXN][MAXN][MAXN][MAXN],matriz[MAXN][MAXN],acumulado[MAXN][MAXN],n,m;
ll soma(ll x1,ll y1,ll x2,ll y2){
	return acumulado[x2][y2] - acumulado[x2][y1-1] - acumulado[x1-1][y2] + acumulado[x1-1][y1-1];
}
ll solve(ll x1,ll y1,ll x2,ll y2){
	if(dp[x1][y1][x2][y2] != -1) return dp[x1][y1][x2][y2];
	if(x1 == x2 && y1 == y2){
		return dp[x1][y1][x2][y2] = 0;
	}
	ll ans = INF;
	for(ll quebra = x1;quebra+1<=x2;quebra++){
		ans = min(ans,solve(x1,y1,quebra,y2) + solve(quebra+1,y1,x2,y2) + soma(x1,y1,x2,y2));
	}
	for(ll quebra =  y1;quebra+1<=y2;quebra++){
		ans = min(ans,solve(x1,y1,x2,quebra) + solve(x1,quebra+1,x2,y2) + soma(x1,y1,x2,y2));
	}
	return dp[x1][y1][x2][y2] = ans;
}
int main(){
	memset(dp,-1,sizeof(dp));
	scanf("%lld %lld",&n,&m);
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			scanf("%lld",&matriz[i][j]);
			acumulado[i][j] = matriz[i][j] + acumulado[i-1][j] + acumulado[i][j-1] - acumulado[i-1][j-1];
		}
	}
	printf("%lld\n",solve(1,1,n,m));
	return 0;
}