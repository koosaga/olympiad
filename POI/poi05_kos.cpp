#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

const int MAXN = 20005;

struct maxflow{
	struct edg{int pos, cap, rev;};
	vector<edg> gph[MAXN];

	void clear(){
		for(int i=0; i<MAXN; i++){
			gph[i].clear();
		}
	}

	void add_edge(int s, int e, int x){
		gph[s].push_back((edg){e, x, (int)gph[e].size()});
		gph[e].push_back((edg){s, 0, (int)gph[s].size()-1});
	}

	int dis[MAXN], pnt[MAXN];
	
	bool bfs(int src, int sink){
		memset(dis, 0, sizeof(dis));
		memset(pnt, 0, sizeof(pnt));
		queue<int> que;
		que.push(src);
		dis[src] = 1;
		while(!que.empty()){
			int x = que.front();
			que.pop();
			for(int i=0; i<gph[x].size(); i++){
				edg e = gph[x][i];
				if(e.cap > 0 && !dis[e.pos]){
					dis[e.pos] = dis[x] + 1;
					que.push(e.pos);
				}
			}
		}
		return dis[sink] > 0;
	}

	int dfs(int x, int sink, int f){
		if(x == sink) return f;
		for(; pnt[x] < gph[x].size(); pnt[x]++){
			edg e = gph[x][pnt[x]];
			if(e.cap > 0 && dis[e.pos] == dis[x] + 1){
				int w = dfs(e.pos, sink, min(f, e.cap));
				if(w){
					gph[x][pnt[x]].cap -= w;
					gph[e.pos][e.rev].cap += w;
					return w;
				}
			}
		}
		return 0;
	}

	lint match(int src, int sink){
		lint ret = 0;
		while(bfs(src, sink)){
			int r;
			while((r = dfs(src, sink, 2e9))) ret += r;
		}
		return ret;
	}
}maxflow;
 
int n, m, s[10005], e[10005];

int trial(int x){
	maxflow.clear();
	for(int i=0; i<m; i++){
		maxflow.add_edge(s[i], i + n + 1, 1);
		maxflow.add_edge(e[i], i + n + 1, 1);
		maxflow.add_edge(i+n+1, n+m+1, 1);
	}
	for(int j=1; j<=n; j++) maxflow.add_edge(0, j, x);
	return maxflow.match(0, n+m+1) == m;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++) scanf("%d %d",&s[i],&e[i]);
	int s = 0, e = m;
	while(s != e){
		int mi = (s+e)/2;
		if(trial(mi)) e = mi;
		else s = mi + 1;
	}
	trial(s);
	printf("%d\n", s);
	for(int j=0; j<m; j++){
		for(int k=0; k<maxflow.gph[::s[j]].size(); k++){
			if(maxflow.gph[::s[j]][k].pos == j + n + 1){
				printf("%d\n", 1 - maxflow.gph[::s[j]][k].cap);
			}
		}
	}
}


