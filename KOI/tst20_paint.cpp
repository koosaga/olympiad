#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
const int MAXN = 1000005;

int idx[2][1005][1005], vtx;

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
		s--, e--;
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

	int get_scc(int n){
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
		return piv;
	}
}scc;
int yellowblue(int N, int M, std::vector<std::string> V){
	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
			if(V[i][j] == '.'){
				int e = j;
				while(e < M && V[i][e] == '.') e++;
				vtx++;
				for(int k=j; k<e; k++){
					idx[0][i][k] = vtx;
				}
				j = e;
			}
		}
	}
	for(int j=0; j<M; j++){
		for(int i=0; i<N; i++){
			if(V[i][j] == '.'){
				int e = i;
				while(e < N && V[e][j] == '.') e++;
				vtx++;
				for(int k=i; k<e; k++){
					idx[1][k][j] = vtx;
				}
				i = e;
			}
		}
	}
	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
			if(V[i][j] == '.'){
				int e = j;
				while(e < M && V[i][e] == '.') e++;
				scc.add_edge(idx[0][i][j], idx[1][i][j]);
				scc.add_edge(idx[0][i][e - 1], idx[1][i][e - 1]);
				j = e;
			}
		}
	}
	for(int j=0; j<M; j++){
		for(int i=0; i<N; i++){
			if(V[i][j] == '.'){
				int e = i;
				while(e < N && V[e][j] == '.') e++;
				scc.add_edge(idx[1][i][j], idx[0][i][j]);
				scc.add_edge(idx[1][e - 1][j], idx[0][e - 1][j]);
				i = e;
			}
		}
	}
	int m = scc.get_scc(vtx);
	vector<pi> congph;
	vector<int> chk(m);
	for(int i=0; i<vtx; i++){
		for(auto &j : scc.gph[i]){
			if(scc.comp[j] - scc.comp[i] == 1){
				chk[scc.comp[i]] = 1;
			}
		}
	}
	return count(all(chk), 1) == m - 1;
}
