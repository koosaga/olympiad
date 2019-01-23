#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1005;

int n, a[MAXN];
bool vis[MAXN][33];
double dp[MAXN][33];

double sub(int m, int s);

double f(int m){
	if(m == 1) return 0;
	return sub(m, 0) / m;
}

double sub(int m, int s){
	if(m == 0) return 0;
	if(s == n + 1) return (m == 0 ? 0 : 1e18);
	if(vis[m][s]) return dp[m][s];
	vis[m][s] = 1;
	double ret = 1e18;
	for(int i=1; i<=m; i++){
		if(s == 0 && i == m) continue;
		ret = min(ret, sub(m - i, s + 1) + i * (f(i) + a[s]));
	}
//	printf("%d %d = %.10f\n", m, s, ret);
	return dp[m][s] = ret;
}

int main(){
	int l, r;
	cin >> l >> r >> n;
	for(int i=0; i<=n; i++) cin >> a[i];
	printf("%.10f\n", f(r - l));
}
