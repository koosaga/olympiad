#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, lint> pi;

const int MAXN = 10005;
const int MAXM = 10005;

struct bpm{
	vector<int> gph[MAXN];
	int dis[MAXN], l[MAXN], r[MAXN], vis[MAXM];

	void clear(){
		for(int i=0; i<MAXN; i++){
			gph[i].clear();
		}
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
			for(int i=0; i<n; i++){
				if(l[i] == -1 && dfs(i)) ret++;
			}
		}
		return ret;
	} 

	bool chk[MAXN + MAXM];

	void rdfs(int x, int n){
		if(chk[x]) return;
		chk[x] = 1;
		for(int idx=0; idx<gph[x].size(); idx++){
			int i = gph[x][idx];
			chk[i + n] = 1;
			rdfs(r[i], n);
		}
	}

	vector<int> getcover(int n, int m){
		match(n);
		memset(chk, 0, sizeof(chk));
		for(int i=0; i<n; i++){
			if(l[i] == -1) rdfs(i, n);
		}
		vector<int> v;
		for(int i=0; i<n; i++){
			if(!chk[i]) v.push_back(i);
		}
		for(int i=n; i<n+m; i++){
			if(chk[i]) v.push_back(i);
		}
		return v;
	}
}bpm;

int n, m, k;
vector<int> rl, rr;
vector<int> gph[20005];
bool vis[20005];

void dfs(int x){
	if(vis[x]) return;
	vis[x] = 1;
	for(auto &i : gph[x]) dfs(i);
}

int main(){
	cin >> n >> m >> k;
	for(int i=0; i<k; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		bpm.add_edge(s-1, e-1);
	}
	bpm.match(n);
	for(int i=0; i<n; i++){
		for(auto &j : bpm.gph[i]){
			if(j == bpm.l[i]){
				gph[j + n].push_back(i);
			}
			else{
				gph[i].push_back(j + n);
			}
		}
	}
	for(int i=0; i<n; i++){
		if(bpm.l[i] == -1){
			dfs(i);
		}
	}
	for(int i=0; i<n; i++){
		if(bpm.l[i] != -1 && !vis[bpm.l[i] + n]) rl.push_back(i);
	}
	for(int i=0; i<n+m; i++) gph[i].clear();
	memset(vis, 0, sizeof(vis));
	for(int i=0; i<n; i++){
		for(auto &j : bpm.gph[i]){
			if(j == bpm.l[i]){
				gph[i].push_back(j + n);
			}
			else{
				gph[j + n].push_back(i);
			}
		}
	}
	for(int i=0; i<m; i++){
		if(bpm.r[i] == -1){
			dfs(i + n);
		}
	}
	for(int i=0; i<m; i++){
		if(bpm.r[i] != -1 && !vis[bpm.r[i]]) rr.push_back(i);
	}
	sort(rl.begin(), rl.end());
	sort(rr.begin(), rr.end());
	for(auto &i : rl) printf("%d\n", i+1);
	for(auto &i : rr) printf("%d\n", i+1);
}
