#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1000000;
const int MAXN = 1000000;

int dp[2][40][40][40][4][4];
int ok[4][4][4];
int p, q, r, s;

int main(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			for(int k=0; k<4; k++){
				if((i/2 == j/2 && j/2 == k/2) || (i%2 == j%2 && j%2 == k%2)){
					ok[i][j][k] = 0;
				}
				else ok[i][j][k] = 1;
			}
		}
	}
	cin >> p >> q >> r >> s;
	for(int i=0; i<=p; i++){
		memset(dp[i%2], 0, sizeof(dp[i%2]));
		for(int j=0; j<=q; j++){
			for(int k=0; k<=r; k++){
				for(int l=0; l<=s; l++){
					for(int m=0; m<4; m++){
						for(int n=0; n<4; n++){
							if(i + j + k + l == 0) dp[i%2][j][k][l][m][n] = 1;
							if(i && ok[0][m][n]) dp[i%2][j][k][l][m][n] += dp[(i-1)%2][j][k][l][0][m];
							if(j && ok[1][m][n]) dp[i%2][j][k][l][m][n] += dp[i%2][j-1][k][l][1][m];
							if(k && ok[2][m][n]) dp[i%2][j][k][l][m][n] += dp[i%2][j][k-1][l][2][m];
							if(l && ok[3][m][n]) dp[i%2][j][k][l][m][n] += dp[i%2][j][k][l-1][3][m];
							dp[i%2][j][k][l][m][n] %= mod;
						}
					}
				}
			}
		}
	}
	int ret = 0;
	for(int i=0; i<4; i++) ret += dp[p%2][q][r][s][i][i];
	cout << ret % mod;
}
