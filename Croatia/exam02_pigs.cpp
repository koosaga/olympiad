#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 111000;

struct maxflow{
	struct edg{int pos, cap, rev;};
	vector<edg> gph[MAXN];
	int n;

	void init(int _n){
		n = _n;
	}
	  
	void add_edge(int s, int e, int x){
		gph[s].push_back({e, x, (int)gph[e].size()});
		gph[e].push_back({s, 0, (int)gph[s].size()-1});
	}
	  
	int pa[MAXN], pe[MAXN];

	bool bfs(){
		bool vis[MAXN] = {};
		queue<int> que;
		que.push(0);
		vis[0] = 1;
		while(!que.empty()){
			int x = que.front(); 
			que.pop();
			for(int i=0; i<gph[x].size(); i++){
				edg e = gph[x][i];
				if(e.cap > 0 && !vis[e.pos]){
					vis[e.pos] = 1;
					pa[e.pos] = x;
					pe[e.pos] = i;
					que.push(e.pos);
				}
			}
		}
		return vis[n];
	}
 
	int match(){
		int ret = 0;
		while(bfs()){
			int minv = 1e9;
			for(int pos = n; pos; pos = pa[pos]){
				minv = min(minv, gph[pa[pos]][pe[pos]].cap);
			}
			for(int pos = n; pos; pos = pa[pos]){
				int rev = gph[pa[pos]][pe[pos]].rev;
				gph[pa[pos]][pe[pos]].cap -= minv;
				gph[pos][rev].cap += minv;
			}
			ret += minv;
		}
		return ret;
	}

	int getcap(int x, int y){
		for(auto &i : gph[x]){
			if(i.pos == y) return i.cap;
		}
		return 0;
	}
}maxflow;

int idx[1005];
vector<pi> qry;
int n, m;

int main(){
	cin >> n >> m;
	for(int i=1; i<=n; i++){
		int cap;
		scanf("%d",&cap);
		idx[i] = i;
		maxflow.add_edge(0, i, cap);
	}
	int cp = n;
	while(m--){
		int v;
		scanf("%d",&v);
		cp++;
		while(v--){
			int i;
			scanf("%d",&i);
			maxflow.add_edge(idx[i], cp, 1e9);
			idx[i] = cp;
		}
		int cap;
		scanf("%d",&cap);
		qry.push_back(pi(cp, cap));
		for(int i=1; i<=n; i++){
			if(idx[i] == qry.back().first){
				maxflow.add_edge(idx[i], ++cp, 1e9);
				idx[i] = cp;
			}
		}
	}
	cp++;
	maxflow.init(cp);
	for(auto &i : qry){
		maxflow.add_edge(i.first, cp, i.second);
	}
	cout << maxflow.match();
}
