#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
 
vector<int> gph[100005];
int dist[100005], dist2[100005];
int n, m;
 
void bfs1(int r, int *d){
	queue<int> que;
	que.push(r);
	while(!que.empty()){
		int x = que.front();
		que.pop();
		for(auto &i : gph[x]){
			if(d[i] > d[x] + 1){
				d[i] = d[x] + 1;
				que.push(i);
			}
		}
	}
}
 
bool vis[100005];
vector<int> active[100005];
set<int> gph2[100005];
 
void bfs2(int r, int *d){
	for(int i=1; i<=n; i++){
		active[i] = gph[i];
		for(auto &j : gph[i]){
			gph2[i].insert(j);
		}
	}
	queue<int> que;
	que.push(r);
	vis[r] = 1;
	while(!que.empty()){
		int x = que.front();
		que.pop();
		for(auto &i : gph[x]){
			vector<int> p;
			while(!active[i].empty()){
				int y = active[i].back();
				active[i].pop_back();
				if(vis[y]) continue;
				if(gph2[x].find(y) != gph2[x].end()){
					p.push_back(y);
					continue;
				}
				vis[y] = 1; 
				d[y] = d[x] + 1;
				que.push(y);
			}
			active[i] = p;
		}
	}
}
 
int main(){
	int k, a, b;
	memset(dist, 0x3f, sizeof(dist));
	memset(dist2, 0x3f, sizeof(dist2));
	scanf("%d %d %d %d %d",&n,&m,&k,&a,&b);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dist[k] = dist2[k] = 0;
	bfs1(k, dist);
	bfs2(k, dist2);
	for(int i=1; i<=n; i++){
		int ret = a * dist[i];
		if(dist2[i] < 1e9) ret = min(ret, b * dist2[i]);
		if(dist[i] % 2 == 0) ret = min(ret, b * (dist[i] / 2));
		else ret = min(ret, b * (dist[i] / 2) + a);
		printf("%d\n", ret);
	}
}