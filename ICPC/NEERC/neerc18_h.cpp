#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;

struct strongly_connected{
	vector<int> gph[MAXN];
	vector<int> rev[MAXN];
	vector<int> dfn;
	int comp[MAXN], piv;
	bool vis[MAXN];

	void clear(int n){
		for(int i=0; i<n; i++){
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
		memset(comp, 0, sizeof(comp[0]) * (n + 2));
		memset(vis, 0, sizeof(vis[0]) * (n + 2));
		piv = 0;
		for(int i=0; i<n; i++){
			if(!vis[i]) dfs(i);
		}
		reverse(dfn.begin(), dfn.end());
		for(auto &i : dfn){
			if(!comp[i]) rdfs(i, ++piv);
		}
	}

	vector<int> cnd[MAXN];
	bool check(vector<int> prop, int n){
		for(int i=0; i<=n; i++) cnd[i].clear();
		for(int i=0; i<n; i++){
			for(auto &j : gph[i]){
				if(comp[i] != comp[j]){
					assert(comp[i] < comp[j]);
					cnd[comp[i]].push_back(comp[j]);
				}
			}
		}
		for(int i=piv; i; i--){
			int has = 0;
			for(auto &j : cnd[i]){
				if(prop[j]) has = 1;
			}
			if(has && prop[i]) return false;
			prop[i] |= has;
		}
		return true;
	}
}scc;

struct twosat{
	strongly_connected scc;
	int n;
	void init(int _n){ scc.clear(2 * _n + 3); n = _n; }
	int NOT(int x){ return x >= n ? (x - n) : (x + n); }
	void add_edge(int x, int y){
		if((x >> 31) & 1) x = (~x) + n;
		if((y >> 31) & 1) y = (~y) + n;
		scc.add_edge(x, y), scc.add_edge(NOT(y), NOT(x));
	}
	bool satisfy(int *res){
		scc.get_scc(2*n);
		for(int i=0; i<n; i++){
			if(scc.comp[i] == scc.comp[NOT(i)]) return 0;
			if(scc.comp[i] < scc.comp[NOT(i)]) res[i] = 0;
			else res[i] = 1;
		}
		return 1;
	}
}twosat;

int junggyu(int s){ 
	if(s > 0) return s - 1;
	return ~(-s - 1);
}

int res[MAXN];
char str[MAXN];

int main(){
	int tc, n, m;
	scanf("%d",&tc);
	while(tc--){
		scanf("%d %d %s",&n,&m,str);
		twosat.init(n);
		for(int i=0; i<m; i++){
			int s, e; scanf("%d %d",&s,&e);
			s = junggyu(s);
			e = junggyu(e);
			twosat.add_edge(s, ~e);
		}
		if(!twosat.satisfy(res)){
			puts("FALSE");
			continue;
		}
		int K = twosat.scc.piv;
		vector<int> prop(K + 1);
		if(*max_element(prop.begin(), prop.end()) > 1){
			puts("FALSE");
			continue;
		}
		bool good = 0;
		for(int i=n-1; i>=0; i--){
			if(prop[twosat.scc.comp[i]] || prop[twosat.scc.comp[i + n]]){
				puts("FALSE");
				good = 1;
				break;
			}
			if(str[i] == 'A'){
				prop[twosat.scc.comp[i]]++;
				prop[twosat.scc.comp[i + n]]++;
			}
		}
		if(good){
			continue;
		}
		puts(twosat.scc.check(prop, n*2) ? "TRUE" : "FALSE");
	}
}
