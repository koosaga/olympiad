#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;

const int MAXN = 444;
struct maxflow{
	struct edg{int pos, cap, rev;};
	vector<edg> gph[MAXN];

	void clear(){
		for(int i=0; i<MAXN; i++){
			gph[i].clear();
		}
	}

	void add_edge(int s, int e, int x){
		gph[s].push_back({e, x, (int)gph[e].size()});
		gph[e].push_back({s, 0, (int)gph[s].size()-1});
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
};

struct circ{
	maxflow mf;
	lint lsum;
	void clear(){
		lsum = 0;
		mf.clear();
	}
	void add_edge(int s, int e, int l, int r){
		lsum += l;
		mf.add_edge(s + 2, e + 2, r - l);
		mf.add_edge(0, e + 2, l);
		mf.add_edge(s + 2, 1, l);
	}
	bool solve(int s, int e){
		mf.add_edge(e+2, s+2, 1e9);
		return lsum == mf.match(0, 1);
	}
	int get(int s, int e){
		s += 2;
		e += 2;
		for(auto &j : mf.gph[s]){
			if(j.pos == e) return j.cap;
		}
		assert(0);
	}
}circ;

int n, m;
int a[205][205], s1[205], s2[205];

void in(int &x){
	double y;
	scanf("%lf",&y);
	x = (int)round(10 * y);
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			in(a[i][j]);
		}
		in(s1[i]);
	}
	for(int i=1; i<=m; i++) in(s2[i]);
	int ls = 0;
	circ.clear();
	for(int i=1; i<=n; i++){
		circ.add_edge(0, i, s1[i] / 10, (s1[i] + 9) / 10);
	}
	for(int i=1; i<=m; i++){
		circ.add_edge(i + n, n + m + 1, s2[i] / 10, (s2[i] + 9) / 10);
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			circ.add_edge(i, j + n, a[i][j] / 10, (a[i][j] + 9) / 10);
		}
	}
	assert(circ.solve(0, n+m+1));
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			printf("%d ", (a[i][j] + 9) / 10 - circ.get(i, j + n));
		}
		printf("%d\n", (s1[i] + 9) / 10 - circ.get(0, i));
	}
	for(int i=1; i<=m; i++){
		printf("%d ", (s2[i] + 9) / 10 - circ.get(i+n, n+m+1));
	}
}
