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

struct edg{int st, ed, x;};

int grp[25005], deg[25005], p;
vector<pi> graph[25005];
vector<edg> dag[25005];
int dist[25005];

void dfs(int x){
	if(grp[x]) return;
	grp[x] = p;
	for(int i=0; i<graph[x].size(); i++){
		dfs(graph[x][i].second);
	}
}

int n, m1, m2, s;
bool vis[25005];

queue<int> q;
priority_queue<pi, vector<pi>, greater<pi> > pq[25005];

void solve(int x){
	while(!pq[x].empty()){
		pi t = pq[x].top();
		pq[x].pop();
		if(vis[t.second]) continue;
		vis[t.second] = 1;
		dist[t.second] = t.first;
		for(int i=0; i<graph[t.second].size(); i++){
			pi j = graph[t.second][i];
			pq[x].push(pi(j.first + t.first, j.second));
		}
	}
}

int main(){
	memset(dist,0x3f,sizeof(dist));
	scanf("%d %d %d %d",&n,&m1,&m2,&s);
	for(int i=0; i<m1; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		graph[s].push_back(pi(x,e));
		graph[e].push_back(pi(x,s));
	}
	for(int i=1; i<=n; i++){
		if(!grp[i]){
			p++;
			dfs(i);
		}
	}
	for(int i=0; i<m2; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		dag[grp[s]].push_back((edg){s, e, x});
		deg[grp[e]]++;
	}
	for(int i=1; i<=p; i++){
		if(deg[i] == 0){
			q.push(i);
		}
	}
	dist[s] = 0;
	pq[grp[s]].push(pi(0, s));
	while(!q.empty()){
		int f = q.front();
		q.pop();
		solve(f);
		for(int ii=0; ii<dag[f].size(); ii++){
			edg i = dag[f][ii];
			int g = grp[i.ed];
			deg[g]--;
			if(vis[i.st]) pq[g].push(pi(dist[i.st] + i.x, i.ed));
			if(deg[g] == 0) q.push(g);
		}
	}
	for(int i=1; i<=n; i++){
		if(!vis[i]) puts("NO PATH");
		else printf("%d\n",dist[i]);
	}
}