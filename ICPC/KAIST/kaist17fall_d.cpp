#include<bits/stdc++.h>
using namespace std;
const int MAXN = 55;
const int MAXV = 20005;
using pi = pair<int, int>;

struct strongly_connected{
	vector<int> gph[MAXV];
	vector<int> rev[MAXV];
	vector<int> dfn;
	int comp[MAXV], piv;
	bool vis[MAXV];

	void clear(){
		for(int i=0; i<MAXV; i++){
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

int n, m;
char str[MAXN][MAXN];
int L[MAXN][MAXN];
int R[MAXN][MAXN];
int V[MAXN][MAXN];
bool reach[5500][5500];
int Lesc[MAXV], Resc[MAXV];
vector<int> cnd[MAXV];
int vtx;

int main(){
	cin >> n >> m;
	for(int i=0; i<n; i++) cin >> str[i];
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] == '#') continue;
			V[i][j] = vtx++;
		}
	}
	int cur = vtx;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; ){
			if(str[i][j] == '#'){
				j++;
				continue;
			}
			int e = j;
			while(e < m && str[i][e] != '#') e++;
			for(int k=j; k<e; k++) L[i][k] = vtx;
			Lesc[vtx] = V[i][j];
			Resc[vtx] = V[i][e-1];
			vtx++;
			j = e;
		}
	}
	for(int j=0; j<m; j++){
		for(int i=0; i<n; ){
			if(str[i][j] == '#'){
				i++;
				continue;
			}
			int e = i;
			while(e < n && str[e][j] != '#') e++;
			for(int k=i; k<e; k++) R[k][j] = vtx;
			Lesc[vtx] = V[i][j];
			Resc[vtx] = V[e-1][j];
			vtx++;
			i = e;
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] != '#'){
				scc.add_edge(V[i][j], L[i][j]);
				scc.add_edge(V[i][j], R[i][j]);
			}
		}
	}
	for(int i=cur; i<vtx; i++){
		scc.add_edge(i, Lesc[i]);
		scc.add_edge(i, Resc[i]);
	}
	scc.get_scc(vtx);
	int cvtx = scc.piv;
	for(int i=0; i<vtx; i++){
		for(auto &j : scc.gph[i]){
			if(scc.comp[i] != scc.comp[j]){
				cnd[scc.comp[i]].push_back(scc.comp[j]);
			}
		}
	}
	for(int i=cvtx; i; i--){
		reach[i][i] = 1;
		for(auto &j : cnd[i]){
			for(int k=1; k<=cvtx; k++){
				reach[i][k] |= reach[j][k];
			}
		}
	}
	int stV = -1;
	twosat.init(cvtx + vtx - cur);
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] == 'O'){
				stV = scc.comp[V[i][j]];
			}
		}
	}
	for(int i=1; i<=cvtx; i++){
		if(!reach[stV][i]){
			twosat.add_edge(i-1, ~(i-1));
		}
		for(int j=i+1; j<=cvtx; j++){
			if(!reach[i][j]){
				twosat.add_edge(i-1, ~(j-1));
			}
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] == '#') continue;
			int Lnum = L[i][j] - cur + cvtx;
			int Rnum = R[i][j] - cur + cvtx;
			twosat.add_edge(Lnum, scc.comp[L[i][j]] - 1);
			twosat.add_edge(Rnum, scc.comp[R[i][j]] - 1);
			if(str[i][j] == '*') twosat.add_edge(~Lnum, Rnum);
		}
	}
	puts(twosat.satisfy() ? "YES" : "NO");
}
