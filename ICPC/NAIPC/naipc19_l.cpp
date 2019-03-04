#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using llf = long double;
using lint = long long;
const int MAXN = 100005;
const int MAXM = 100005;

struct bpm{
	vector<int> gph[MAXN];
	int dis[MAXN], l[MAXN], r[MAXN], vis[MAXN];
	void clear(){
		for(int i=0; i<MAXN; i++) gph[i].clear();
	}
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
			for(int i=0; i<n; i++){
				if(l[i] == -1 && dfs(i)) ret++;
			}
		}
		return ret;
	}
	vector<int> free(int n){
		bool vis[MAXN] = {};
		queue<int> que;
		for(int i=0; i<n; i++){
			if(l[i] == -1){
				vis[i] = 1;
				que.push(i);
			}
		}
		while(!que.empty()){
			int x = que.front();
			que.pop();
			for(auto &i : gph[x]){
				if(r[i] != -1 && !vis[r[i]]){
					que.push(r[i]);
					vis[r[i]] = 1;
				}
			}
		}
		vector<int> ans;
		for(int i=0; i<n; i++) if(vis[i]) ans.push_back(i);
		return ans;
	}
}bpm;

int n, m;
pi a[MAXN];
int chk[MAXN];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
		a[i].first--;
		a[i].second--;
		bpm.add_edge(a[i].first, a[i].second);
	}
	int dap = n - 1 - bpm.match(n);
	printf("%d\n", dap);
	if(dap == 0){
		return 0;
	}
	{
		vector<int> ans = bpm.free(n);
		for(auto &i : ans) chk[i] = 1;
		bpm.clear();
		for(int i=0; i<m; i++){
			bpm.add_edge(a[i].second, a[i].first);
		}
		bpm.match(n);
		ans = bpm.free(n);
		for(auto &i : ans) chk[i] = 1;
		for(int i=0; i<n; i++) if(chk[i]) printf("%d ", i + 1);
	}
}
