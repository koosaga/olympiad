#include <bits/stdc++.h>
using namespace std;
typedef long long lint;

const int MAXN = 5005;
const int MAXM = 5005;

struct bpm{
	vector<int> gph[MAXN], gph2[MAXM];
	int dis[MAXN], l[MAXN], r[MAXN], vis[MAXM];

	void clear(){
		for(int i=0; i<MAXN; i++){
			gph[i].clear();
		}
		for(int i=0; i<MAXM; i++){
			gph2[i].clear();
		}
	}

	void add_edge(int l, int r){
		gph[l].push_back(r);
		gph2[r].push_back(l);
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

	bool dfsl(int x){
		if(l[x] == -1) return 1;
		vis[x] = 1;
		for(auto &i : gph2[l[x]]){
			if(!vis[i] && dfsl(i)) return 1;
		}
		return 0;
	}
	
	bool dfsr(int x){
		if(r[x] == -1) return 1;
		vis[x] = 1;
		for(auto &i : gph[r[x]]){
			if(!vis[i] && dfsr(i)) return 1;
		}
		return 0;
	}
}bpm;

int idx[105][105], l, r;
char str[105][105];
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

int main(){
	while(1){
		int n, m;
		scanf("%d %d",&n,&m);
		if(n + m == 0) break;
		bpm.clear();
		l = r = 0;
		for(int i=0; i<n; i++){
			scanf("%s", str[i]);
			for(int j=0; j<m; j++){
				if(str[i][j] != 'X'){
					if(i%2 == j%2) idx[i][j] = l++;
					else idx[i][j] = r++;
				}
			}
		}
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				if(i%2 == j%2 && str[i][j] != 'X'){
					for(int k=0; k<4; k++){
						if(i + dx[k] < 0 || j + dy[k] < 0 || i + dx[k] >= n || j + dy[k] >= m){
							continue;
						}
						if(str[i+dx[k]][j+dy[k]] == 'X') continue;
						bpm.add_edge(idx[i][j], idx[i+dx[k]][j+dy[k]]);
					}
				}
			}
		}
		bpm.match(l);
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++){
				if(str[i][j] == 'X'){
					putchar('X');
				}
				else{
					memset(bpm.vis, 0, sizeof(bpm.vis));
					if(i%2 == j%2 && bpm.dfsl(idx[i][j])) putchar('B');
					else if(i%2 != j%2 && bpm.dfsr(idx[i][j])) putchar('B');
					else putchar('A');
				}
			}
			puts("");
		}
		puts("");
	}
}
