#include <bits/stdc++.h>
using namespace std;
const int MAXN = 4005;

int n, m, dp[MAXN][MAXN];
char s[MAXN], t[MAXN];
int ns[2][MAXN];
int nt[2][MAXN];

int f(int x, int y){
	if(x == n + 1 && y == m + 1) return 0;
	if(~dp[x][y]) return dp[x][y];
	int ret = 1e9;
	for(int i=0; i<2; i++){
		int nx = ns[i][x] + 1;
		int ny = nt[i][y] + 1;
		ret = min(ret, f(nx, ny) + 1);
	}
	return dp[x][y] = ret;
}

void track(int x, int y){
	if(x == n + 1 && y == m + 1) return;
	int w = f(x, y);
	for(int i=0; i<2; i++){
		int nx = ns[i][x] + 1;
		int ny = nt[i][y] + 1;
		if(f(nx, ny) + 1 == w){
			printf("%d", i);
			track(nx, ny);
			return;
		}
	}
	assert(0);
}

int main(){
	cin >> s >> t;
	n = strlen(s);
	m = strlen(t);
	ns[0][n] = ns[1][n] = n;
	ns[0][n+1] = ns[1][n+1] = n;
	for(int i=n-1; i>=0; i--){
		ns[0][i] = ns[0][i+1];
		ns[1][i] = ns[1][i+1];
		ns[s[i] - '0'][i] = i;
	}
	nt[0][m] = nt[1][m] = m;
	nt[0][m+1] = nt[1][m+1] = m;
	for(int i=m-1; i>=0; i--){
		nt[0][i] = nt[0][i+1];
		nt[1][i] = nt[1][i+1];
		nt[t[i] - '0'][i] = i;
	}
	memset(dp, -1, sizeof(dp));
	f(0, 0);
	track(0, 0);
}

