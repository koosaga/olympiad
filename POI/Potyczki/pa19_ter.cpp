#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 1005;
const int mod = 1e9 + 7;

int n, m;
lint sum[MAXN][MAXN], A[4][MAXN][MAXN];

lint f(lint x){
	return x * (x - 1) / 2;
}

int main(){	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int q, n, m; cin >> q >> n >> m;
	lint tot = 0;
	for(int i = 0; i < q; i++){
		int sx, sy, ex, ey, v;
		cin >> sx >> sy >> ex >> ey >> v;
		tot += v;
		sum[sx][sy] += v;
		sum[sx][ey+1] -= v;
		sum[ex+1][sy] -= v;
		sum[ex+1][ey+1] += v;
		if(pi(sx, sy) == pi(1, 1)) A[0][ex][ey] += v;
		if(pi(sx, ey) == pi(1, m)) A[1][ex][sy] += v;
		if(pi(ex, sy) == pi(n, 1)) A[2][sx][ey] += v;
		if(pi(ex, ey) == pi(n, m)) A[3][sx][sy] += v;
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			sum[i][j] += sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
		}
	}
	for(int i = n; i; i--){
		for(int j = m; j; j--){
			A[0][i][j] += A[0][i + 1][j] + A[0][i][j + 1] - A[0][i + 1][j + 1];
		}
		for(int j = 1; j <= m; j++){
			A[1][i][j] += A[1][i + 1][j] + A[1][i][j - 1] - A[1][i + 1][j - 1];
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = m; j; j--){
			A[2][i][j] += A[2][i - 1][j] + A[2][i][j + 1] - A[2][i - 1][j + 1];
		}
		for(int j = 1; j <= m; j++){
			A[3][i][j] += A[3][i - 1][j] + A[3][i][j - 1] - A[3][i - 1][j - 1];
		}
	}
	lint ans = 0;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			ans = max(ans, f(tot - sum[i][j]) + f(A[0][i][j]) + f(sum[i][j] - A[0][i][j]));
			ans = max(ans, f(tot - sum[i][j]) + f(A[1][i][j]) + f(sum[i][j] - A[1][i][j]));
			ans = max(ans, f(tot - sum[i][j]) + f(A[2][i][j]) + f(sum[i][j] - A[2][i][j]));
			ans = max(ans, f(tot - sum[i][j]) + f(A[3][i][j]) + f(sum[i][j] - A[3][i][j]));
		}
	}
	cout << ans << "\n";
}

