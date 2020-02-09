#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int mod = 1e9 + 7;
const int MAXN = 355;

int n;
int bino[MAXN][MAXN];
int dp[MAXN][MAXN][2];

int f(int x, int y, int z){
	if(x == 0) return y == 0 && z;
	if(~dp[x][y][z]) return dp[x][y][z];
	int ret = 0;
	for(int i=0; i<=y; i++){
		ret += 1ll * f(x - 1, y - i, z | (x == i)) * bino[y][i] % mod;
		if(ret >= mod) ret -= mod;
	}
	return dp[x][y][z] = ret;
}

int main(){
	cin >> n;
	for(int i=0; i<=n; i++){
		bino[i][0] = 1;
		for(int j=1; j<=i; j++){
			bino[i][j] = (bino[i-1][j] + bino[i-1][j-1]) % mod;
		}
	}
	memset(dp, -1, sizeof(dp));
	cout << f(n, n, 0) << endl;
}
