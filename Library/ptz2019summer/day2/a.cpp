#include <bits/stdc++.h>
using namespace std;
const int MAXN = 4005;

int n, m;
bool adj[MAXN][MAXN];
int s[MAXN], e[MAXN];
vector<int> gph[MAXN];

void dfs(int x, int s){
	adj[s][x] = 1;
	for(auto &i : gph[x]){
		if(!adj[s][i]) dfs(i, s);
	}
}

bool onlyone[MAXN][MAXN];

struct strongly_connected{
	bitset<MAXN> gph[MAXN];
	void clear(){
		for(int i=0; i<MAXN; i++) gph[i] = 0;
	}
	void add_edge(int x, int y){
		gph[x][y] = 1;
	}
	int n;
	vector<int> dfn;
	int vis[MAXN], comp[MAXN];
	void dfs(int x){
		vis[x] = 1;
		for(int i=0; i<n; i++){
			if(!vis[i] && gph[x][i]) dfs(i);
		}
		dfn.push_back(x);
	}
	void rdfs(int x, int p){
		comp[x] = p;
		for(int i=0; i<n; i++){
			if(!comp[i] && gph[i][x]) rdfs(i, p);
		}
	}
	void get_scc(int _n){
		memset(vis, 0, sizeof(vis));
		memset(comp, 0, sizeof(comp));
		n = _n;
		dfn.clear();
		for(int i=0; i<n; i++){
			if(!vis[i]) dfs(i);
		}
		reverse(dfn.begin(), dfn.end());
		int p = 0;
		for(auto &i : dfn){
			if(!comp[i]) rdfs(i, ++p);
		}
	}
};

struct twosat{
	strongly_connected scc;
	int n;
	void init(int _n){ scc.clear(); n = _n; }
	int NOT(int x){ return x >= n ? (x - n) : (x + n); }
	void add_edge(int x, int y){
		if((x >> 31) & 1) x = (~x) + n;
		if((y >> 31) & 1) y = (~y) + n;
		scc.add_edge(x, y), scc.add_edge(NOT(y), NOT(x));
	}
	bool satisfy(){
		scc.get_scc(2*n);
		for(int i=0; i<n; i++){
			if(scc.comp[i] == scc.comp[NOT(i)]) return 0;
		}
		return 1;
	}
}twosat;

bool trial(int x){
	twosat.init(x);
	for(int i=0; i<2*x; i++){
		for(int j=0; j<i; j++){
			if(onlyone[i][j]){
				int l = i / 2;
				int r = j / 2;
				if(i % 2) l = ~l;
				if(j % 2) r = ~r;
				twosat.add_edge(l, ~r);
			}
		}
	}
	return twosat.satisfy();
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<2*n; i++){
		scanf("%d %d",&s[i],&e[i]);
		gph[s[i]].push_back(e[i]);
	}
	for(int i=1; i<=n; i++){
		dfs(i, i);
	}
	for(int i=0; i<2*n; i++){
		for(int j=0; j<i; j++){
			if(!adj[e[i]][s[j]] && !adj[e[j]][s[i]]){
				onlyone[i][j] = onlyone[j][i] = 1;
			}
		}
	}
	int s = 0, e = n;
	while(s != e){
		int m = (s+e+1)/2;
		if(trial(m)) s = m;
		else e = m-1;
	}
	cout << s << endl;
}
