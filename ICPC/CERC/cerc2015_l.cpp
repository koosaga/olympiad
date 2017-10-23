#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

char str[105][105];
int n, m, q, lab[105][105], idx;

bool ok(int x, int y){
	return x >= 0 && y >= 0 && x < n && y < m && !lab[x][y] && str[x][y] == '.';
}

void dfs(int x, int y){
	lab[x][y] = idx;
	for(int i=0; i<4; i++){
		if(ok(x + dx[i], y + dy[i])) dfs(x + dx[i], y + dy[i]);
	}
}

struct edg{
	int pos, dx, dy;
};

int root[5050], depx[5050], depy[5050];
vector<pi> cycle[5050];
vector<edg> gph[5050];

void add_edge(int x, int y, int dx, int dy){
	if(x == 0 || y == 0) return;
	gph[x].push_back({y, -dx, -dy});
	gph[y].push_back({x, dx, dy});
}

void dfs2(int x, int r){
	root[x] = r;
	for(auto &i : gph[x]){
		if(root[i.pos]){
			int dx = depx[x] - depx[i.pos] + i.dx;
			int dy = depy[x] - depy[i.pos] + i.dy;
			if(dx != 0 || dy != 0) cycle[r].push_back(pi(dx, dy));
		}
		else{
			depx[i.pos] = depx[x] + i.dx;
			depy[i.pos] = depy[x] + i.dy;
			dfs2(i.pos, r);
		}
	}
}

int gcd(int x, int y){
	return y ? gcd(y, x%y) : x;
}

lint ccw(pi a, pi b){
	return 1ll * a.first * b.second - 1ll * b.first * a.second;
}

int main(){
	cin >> n >> m;
	for(int i=0; i<n; i++){
		scanf("%s", str[i]);
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(ok(i, j)){
				idx++;
				dfs(i, j);
			}
		}
	}
	for(int i=0; i<n; i++){
		add_edge(lab[i][0], lab[i][m-1], 0, 1);
	}
	for(int i=0; i<m; i++){
		add_edge(lab[0][i], lab[n-1][i], 1, 0);
	}
	for(int i=1; i<=idx; i++){
		if(!root[i]){
			dfs2(i, i);
			if(cycle[i].empty()) continue; // Case 1. no cycle
			int sz = 0;
			for(int j=1; j<cycle[i].size(); j++){
				if(ccw(cycle[i][j-1], cycle[i][j]) != 0) sz = 2;
			}
			if(sz == 2){
				cycle[i].clear();
				cycle[i].push_back(pi(0, 1));
				cycle[i].push_back(pi(1, 0));
				continue;
			}
			int l = 0;
			for(auto &j : cycle[i]){
				l = gcd(l, abs(j.first) + abs(j.second));
			}
			while(cycle[i].size() > 1) cycle[i].pop_back();
			int sc = abs(cycle[i][0].first) + abs(cycle[i][0].second);
			sc /= l;
			cycle[i][0].first /= sc;
			cycle[i][0].second /= sc;
		}
	}
	cin >> q;
	for(int i=0; i<q; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		int mx = (x % n + n) % n;
		int my = (y % m + m) % m;
		int gx = (x - mx) / n;
		int gy = (y - my) / m;
		int group = lab[mx][my];
		if(root[lab[0][0]] != root[group]){
			puts("no");
			continue;
		}
		gx -= depx[group] - depx[lab[0][0]];
		gy -= depy[group] - depy[lab[0][0]];
		group = root[group];
		if(cycle[group].empty()){
			puts(gx == 0 && gy == 0 ? "yes" : "no");
			continue;
		}
		if(cycle[group].size() == 2){
			puts("yes");
			continue;
		}
		pi fr = cycle[group][0];
		if(ccw(pi(gx, gy), cycle[group][0]) == 0){
			int dx1 = abs(gx) + abs(gy);
			int dx2 = abs(cycle[group][0].first) + abs(cycle[group][0].second);
			if(dx1 % dx2 == 0) puts("yes");
			else puts("no");
		}
		else puts("no");
	}
}
