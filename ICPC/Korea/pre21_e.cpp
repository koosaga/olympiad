#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
using point = complex<llf>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 4005;

int m, n;
int a[MAXN];
double cost[MAXN][MAXN], dp[41][MAXN];

int main(){
	scanf("%d %d",&m,&n);
	for(int i = 1; i <= n; i++) scanf("%d",&a[i]);
	m = min(m, n);
	for(int i = 1; i <= n; i++){
		int sqs = 0, s = 0;
		for(int j = i; j <= n; j++){
			sqs += a[j]*a[j];
			s += a[j];
			cost[i][j] = sqs - 1.0 * s * s / (j - i + 1);
		}
	}
	fill(dp[0] + 1, dp[0] + n + 1, 1e9);
	for(int i = 1; i <= m; i++){
        fill(dp[i], dp[i] + n + 1, 1e9);
		for(int j = 0; j <= n; j++){
			for(int k = j + 1; k <= n; k++) dp[i][k] = min(dp[i][k], dp[i-1][j] + cost[j+1][k]);
		}
	}
	printf("%.10f\n", dp[m][n]);
}
