#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 1000005;
const int mod = 1e9 + 7;

int n, k, p;
int adj[MAXN][7];
int dp[MAXN][3][3];

bool con(int s, int e){
	if(abs(e - s) > p) return 0;
	return s <= n && e <= n && !adj[s][e - s + 3];
}

lint solve(int s, int e, int siz){
	vector<int> perm(siz);
	iota(perm.begin() + 1, perm.end(), n - siz + 1);
	perm[0] = n;
	lint ret = 0;
	do{
		bool good = 0;
		for(int i=0; i<sz(perm); i++){
			if(perm[i] == s && perm[(i + 1) % sz(perm)] == e) good = 1;
		}
		for(int i=0; i<sz(perm); i++){
			if(perm[i] != s && !con(perm[i], perm[(i + 1) % sz(perm)])) good = 0;
		}
		if(good) ret++;
	}while(next_permutation(all(perm)));

	return ret;
}

int main(){
	scanf("%d %d %d",&n,&k,&p);
	for(int i=0; i<k; i++){
		int s, e; scanf("%d %d",&s,&e);
		if(abs(e - s) > p) continue;
		adj[s][e-s+3] = 1;
	}
	if(n == 1){
		puts("1");
		return 0;
	}
	if(n <= 8){
		int ret = 0;
		for(int i=1; i<n; i++) if(con(n, i)) ret += solve(n, i, n);
		cout << ret << endl;
		return 0;
	}
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			if(con(1, i+2) && con(j+2, 1) && i!=j) dp[2][i][j] = 1;
		}
	}
	auto add = [&](int x, int y, int z, int v){
		dp[x][y][z] += v;
		if(dp[x][y][z] >= mod) dp[x][y][z] -= mod;
	};
	for(int i=2; i<=n-8; i++){
		if(con(i, i + 3)) add(i + 1, 2, 0, dp[i][0][1]);
		if(con(i + 3, i)) add(i + 1, 0, 2, dp[i][1][0]);

		if(con(i, i + 2)) add(i + 1, 1, 0, dp[i][0][1]);
		if(con(i + 2, i)) add(i + 1, 0, 1, dp[i][1][0]);

		if(con(i, i + 3)) add(i + 1, 2, 1, dp[i][0][2]);
		if(con(i + 3, i)) add(i + 1, 1, 2, dp[i][2][0]);

		if(con(i, i + 1)) add(i + 1, 0, 1, dp[i][0][2]);
		if(con(i + 1, i)) add(i + 1, 1, 0, dp[i][2][0]);

		if(con(i + 1, i) && con(i, i + 3)) add(i + 2, 1, 0, dp[i][1][2]);
		if(con(i + 3, i) && con(i, i + 1)) add(i + 2, 0, 1, dp[i][2][1]);

		if(con(i + 2, i) && con(i, i + 3) && con(i + 4, i + 1)) add(i + 3, 0, 1, dp[i][2][1]);
		if(con(i, i + 2) && con(i + 3, i) && con(i + 1, i + 4)) add(i + 3, 1, 0, dp[i][1][2]);
	}
	lint ret = 0;
	for(int i=max(2, n-7); i<=n-2; i++){
		for(int j=0; j<3; j++){
			for(int k=0; k<3; k++){
				ret += dp[i][j][k] * solve(k + i, j + i, n - i + 1);
			}
		}
	}
	cout << ret % mod << endl;
}