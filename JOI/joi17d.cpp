#include <bits/stdc++.h>
typedef long long lint;
typedef long double llf;
using namespace std;
typedef pair<int, int> pi;
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

int n, m;
lint a, b, c;
int dis[505][505];

bool ok(int x, int y){
	return x >= 0 && x <= n && y >= 0 && y <= m;
}

struct node{
	int x, y, typ;
	lint dis;
	bool operator<(const node &c)const{
		return dis > c.dis;
	}
};

priority_queue<node> pq;
lint dist[505][505][5];

void enqueue(int x, int y, int t, lint d){
	if(!ok(x, y)) return;
	if(dist[x][y][t] > d){
		dist[x][y][t] = d;
		pq.push({x, y, t, d});
	}
}

int main(){
	memset(dis, 0x3f, sizeof(dis));
	int t;
	cin >> n >> m >> a >> b >> c >> t;
	queue<pi> que;
	pi st, ed;
	for(int i=0; i<t; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		if(i == 0) st = pi(x, y);
		if(i == t-1) ed = pi(x, y);
		dis[x][y] = 0;
		que.push(pi(x, y));
	}
	while(!que.empty()){
		auto x = que.front();
		que.pop();
		for(int i=0; i<4; i++){
			if(ok(x.first + dx[i], x.second + dy[i]) && dis[x.first + dx[i]][x.second + dy[i]] > 1e9){
				dis[x.first + dx[i]][x.second + dy[i]] = dis[x.first][x.second] + 1;
				que.push(pi(x.first + dx[i], x.second + dy[i]));
			}
		}
	}
	memset(dist, 0x3f, sizeof(dist));
	enqueue(st.first, st.second, 4, 0);
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(dist[x.x][x.y][x.typ] != x.dis) continue;
		if(x.typ == 4){
			for(int i=0; i<4; i++){
				enqueue(x.x + dx[i], x.y + dy[i], 4, x.dis + c);
				enqueue(x.x, x.y, i, x.dis + b);
			}
		}
		else{
			enqueue(x.x + dx[x.typ], x.y + dy[x.typ], x.typ, x.dis + a);
			enqueue(x.x, x.y, 4, x.dis + dis[x.x][x.y] * c);
		}
	}
	cout << dist[ed.first][ed.second][4];
}

