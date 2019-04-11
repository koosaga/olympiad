#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;
using real_t = double;
const int MAXN = 1005;

int n, d, r;
real_t bino[MAXN][MAXN];
real_t dp[MAXN][MAXN];

real_t trans(int n, int d, int k){
	return (bino[d - 1][k - 1] * bino[n][k]) / bino[n + d - 1][n - 1];
}

int main(){
	cin >> n >> d >> r;
	for(int i=0; i<MAXN; i++){
		bino[i][0] = 1;
		for(int j=1; j<=i; j++){
			bino[i][j] = bino[i-1][j] + bino[i-1][j-1];
		}
	}
	for(int i=0; i<=n; i++){
		for(int j=0; j<=d; j++){
			if(i <= r){
				dp[i][j] = i + j;
				continue;
			}
			dp[i][j] = r;
			for(int k=1; k<=min(j, i); k++){
				dp[i][j] += dp[k][j - k] * trans(i, j, k);
			}
		}
	}
	printf("%.10f\n", dp[n][d]);
}
