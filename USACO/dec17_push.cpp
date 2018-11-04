#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXH = 1505;
const int MAXN = 2350005;
const int dx[4] = { 1, 0, -1, 0 };
const int dy[4] = { 0, 1, 0, -1 };

int n, m, V;
int idx[MAXH][MAXH];
char str[MAXH][MAXH];
int route[MAXH][MAXH][4][4];

vector<int> gph[MAXN];
int low[MAXN], dfn[MAXN], piv;
int X[MAXN], Y[MAXN];

bool ok(int x, int y) {
	return x >= 0 && y >= 0 && x < n && y < m && str[x][y] == '.';
}

void dfs(int x, int p) {
	dfn[x] = low[x] = ++piv;
	vector<pi> special;
	for(auto &i : gph[x]) {
		if(i == p) continue;
		if(!dfn[i]) {
			int curv = piv;
			dfs(i, x);
			low[x] = min(low[x], low[i]);
			if(low[i] >= dfn[x]) {
				special.emplace_back(curv + 1, piv);
			}
		}
		else low[x] = min(low[x], dfn[i]);
	}
	int equiv_class[4] = { 0, 0, 0, 0 };
	for(int j = 0; j < 4; j++) {
		if(!ok(X[x] + dx[j], Y[x] + dy[j])) {
			equiv_class[j] = -1;
			continue;
		}
		equiv_class[j] = 100;
		int clock = 0;
		for(auto &k : special) {
			int v = idx[X[x] + dx[j]][Y[x] + dy[j]];
			if(k.first <= dfn[v] && dfn[v] <= k.second) {
				equiv_class[j] = clock;
			}
			clock++;
		}
	}
	for(int j = 0; j < 4; j++) {
		for(int k = 0; k < 4; k++) {
			if(~equiv_class[j] && ~equiv_class[k] && equiv_class[j] == equiv_class[k]) {
				route[X[x]][Y[x]][j][k] = 1;
			}
		}
	}
}

struct node {
	int x, y, d, dist;
	bool operator<(const node &n)const {
		return dist > n.dist;
	}
};

priority_queue<node> que;
int dis[MAXH][MAXH][4];
int vis[MAXH][MAXH];

void ff(int x, int y) {
	if(vis[x][y]) return;
	vis[x][y] = 1;
	for(int i = 0; i < 4; i++) {
		if(ok(x + dx[i], y + dy[i])) {
			ff(x + dx[i], y + dy[i]);
		}
	}
}

void enqueue(int x, int y, int dir, int d) {
	if(dis[x][y][dir] > d) {
		dis[x][y][dir] = d;
		que.push({ x, y, dir, d });
	}
}

int q;

int main() {
    cin >> n >> m >> q;
    pi st, stp;
    for(int i = 0; i < n; i++) {
    	scanf("%s", str[i]);
        for(int j = 0; j < m; j++) {
        	if(str[i][j] == 'A'){
        		st = pi(i, j);
        		str[i][j] = '.';
			}
			if(str[i][j] == 'B'){
        		stp = pi(i, j);
        		str[i][j] = '.';
			}
            if(str[i][j] == '.') {
                idx[i][j] = ++V;
				X[V] = i, Y[V] = j;
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
			if(!ok(i, j)) continue;
            for(int k = 0; k < 4; k++) {
                if(ok(i + dx[k], j + dy[k])) {
                    int l = idx[i][j];
                    int r = idx[i + dx[k]][j + dy[k]];
                    gph[l].push_back(r);
                }
            }
        }
    }
	memset(dis, 0x3f, sizeof(dis));
	int R = idx[st.first][st.second];
	dfs(R, -1);
	str[stp.first][stp.second] = '#';
	ff(st.first, st.second);
	str[stp.first][stp.second] = '.';
	for(int i = 0; i < 4; i++) {
		if(ok(stp.first + dx[i], stp.second + dy[i])){
			int w = vis[stp.first + dx[i]][stp.second + dy[i]];
			if(w) enqueue(stp.first, stp.second, i, 0);
		}
	}
	while(!que.empty()) {
		auto x = que.top();
		que.pop();
		if(dis[x.x][x.y][x.d] != x.dist) continue;
		for(int i = 0; i < 4; i++) {
			if(route[x.x][x.y][x.d][i]) {
				enqueue(x.x, x.y, i, x.dist);
			}
		}
		if(ok(x.x + dx[x.d ^ 2], x.y + dy[x.d ^ 2])) {
			enqueue(x.x + dx[x.d ^ 2],
					x.y + dy[x.d ^ 2],
					x.d, x.dist + 1);
		}
	}
	while(q--){
		pi edp; scanf("%d %d",&edp.first,&edp.second);
		edp.first--;
		edp.second--;
		if(str[edp.first][edp.second] == '#'){
			puts("NO");
			continue;
		}
		if(stp == edp){
			puts("YES");
			continue;
		}
		int ret = 1e9;
		for(int i = 0; i < 4; i++) {
			if(ok(edp.first + dx[i], edp.second + dy[i])) {
				ret = min(ret, dis[edp.first][edp.second][i]);
			}
		}
		if(ret > 1e8) puts("NO");
		else puts("YES");
	}
}
