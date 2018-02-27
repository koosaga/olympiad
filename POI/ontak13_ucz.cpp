#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2005;

struct bpm{
	vector<int> gph[MAXN];
	int dis[MAXN], l[MAXN], r[MAXN], vis[MAXN];
	void add_edge(int l, int r){
		gph[l].push_back(r);
	}
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
		for(auto &i : gph[x]){
			if(r[i] == -1 || (!vis[r[i]] && dis[r[i]] == dis[x] + 1 && dfs(r[i]))){
				vis[r[i]] = 1;
				l[x] = i;
				r[i] = x;
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
	int rt;
	bool dfsa(int x){
		if(vis[x]) return false;
		vis[x] = 1;
		for(auto &i : gph[x]){
			if(i == rt){
				l[x] = i;
				r[i] = x;
				return true;
			}
			else if(dfsa(r[i])){
				l[x] = i;
				r[i] = x;
				return true;
			}
		}
		return false;
	}
	void tryit(int p){
		if(l[p] != p){
			gph[p].erase(find(gph[p].begin(), gph[p].end(), p));
			return;
		}
		gph[p].erase(find(gph[p].begin(), gph[p].end(), p));
		rt = p;
		memset(vis, 0, sizeof(vis));
		if(!dfsa(p)){
			gph[p].push_back(p);
		}
	}
}bpm;

int n;
vector<int> gph[MAXN];
bool vis[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		int x;
		scanf("%d",&x);
		gph[i].resize(x);
		for(auto &j : gph[i]) scanf("%d",&j), j--;
	}
	for(int i=0; i<n; i++){
		bpm.add_edge(i, i);
		for(auto &j : gph[i]) bpm.add_edge(i, j);
	}
	assert(bpm.match(n) == n);
	for(int i=0; i<n; i++){
		bpm.tryit(i);
	}
	vector<vector<int>> ans;
	for(int i=0; i<n; i++){
		if(bpm.r[i] != i && !vis[i]){
			vector<int> pos;
			for(int j=i; !vis[j]; j = bpm.l[j]){
				pos.push_back(j + 1);
				vis[j] = 1;
			}
			ans.push_back(pos);
		}
	}
	printf("%d\n", ans.size());
	for(auto &i : ans){
		printf("%d ", i.size());
		for(auto &j : i) printf("%d ", j);
	}
}
