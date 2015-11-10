#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

struct edg{int s, e, x;};

vector<pi> graph[100005];
vector<int> tree[100005];

bool vis[100005];
int dist[100005];
int par[17][100005], pae[100005], dep[100005];
priority_queue<pi, vector<pi>, greater<pi> > pq;

int n, m;
int s[200005], e[200005], x[200005];

int nxt[100005], rootway[100005];

void dfs(int x){
	for(int i=1; i<17; i++){
		par[i][x] = par[i-1][par[i-1][x]];
	}
	nxt[x] = par[0][x];
	rootway[x] = 1e9;
	for(auto &i : tree[x]){
		dfs(i);
	}
}

int lca(int s, int e){
	if(dep[s] > dep[e]) swap(s, e);
	int dx = dep[e] - dep[s];
	for(int i=0; i<17; i++){
		if((dx >> i) & 1) e = par[i][e];
	}
	for(int i=16; i>=0; i--){
		if(par[i][s] != par[i][e]){
			s = par[i][s];
			e = par[i][e];
		}
	}
	if(s != e) return par[0][s];
	return s;
}

vector<edg> pnt;

int paint(int s, int e, int x){
	if(dep[s] <= dep[e]) return s;
	rootway[s] = min(rootway[s], x);
	return nxt[s] = paint(nxt[s], e, x);
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		scanf("%d %d %d",&s[i],&e[i],&x[i]);
		graph[s[i]].push_back(pi(x[i], e[i]));
		graph[e[i]].push_back(pi(x[i], s[i]));
	}
	pq.push(pi(0, 1));
	memset(dist,0x3f,sizeof(dist));
	dist[1] = 0;
	while(!pq.empty()){
		pi t = pq.top();
		pq.pop();
		if(vis[t.second]) continue;
		vis[t.second] = 1;
		if(t.second != 1){
			dep[t.second] = dep[par[0][t.second]] + 1;
			tree[par[0][t.second]].push_back(t.second);
		}
		for(auto &i : graph[t.second]){
			if(dist[i.second] > t.first + i.first){
				dist[i.second] = t.first + i.first;
				par[0][i.second] = t.second;
				pae[i.second] = i.first;
				pq.push(pi(t.first + i.first, i.second));
			}
		}
	}
	for(int i=1; i<=n; i++){
		if(!vis[i]){
			dep[i] = 1;
			tree[1].push_back(i);
		}
	}
	dfs(1);
	for(int i=0; i<m; i++){
		if(par[0][s[i]] == e[i]){
			continue;
		}
		if(par[0][e[i]] == s[i]){
			continue;
		}
		int upd = dist[e[i]] + dist[s[i]] + x[i];
		int l = lca(s[i], e[i]);
		pnt.push_back((edg){e[i], l, upd});
		pnt.push_back((edg){s[i], l, upd});
	}
	sort(pnt.begin(), pnt.end(), [&](const edg &a, const edg &b){
		return a.x < b.x;
	});
	for(auto &i : pnt){
		paint(i.s, i.e, i.x);
	}
	for(int i=2; i<=n; i++){
		if(rootway[i] > 3e8) puts("-1");
		else printf("%d\n",rootway[i] - dist[i]);
	}
}