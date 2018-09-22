#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
using lint = long long;


const int MAXN = 3005;
struct strongly_connected{
	vector<int> gph[MAXN];
	vector<int> rev[MAXN];
	vector<int> dfn;
	int comp[MAXN], piv;
	bool vis[MAXN];

	void clear(){
		for(int i=0; i<MAXN; i++){
			gph[i].clear();
			rev[i].clear();
		}
	}

	void add_edge(int s, int e){
		gph[s].push_back(e);
		rev[e].push_back(s);
	}

	void dfs(int x){
		vis[x] = 1;
		for(auto &i : gph[x]){
			if(!vis[i]) dfs(i);
		}
		dfn.push_back(x);
	}

	void rdfs(int x, int p){
		comp[x] = p;
		for(auto &i : rev[x]){
			if(!comp[i]) rdfs(i, p);
		}
	}

	void get_scc(int n){
		dfn.clear();
		memset(comp, 0, sizeof(comp));
		memset(vis, 0, sizeof(vis));
		piv = 0;
		for(int i=0; i<n; i++){
			if(!vis[i]) dfs(i);
		}
		reverse(dfn.begin(), dfn.end());
		for(auto &i : dfn){
			if(!comp[i]) rdfs(i, ++piv);
		}
	}
}scc;

int n, m, ccost[MAXN], cost[MAXN], s[8005], e[8005];
int mark[MAXN], anyguy[MAXN];

int main(){
	int q;
	scanf("%d %d",&n,&q);
	memset(cost, 0x3f, sizeof(cost));
	while(q--){
		int p, v; scanf("%d %d",&p,&v);
		p--;
		cost[p] = min(cost[p], v);
	}
	scanf("%d",&m);
	for(int i=0; i<m; i++){
		scanf("%d %d",&s[i],&e[i]);
		s[i]--, e[i]--;
		scc.add_edge(s[i], e[i]);
	}
	scc.get_scc(n);
	int K = scc.piv;
	memset(ccost, 0x3f, sizeof(ccost));
	for(int i=n-1; i>=0; i--){
		ccost[scc.comp[i]] = min(ccost[scc.comp[i]], cost[i]);
		anyguy[scc.comp[i]] = i + 1;
	}
	for(int i=0; i<m; i++){
		if(scc.comp[s[i]] != scc.comp[e[i]]){
			mark[scc.comp[e[i]]] = 1;
		}
	}
	lint ans = 0;
	int minv = 1e9;
	for(int i=1; i<=K; i++){
		if(!mark[i]){
			if(ccost[i] > 1e8){
				minv = min(minv, anyguy[i]);
			}
			ans += ccost[i];
		}
	}
	if(minv <= n){
		cout << "NIE" << endl;
		cout << minv << endl;
		return 0;
	}
	cout << "TAK" << endl;
	cout << ans << endl;
}
