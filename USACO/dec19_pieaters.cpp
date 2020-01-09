#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 305;

int n, m, a[MAXN][MAXN], dp[MAXN][MAXN];
int prec[MAXN][MAXN][MAXN];

int main(){
	freopen("pieaters.in", "r", stdin);
	freopen("pieaters.out", "w", stdout);
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e, x; 
		scanf("%d %d %d",&x,&s,&e);
		a[s-1][e-1] = x;
	}
	for(int i=0; i<n; i++){
		prec[i][i][i] = a[i][i];
		for(int j=i; j>=0; j--){
			for(int k=i; k<n; k++){
				prec[i][j][k] = max({a[j][k], prec[i][j + 1][k], (k ? prec[i][j][k - 1] : 0)});
			}
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=0; j+i<=n; j++){
			dp[j][j + i] = -1e9;
			for(int k=j; k<j+i; k++){
				dp[j][j+i] = max(dp[j][j+i], dp[j][k] + dp[k+1][j+i] + prec[k][j][j+i-1]);
			}
		}
	}
	cout << dp[0][n] << endl;
}
