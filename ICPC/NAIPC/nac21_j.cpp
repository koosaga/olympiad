#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55;
using pi = pair<int, int>;
using lint = long long;

int n, m;
int adj[26][26];
int dp[26][105];

int f(int x, int y){
	if(y == 1) return 0;
	if(y == 2) return adj[x][x];
	if(~dp[x][y]) return dp[x][y];
	lint ret = 1e9;
	for(int i = 0; i < 26; i++){
		ret = min(ret, 1ll * adj[x][i] + adj[i][x] + f(i, y-2));
	}
	return dp[x][y] = ret;
}

int main(){
	cin >> n >> m;
	memset(adj, 0x3f, sizeof(adj));
	memset(dp, -1, sizeof(dp));
	for(int i = 0; i < n; i++){
		string s; cin >> s;
		int z; cin >> z;
		adj[s[0]-'a'][s[1]-'a'] = z;
	}
	int ret = 1e9;
	for(int i = 0; i < 26; i++){
		ret = min(ret, f(i, m));
	}
	if(ret > 1e8) ret = -1;
	cout << ret << endl;
}
