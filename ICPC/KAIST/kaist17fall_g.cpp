#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
const int MAXN = 1005;
using lint = long long;
using pi = pair<int, int>;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int n, m;
char str[55][55];
bool chk[55][55][4][240];
bool ban[55][55][240];

void Do(int x1, int y1, int x2, int y2, int t){
	for(int i=0; i<4; i++){
		if(x1 + dx[i] == x2 && y1 + dy[i] == y2){
			chk[x1][y1][i][t%240] = 1;
			chk[x2][y2][i^2][t%240] = 1;
		}
	}
}

struct node{
	int x, y, t, dist;
};

int dis[55][55][240];
queue<node> que;

void enque(node t){
	if(dis[t.x][t.y][t.t] > t.dist){
		dis[t.x][t.y][t.t] = t.dist;
		que.push(t);
	}
}

int main(){
	cin >> n >> m;
	n++; m++;
	for(int i=0; i<n; i++) cin >> str[i];
	int q; cin >> q;
	while(q--){
		int x, y, d; cin >> d >> x >> y;
		for(int i=0; i<240; i+=d*4){
			for(int j=0; j<d; j++){
				ban[x][y+j][i+j] = 1;
				ban[x+j][y+d][i+j+d] = 1;
				ban[x+d][y+d-j][i+j+2*d] = 1;
				ban[x+d-j][y][i+j+3*d] = 1;
				Do(x, y + j, x, y + j + 1, i + j);
				Do(x + j, y + d, x + j + 1, y + d, i + j + d);
				Do(x + d, y + d - j - 1, x + d, y + d - j, i + j + 2 * d);
				Do(x + d - j - 1, y, x + d - j, y, i + j + 3 * d);
			}
		}
	}
	memset(dis, 0x3f, sizeof(dis));
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] == 'S') enque({i, j, 0, 0});
		}
	}
	auto ok = [&](int x, int y){
		return x >= 0 && x < n && y >= 0 && y < m && str[x][y] != '#';
	};
	while(!que.empty()){
		auto x = que.front(); que.pop();
		if(str[x.x][x.y] == 'E'){
			cout << x.dist << endl;
			return 0;
		}
		if(!ban[x.x][x.y][(x.t+1)%240]){
			enque({x.x, x.y, (x.t + 1) % 240, x.dist + 1});
		}
		for(int i=0; i<4; i++){
			if(!ok(x.x + dx[i], x.y + dy[i])) continue;
			if(ban[x.x + dx[i]][x.y + dy[i]][(x.t + 1)%240] || chk[x.x][x.y][i][x.t]) continue;
			enque({x.x + dx[i], x.y + dy[i], (x.t + 1)%240, x.dist + 1});
		}
	}
	cout << "INF" << endl;
}

