#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

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
struct twosat{
	int n; // = number of clauses
	void init(int _n){ scc.clear(); n = _n; }
	int NOT(int x){ return x >= n ? (x - n) : (x + n); }
	void add_edge(int x, int y){ // input ~x to denote NOT
		if((x >> 31) & 1) x = (~x) + n;
		if((y >> 31) & 1) y = (~y) + n;
		scc.add_edge(x, y), scc.add_edge(NOT(y), NOT(x));
	}
	bool satisfy(vector<bool> &res){
		res.resize(n);
		scc.get_scc(2*n);
		for(int i=0; i<n; i++){
			if(scc.comp[i] == scc.comp[NOT(i)]) return 0;
			if(scc.comp[i] < scc.comp[NOT(i)]) res[i] = 0;
			else res[i] = 1;
		}
		return 1;
	}
}twosat;

int n, q;

int readp(){
	string s;
	int x;
	cin >> x >> s;
	x--;
	if(s == "B") x = ~x;
	return x;
}

int main(){
	cin >> n >> q;
	twosat.init(n);
	while(q--){
		int x = readp();
		int y = readp();
		int z = readp();
		twosat.add_edge(~x, y);
		twosat.add_edge(~y, z);
		twosat.add_edge(~z, x);
	}
	vector<bool> res;
	if(!twosat.satisfy(res)) puts("-1");
	else{
		for(int i=0; i<n; i++) printf("%c", res[i] ? 'R' : 'B');
	}
}
