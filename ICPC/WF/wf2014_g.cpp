#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int n, adj[205][205];
vector<int> ls;

struct disj{
	int pa[405];
	void init(int n){
		for(int i=0; i<=n; i++) pa[i] = i;
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p), q = find(q);
		if(p == q) return 0;
		pa[q] = p; find(q);
		return 1;
	}
}disj;

struct edg{int s,e,x;};
vector<edg> v;

struct scc{
	vector<int> graph[405], rev[405];
	int n;

	int comp[405], piv;

	bool vis[405], vis2[405];
	vector<int> dfn;

	void init(int n){
		memset(vis,0,sizeof(vis));
		memset(vis2,0,sizeof(vis2));
		dfn.clear();
		piv = 0;
		this->n = n;
		for(int i=0; i<=2*n; i++){
			graph[i].clear();
			rev[i].clear();
		}
	}
	int NOT(int x){
		if(x > n) return x-n;
		return x+n;
	}
	void add(int x, int y){
		graph[x].push_back(y);
		graph[NOT(y)].push_back(NOT(x));
		rev[y].push_back(x);
		rev[NOT(x)].push_back(NOT(y));
	}
	void dfs(int x){
		if(vis[x]) return;
		vis[x] = 1;
		for(auto &i : graph[x]){
			dfs(i);
		}
		dfn.push_back(x);
	}
	void dfs2(int x){
		if(vis2[x]) return;
		comp[x] = piv;
		vis2[x] = 1;
		for(auto &i : rev[x]){
			dfs2(i);
		}
	}
	void get_scc(){
		for(int i=1; i<=2*n; i++){
			if(!vis[i]) dfs(i);
		}
		reverse(dfn.begin(),dfn.end());
		for(auto &i : dfn){
			if(!vis2[i]){
				piv++;
				dfs2(i);
			}
		}
	}
}scc;

bool trial(int lim1, int lim2){
	scc.init(n);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(adj[i][j] > lim1){
				scc.add(i+n,j);
				scc.add(i,j+n);
			}
			else if(adj[i][j] > lim2){
				scc.add(i+n,j);
			}
		}
	}
	scc.get_scc();
	for(int i=1; i<=n; i++){
		if(scc.comp[i] == scc.comp[n+i]) return 0;
	}
	return 1;
}

int main(){
	scanf("%d",&n);
	ls.push_back(0);
	ls.push_back(1e9 + 1);
	for(int i=1; i<=n; i++){
		for(int j=i+1; j<=n; j++){
			scanf("%d",&adj[i][j]);
			adj[j][i] = adj[i][j];
			v.push_back({i,j,adj[i][j]});
			ls.push_back(adj[i][j]);
		}
	}
	v.push_back({0,0,0});
	sort(v.begin(), v.end(), [&](const edg &a, const edg &b){return a.x > b.x;});
	sort(ls.begin(), ls.end());
	ls.resize(unique(ls.begin(), ls.end()) - ls.begin());
	disj.init(2*n);
	int res = 2e9;
	for(int i=0; i<v.size();){
		int e = i;
		while(e < v.size() && v[e].x == v[i].x) e++;
		int find = 0;
		for(int j=i; j<e; j++){
			if(disj.find(v[j].s) != disj.find(v[j].e + n)){
				find = 1;
			}
		}
		if(find){
			int st = 0, ed = (int)(lower_bound(ls.begin(),ls.end(),v[i].x) - ls.begin());
			while(st != ed){
				int m = (st + ed) / 2;
				if(trial(v[i].x,ls[m])) ed = m;
				else st = m+1;
			}
			res = min(res,v[i].x + ls[st]);
			for(int j=i; j<e; j++){
				disj.uni(v[j].s,v[j].e + n);
				disj.uni(v[j].s + n, v[j].e);
			}
			bool bad = 0;
			for(int i=1; i<=n; i++){
				if(disj.find(i) == disj.find(i+n)){
					bad = 1;
				}
			}
			if(bad) break;
		}
		i = e;
	}
	printf("%d",res);
}