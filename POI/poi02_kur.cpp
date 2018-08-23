#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1005;

vector<pi> gph[MAXN];
bool vis[MAXN][2005];

int n, m, a, b;

void dfs(int x, int y){
	vis[x][y] = 1;
	for(auto &i : gph[x]){
		if(i.second + y <= b && !vis[i.first][i.second + y]){
			dfs(i.first, i.second + y);
		}
	}
}

int main(){
	cin >> n >> m >> a;
	for(int i=0; i<a; i++){
		int s, e;
		cin >> s >> e;
		gph[s].push_back(pi(e, 0));
	}
	cin >> a;
	for(int i=0; i<a; i++){
		int s, e, x;
		cin >> s >> e >> x;
		gph[s].push_back(pi(e, x));
	}
	cin >> a >> b;
	dfs(a, 0);
	int ans = -1e9;
	for(int i=1; i<=m; i++){
		for(int j=b; j>=0; j--){
			if(vis[i][j]){
				ans = max(ans, j);
				break;
			}
		}
	}
	cout << b - ans;
}

