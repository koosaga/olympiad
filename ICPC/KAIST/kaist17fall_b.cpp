#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 1000005;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

struct mf{
	struct edg{int pos, cap, rev;};
	vector<edg> gph[MAXN];
	void clear(){ for(int i=0; i<MAXN; i++) gph[i].clear(); }
	void add_edge(int s, int e, int x){
		gph[s].push_back({e, x, (int)gph[e].size()});
		gph[e].push_back({s, 0, (int)gph[s].size() - 1});
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
				int w = dfs(e.pos, sink, min(f, e.cap));
				if(w){
					gph[x][pnt[x]].cap -= w;
					gph[e.pos][e.rev].cap += w;
					return w;
				}
			}
		}
		return 0;
	}
	int match(int src, int sink){
		int ret = 0;
		while(bfs(src, sink)){
			int r;
			while((r = dfs(src, sink, 2e9))) ret += r;
		}
		return ret;
	}
}mf;

int n, m, k, c;
int idx[105][105];
int chk[105][105];

vector<int> gph[105];
vector<pi> sn, sk;

int main(){
	cin >> n >> m >> k;
	for(int i=0; i<k; i++){
		int x, y;
		cin >> x >> y;
		x--;
		y--;
		chk[x][y] = -1;
	}
	int v = 0;
	for(int i=0; i<k; i++){
		int x, y;
		cin >> x >> y;
		x--;
		y--;
		sk.push_back(pi(x, y));
		chk[x][y] = ++v;
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(chk[i][j] >= 1) continue;
			sn.push_back(pi(i, j));
			idx[i][j] = ++c;
		}
	}
	auto ok = [&](int x, int y){
		return x >= 0 && x< n && y >= 0 &&y < m;
	};
	int src = 0, snk = sk.size() * 2 + 1;
	for(int i=1; i<=sk.size(); i++){
		mf.add_edge(i, sk.size() + i, 1);
		mf.add_edge(sk.size() + i, snk, 1);
	}
	int ptr = snk + 1;
	int itr = 0;
	int ans = 0;
	vector<int> prv(sn.size());
	for(int j=0; j<prv.size(); j++){
		prv[j] = ptr + j;
		if(chk[sn[j].first][sn[j].second] == -1){
			mf.add_edge(0, ptr + j, 1);
		}
	}
	ptr += prv.size();
	while(clock() < 0.95 * CLOCKS_PER_SEC){
		vector<int> nxt;
		for(int j=0; j<sn.size(); j++){
			mf.add_edge(prv[j], ptr + j, 1);
			mf.add_edge(ptr + j, ptr + j + sn.size(), 1);
			nxt.push_back(ptr + j + sn.size());
		}
		for(int j=0; j<sn.size(); j++){
			for(int k=0; k<4; k++){
				if(ok(sn[j].first + dx[k], sn[j].second + dy[k])){
					int x, y;
					tie(x, y) = sn[j];
					if(chk[x + dx[k]][y + dy[k]] <= 0){
						auto ppap = lower_bound(sn.begin(), sn.end(), pi(x + dx[k], y + dy[k])) - sn.begin();
						mf.add_edge(prv[j], nxt[ppap] - sn.size(), 1); 
					}
					else{
						mf.add_edge(prv[j], chk[sn[j].first + dx[k]][sn[j].second + dy[k]], 1);
					}
				}
			}
		}
		prv = nxt;
		ptr += 2 * sn.size();
		itr++;
		ans += mf.match(0, snk);
	//	cout <<ans <<endl;
		if(ans == k){
			cout << itr;
			return 0;
		}
	}
	cout << -1;
	return 0;
}