#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 205;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int n, m;
char str[MAXN][MAXN];
int dist[MAXN][MAXN];
int dis2[MAXN][MAXN];

bool ok(int x, int y){
	return x >= 0 && x < n && y >= 0 && y < m && str[x][y] != '#';
}

queue<pi> que;

void enqueue(int x, int y, int d){
	if(dist[x][y] > d){
		dist[x][y] = d;
		que.emplace(x, y);
	}
}


int main(){
	cin >> n >> m;
	for(int i=0; i<n; i++) cin >> str[i];
	memset(dist, 0x3f, sizeof(dist));
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] == '$'){
				enqueue(i, j, 0);
			}
		}
	}
	while(!que.empty()){
		auto x = que.front();
		que.pop();
		for(int i=0; i<4; i++){
			if(ok(x.first + dx[i], x.second + dy[i])){
				enqueue(x.first + dx[i], x.second + dy[i], dist[x.first][x.second] + 1);
			}
		}
	}
	memset(dis2, 0x3f, sizeof(dis2));
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] == '@'){
				dis2[i][j] = 0;
				que.emplace(i, j);
			}
		}
	}
	while(!que.empty()){
		auto x = que.front(); que.pop();
		for(int i=0; i<4; i++){
			if(ok(x.first + dx[i], x.second + dy[i])){
				if(dis2[x.first + dx[i]][x.second + dy[i]] > dis2[x.first][x.second] + 1 &&
					dist[x.first + dx[i]][x.second + dy[i]] > dis2[x.first][x.second] + 1){
					dis2[x.first + dx[i]][x.second + dy[i]] = dis2[x.first][x.second] + 1;
					que.emplace(x.first + dx[i], x.second + dy[i]);
				}
			}
		}
	}

	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] == '%'){
				if(dis2[i][j] > 1e7){
					puts("No");
				}
				else puts("Yes");
			}
		}
	}
}
