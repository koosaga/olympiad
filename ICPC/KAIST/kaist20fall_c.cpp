#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 18;
using lint = long long;
using pi = pair<int, int>;

int n, a[MAXN][MAXN];
int dp[1 << MAXN];
int ear[1 << MAXN][MAXN][MAXN];

int solve(){
	memset(dp, 0x3f, sizeof(dp));
	memset(ear, 0x3f, sizeof(ear));
	for(int i=0; i<n; i++) dp[1 << i] = 0;
	for(int i=1; i<(1<<n); i++){
		vector<int> in, out;
		for(int j=0; j<n; j++){
			if((i >> j) & 1) in.push_back(j);
			else out.push_back(j);
		}
		for(auto &u : in){
			for(auto &v : in){
				if(u == v) continue;
				dp[i] = min(dp[i], ear[i][u][v] + a[u][v]);
				for(auto &x : out){
					ear[i | (1 << x)][x][v] = min(
					ear[i | (1 << x)][x][v], 
					ear[i][u][v] + a[u][x]);
				}
			}
		}
		for(auto &u : in){
			for(auto &v : in){
				if(u == v) continue;
				for(auto &x : out){
					ear[i | (1 << x)][x][v] = min(
					ear[i | (1 << x)][x][v], 
					dp[i] + a[u][x]);
				}
			}
		}
		for(auto &u : in){
			for(auto &x : out){
				for(auto &y : out){
					if(x == y) continue;
					ear[i | (1 << x) | (1 << y)][x][y] = min(
					ear[i | (1 << x) | (1 << y)][x][y], 
					dp[i] + a[u][x] + a[y][u]);
				}
			}
		}
	}
	return dp[(1 << n) - 1];
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin >> a[i][j];
		}
	}
	int dap = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			if(~a[i][j]){
				int foo = min(a[i][j], a[j][i]);
				dap += foo;
				a[i][j] -= foo;
				a[j][i] -= foo;
			}
			else a[i][j] = a[j][i] = 5e8;
		}
	}
	dap += solve();
	if(dap > 4e8) dap = -1;
	cout << dap << endl;
}

