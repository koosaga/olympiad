#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 100005;
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x]== x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

struct point{
	int x, y, c, d;
};

int vis[2005][2005], dis[2005][2005];
queue<point> que;

int n, k;

bool ok(int x, int y){
	return x >= 1 && x <= n && y >= 1 && y <= n;
}

void enqueue(int x, int y, int c, int d){
	vis[x][y] = c;
	dis[x][y] = d;
	que.push({x, y, c, d});
}

vector<pi> v[4005];

int main(){
	scanf("%d %d",&n,&k);
	disj.init(k);
	for(int i=1; i<=k; i++){
		int x, y;
		scanf("%d%d",&x,&y);
		enqueue(x, y, i, 0);
	}
	int t = 0;
	while(!que.empty()){
		auto x = que.front();
		que.pop();
		for(int i=0; i<4; i++){
			if(ok(x.x + dx[i], x.y + dy[i])){
				if(!vis[x.x + dx[i]][x.y + dy[i]]) enqueue(x.x + dx[i], x.y + dy[i], x.c, x.d + 1);
			}
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(j < n){
				int t = max(dis[i][j], dis[i][j+1]);
				if(vis[i][j] != vis[i][j+1]) v[t].push_back({vis[i][j], vis[i][j+1]});
			}
			if(i < n){
				int t = max(dis[i][j], dis[i+1][j]);
				if(vis[i][j] != vis[i+1][j]) v[t].push_back({vis[i][j], vis[i+1][j]});
			}
		}
	}
	int ans = 0;
	for(int i=0; i<=n; i++){
		for(auto &j : v[i]) if(disj.uni(j.first, j.second)) ans = i;
	}
	cout << ans;
}
