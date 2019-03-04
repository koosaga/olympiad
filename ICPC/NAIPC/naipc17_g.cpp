#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

const int MAXN = 100005 + 6 * 6 * 51 * 51;

struct maxflow{
	struct edg{int pos;
		lint cap;
		int rev;};
	vector<edg> gph[MAXN];

	void clear(){
		for(int i=0; i<MAXN; i++) gph[i].clear();
	}
	void add_edge(int s, int e, lint x){
		gph[s].push_back({e, x, (int)gph[e].size()});
		gph[e].push_back({s, 0, (int)gph[s].size()-1});
	}

	int dis[MAXN], pnt[MAXN];

	bool bfs(int src, int sink){
		memset(dis, 0, sizeof(dis));
		memset(pnt, 0, sizeof(pnt));
		queue<int> que;
		que.push(src);
		dis[src] = 1;
		while(!que.empty()){
			int x = que.front();
			que.pop();
			for(auto &e : gph[x]){
				if(e.cap > 0 && !dis[e.pos]){
					dis[e.pos] = dis[x] + 1;
					que.push(e.pos);
				}
			}
		}
		return dis[sink] > 0;
	}

	int dfs(int x, int sink, int f){
		if(x == sink) return f;
		for(; pnt[x] < gph[x].size(); pnt[x]++){
			edg e = gph[x][pnt[x]];
			if(e.cap > 0 && dis[e.pos] == dis[x] + 1){
				int w = dfs(e.pos, sink, (int)min(1ll * f, e.cap));
				if(w){
					gph[x][pnt[x]].cap -= w;
					gph[e.pos][e.rev].cap += w;
					return w;
				}
			}
		}
		return 0;
	}
	lint match(int src, int sink){
		lint ret = 0;
		while(bfs(src, sink)){
			int r;
			while((r = dfs(src, sink, 2e9))) ret += r;
		}
		return ret;
	}
}mf;

int n, m, k, a[51][51];
int idx[6][6][51][51], p;

int main(){
	cin >> n >> m >> k;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			cin >> a[i][j];
			idx[0][0][i][j] = ++p;
			mf.add_edge(0, idx[0][0][i][j], a[i][j]);
		}
	}
	for(int i=0; i<6; i++){
		for(int j=0; j<6; j++){
			if(i + j == 0) continue;
			for(int k=0; k<n; k++){
				for(int l=0; l<m; l++){
					if(k + (1<<i) - 1 >= n || l + (1<<j) - 1 >= m){
						continue;
					}
					idx[i][j][k][l] = ++p;
					if(j > 0){
						mf.add_edge(idx[i][j-1][k][l], idx[i][j][k][l], 1e18);
						mf.add_edge(idx[i][j-1][k][l + (1<<(j-1))], idx[i][j][k][l], 1e18);
					}
					else{
						mf.add_edge(idx[i-1][j][k][l], idx[i][j][k][l], 1e18);
						mf.add_edge(idx[i-1][j][k+(1<<(i-1))][l], idx[i][j][k][l], 1e18);
					}
				}
			}
		}
	}
	for(int i=1; i<=k; i++){
		int sx, ex, sy, ey, v;
		cin >> sx >> ex >> sy >> ey >> v;
		sx--, ex--, sy--, ey--;
		if(v == 0) continue;
		int xp = 0, yp = 0;
		for(int j=0; j<6; j++){
			if(ex - sx + 1 >= (1<<j)) xp = j;
			if(ey - sy + 1 >= (1<<j)) yp = j;
		}
		mf.add_edge(idx[xp][yp][sx][sy], p + i, 1e9);
		mf.add_edge(idx[xp][yp][sx][ey-(1<<yp)+1], p+i, 1e9);
		mf.add_edge(idx[xp][yp][ex-(1<<xp)+1][sy], p+i, 1e9);
		mf.add_edge(idx[xp][yp][ex-(1<<xp)+1][ey-(1<<yp)+1], p+i, 1e9);
		mf.add_edge(p+i, p+k+1, v);
	}
	cout << mf.match(0, p+k+1);
}
