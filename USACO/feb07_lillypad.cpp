#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
const int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};

int n, m, a[31][31];
int cmp[31][31][2];
int dis[31][31][2];
bool vis[31][31][2];
lint cnt[31][31][2];
int nxt[31][31];

bool ok(int x, int y){
	return x >= 0 && x < n && y >= 0 && y < m && a[x][y] != 2;
}

void dfs(int x, int y, int z, int d, lint add){
	if(dis[x][y][z] < d) return;
	if(vis[x][y][z]) return;
	vis[x][y][z] = 1;
	dis[x][y][z] = d;
	cnt[x][y][z] += add;
	if(z == 0){
		if(a[x][y]) dfs(x, y, 1, d, add);
		else nxt[x][y] = 1;
	}
	else{
		for(int i=0; i<8; i++){
			if(ok(x + dx[i], y + dy[i])) dfs(x+dx[i], y+dy[i], 0, d, add);
		}
	}
}

int main(){
	cin >> n >> m;
	memset(dis, 0x3f, sizeof(dis));
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			cin >> a[i][j];
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(a[i][j] == 3) dfs(i, j, 0, 0, 1);
		}
	}
	int stp = 0;
	while(1){
		vector<pi> v;
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				if(nxt[i][j]) v.push_back(pi(i, j));
			}
		}
		memset(nxt, 0, sizeof(nxt));
		stp++;
		if(v.empty()) break;
		for(auto &i : v){
			memset(vis, 0, sizeof(vis));
			dfs(i.first, i.second, 1, stp, cnt[i.first][i.second][0]);
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(a[i][j] == 4){
				if(dis[i][j][1] > 1e9){
					cout << -1;
					return 0;
				}
				cout << dis[i][j][1] << endl << cnt[i][j][1];
				return 0;
			}
		}
	}
}
