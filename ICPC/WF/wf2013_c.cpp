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

struct edg{int pos, cap, rev;};

int n, m, c;
vector<pi> graph[25005];
vector<edg> graph2[25005];

priority_queue<pi, vector<pi>, greater<pi>> pq;
int dist[25005];

void add_edge(int s, int e){
	graph2[s].push_back({e, 1, (int)graph2[e].size()});
	graph2[e].push_back({s, 0, (int)graph2[s].size()-1});
}

void const_graph(){
	for(int i=1; i<=n; i++){
		for(auto &j : graph[i]){
			if(dist[i] + j.first == dist[j.second]){
				add_edge(j.second, i);
			}
		}
	}
}

void dijkstra(){
	bool vis[25005] = {};
	pq.push(pi(0, 1));
	while(!pq.empty()){
		pi t = pq.top();
		pq.pop();
		if(vis[t.second]) continue;
		vis[t.second] = 1;
		dist[t.second] = t.first;
		for(auto &i : graph[t.second]){
			pq.push(pi(t.first + i.first, i.second));
		}
	}
}

queue<int> q;
int pa[25005], pe[25005];

int bfs(int x){
	bool vis[25005] = {};
	q.push(x);
	vis[x] = 1;
	while(!q.empty()){
		int qf = q.front();
		q.pop();
		for(int i=0; i<graph2[qf].size(); i++){
			edg e = graph2[qf][i];
			if(e.cap > 0 && !vis[e.pos]){
				pa[e.pos] = qf;
				pe[e.pos] = i;
				vis[e.pos] = 1;
				q.push(e.pos);
			}
		}
	}
	return vis[1];
}

int match(){
	int ret = 0;
	while(bfs(0)){
		ret++;
		int pos = 1;
		while(pos){
			int rev = graph2[pa[pos]][pe[pos]].rev;
			graph2[pa[pos]][pe[pos]].cap--;
			graph2[pos][rev].cap++;
			pos = pa[pos];
		}
	}
	return ret;
}

pi a[1005];
int main(){
	scanf("%d %d %d",&n,&m,&c);
	for(int i=0; i<m; i++){
		int x, y, t;
		scanf("%d %d %d",&x,&y,&t);
		graph[x].push_back(pi(t, y));
		graph[y].push_back(pi(t, x));
	}
	dijkstra();
	for(int i=0; i<c; i++){
		int t;
		scanf("%d",&t);
		a[i] = pi(dist[t], t);
	}
	sort(a, a+c);
	int ret = 0;
	for(int i=0; i<c; ){
		int e = i;
		while(e < c && a[e].first == a[i].first) e++;
		for(int i=0; i<=n; i++){
			graph2[i].clear();
		}
		for(int j=i; j<e; j++){
			add_edge(0, a[j].second);
		}
		const_graph();
		ret += match();
		i = e;
	}
	printf("%d", ret);
}