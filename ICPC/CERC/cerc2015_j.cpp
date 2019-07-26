#include <bits/stdc++.h>
using namespace std;
const int MAXV = 3005;
const int MAXE = 4505;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())

struct disj{
	int pa[MAXV];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p); q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

struct bcc{
	int dfn[MAXV], low[MAXV], bcc[MAXV], piv, col;
	bool same_cmp(int x, int y){
		return bcc[x] == bcc[y];
	}
}ds[MAXE];

vector<int> gph[MAXV];

void dfs(int x, int p, bcc &ds){
	ds.dfn[x] = ds.low[x] = ++ds.piv;
	for(auto &i : gph[x]){
		if(i == p) continue;
		if(!ds.dfn[i]){
			dfs(i, x, ds);
			ds.low[x] = min(ds.low[x], ds.low[i]);
		}
		else ds.low[x] = min(ds.low[x], ds.dfn[i]);
	}
}

void color(int v, int c, bcc &ds){
	ds.bcc[v] = c;
	for(auto &i : gph[v]){
		if(ds.bcc[i]) continue;
		if(ds.low[i] > ds.dfn[v]){
			color(i, ++ds.col, ds);
		}
		else color(i, c, ds);
	}
}

int n, m;
pi e[MAXE];
vector<int> cnd[MAXV];
vector<int> vect[MAXV];

void make_bcc(int ptr){
	for(int i=1; i<=n; i++){
		if(!ds[ptr].dfn[i]){
			++ds[ptr].col;
			dfs(i, 0, ds[ptr]);
			color(i, ds[ptr].col, ds[ptr]);
		}
	}
}

int main(){
	scanf("%d %d",&n,&m);
	disj.init(n);
	for(int i=1; i<=m; i++){
		scanf("%d %d",&e[i].first,&e[i].second);
		disj.uni(e[i].first, e[i].second);
	}
	for(int i=0; i<=m; i++){
		for(int j=1; j<=n; j++) gph[j].clear();
		for(int j=1; j<=m; j++){
			if(i != j){
				gph[e[j].first].push_back(e[j].second);
				gph[e[j].second].push_back(e[j].first);
			}
		}
		make_bcc(i);
	}
	int ret = 0;
	for(int i=1; i<=n; i++){
		cnd[disj.find(i)].push_back(i);
		for(int j=0; j<=m; j++){
			vect[i].push_back(ds[j].bcc[i]);
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=i+1; j<=n; j++){
			if(disj.find(i) != disj.find(j)) continue;
			int cut = 0;
			if(!ds[0].same_cmp(i, j)){
				cut = 1;
			}
			else{
				cut = 2;
			}
			ret += cut;
		}
	}
	for(int i=1; i<=n; i++){
		sort(cnd[i].begin(), cnd[i].end(), [&](const int &x, const int &y){
			return vect[x] < vect[y];
		});
		for(int j=0; j<cnd[i].size(); ){
			int e = j;
			while(e < cnd[i].size() && vect[cnd[i][e]] == vect[cnd[i][j]]) e++;
			ret += (e - j) * (e - j - 1) / 2;
			j = e;
		}
	}
	cout << ret << endl;
}
