#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
#define sz(v) int((v).size())
const int MAXN = 5005;
const int MAXM = 5005;

struct bpm{
	vector<int> gph[MAXN];
	int dis[MAXN], l[MAXN], r[MAXM], vis[MAXN];
	void clear(){ for(int i=0; i<MAXN; i++) gph[i].clear();	}
	void add_edge(int l, int r){ gph[l].push_back(r); }
	bool bfs(int n){
		queue<int> que;
		bool ok = 0;
		memset(dis, 0, sizeof(dis));
		for(int i=0; i<n; i++){
			if(l[i] == -1 && !dis[i]){
				que.push(i);
				dis[i] = 1;
			}
		}
		while(!que.empty()){
			int x = que.front();
			que.pop();
			for(auto &i : gph[x]){
				if(r[i] == -1) ok = 1;
				else if(!dis[r[i]]){
					dis[r[i]] = dis[x] + 1;
					que.push(r[i]);
				}
			}
		}
		return ok;
	}
	bool dfs(int x){
		if(vis[x]) return 0;
		vis[x] = 1;
		for(auto &i : gph[x]){
			if(r[i] == -1 || (!vis[r[i]] && dis[r[i]] == dis[x] + 1 && dfs(r[i]))){
				l[x] = i; r[i] = x;
				return 1;
			}
		}
		return 0;
	}
	int match(int n){
		memset(l, -1, sizeof(l));
		memset(r, -1, sizeof(r));
		int ret = 0;
		while(bfs(n)){
			memset(vis, 0, sizeof(vis));
			for(int i=0; i<n; i++) if(l[i] == -1 && dfs(i)) ret++;
		}
		return ret;
	}
}bpm;
const int MAXV = 105;

int n;
int adj[MAXV][MAXV];
int mid[MAXV][MAXV];
int nxt[MAXN], ind[MAXN];

void trace_path(vector<int> &v, int l, int r){
	if(!mid[l][r]) return;
	trace_path(v, l, mid[l][r]);
	v.push_back(mid[l][r]);
	trace_path(v, mid[l][r], r);
}

vector<pi> drog;
int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		int x; scanf("%d",&x);
		for(int j=0; j<x; j++){
			int y; scanf("%d",&y);
			drog.emplace_back(i, y);
			adj[i][y] = 1;
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			for(int k=1; k<=n; k++){
				if(adj[j][i] && adj[i][k] && !adj[j][k]){
					adj[j][k] = 1;
					mid[j][k] = i;
				}
			}
		}
	}
	for(int i=0; i<sz(drog); i++){
		for(int j=0; j<sz(drog); j++){
			if(drog[i].second == drog[j].first || adj[drog[i].second][drog[j].first]){
				bpm.add_edge(i, j);
			}
		}
	}
	int ret = drog.size() - bpm.match(sz(drog));
	memset(nxt, -1, sizeof(nxt));
	for(int i=0; i<sz(drog); i++){
		if(~bpm.l[i]){
			nxt[i] = bpm.l[i];
			ind[nxt[i]] = 1;
		}
	}
	vector<vector<int>> pths;
	for(int i=0; i<sz(drog); i++){
		if(!ind[i]){
			vector<int> w = {drog[i].first, drog[i].second};
			for(int j=i; ~nxt[j]; j=nxt[j]){
				if(drog[j].second != drog[nxt[j]].first){
					trace_path(w, drog[j].second, drog[nxt[j]].first);
					w.push_back(drog[nxt[j]].first);
				}
				w.push_back(drog[nxt[j]].second);
			}
			pths.push_back(w);
		}
	}
	assert(ret == pths.size());
	cout << pths.size() << endl;
	for(auto &i : pths){
		for(auto &j : i) printf("%d ", j);
		puts("");
	}
}
