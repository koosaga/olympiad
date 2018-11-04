#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using lint = long long;
using pi = pair<lint, int>;

int n, m;
struct edg{
	int pos, cst, idx;
};

vector<edg> gph[MAXN];
vector<edg> rev[MAXN];
lint dist[2][MAXN];

void dijkstra(int src, lint *dis, vector<edg>* gph){
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	dis[src] = 0;
	pq.emplace(dis[src], src);
	while(!pq.empty()){
		auto x = pq.top();
		pq.pop();
		if(dis[x.second] != x.first) continue;
		for(auto &i : gph[x.second]){
			if(dis[i.pos] > x.first + i.cst){
				dis[i.pos] = x.first + i.cst;
				pq.emplace(dis[i.pos], i.pos);
			}
		}
	}
}

vector<pi> g2[MAXN];
int dfn[MAXN], low[MAXN], piv;
int cut[MAXN];

void dfs(int x, int p){
	dfn[x] = low[x] = ++piv;
	for(auto &i : g2[x]){
		if(i.first != p){
			if(!dfn[i.second]){
				dfs(i.second, i.first);
				low[x] = min(low[x], low[i.second]);
				if(low[i.second] > dfn[x]){
					cut[i.first] = 1;
				}
			}
			else low[x] = min(low[x], dfn[i.second]);
		}
	}
}

int s[MAXN], e[MAXN], x[MAXN];
string ans[MAXN];
int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		scanf("%d %d %d",&s[i],&e[i],&x[i]);
		s[i]--, e[i]--;
		gph[s[i]].push_back({e[i], x[i], i});
		rev[e[i]].push_back({s[i], x[i], i});
	}
	memset(dist, 0x3f, sizeof(dist));
	dijkstra(0, dist[0], gph);
	dijkstra(1, dist[1], rev);
	lint D = dist[0][1];
	for(int i=0; i<m; i++){
		if(dist[0][s[i]] + x[i] + dist[1][e[i]] != D){
			if(dist[0][e[i]] + x[i] + dist[1][s[i]] < D){
				ans[i] = "HAPPY";
			}
			else ans[i] = "SOSO";
		}
		else{
			g2[s[i]].emplace_back(i, e[i]);
			g2[e[i]].emplace_back(i, s[i]);
		}
	}
	dfs(0, -1);
	for(int i=0; i<m; i++){
		if(dist[0][s[i]] + x[i] + dist[1][e[i]] == D){
			if(cut[i]) ans[i] = "SAD";
			else ans[i] = "SOSO";
		}
	}
	for(int i=0; i<m; i++) puts(ans[i].c_str());
}