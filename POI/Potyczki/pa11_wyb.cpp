#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
typedef pair<int, int> pi;

struct qr{
	int typ, x, y;
};

struct eg{
	int s, e, x;
	bool operator<(const eg &e)const{
		return x < e.x;
	}
};

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x :find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;


vector<int> gph[MAXN];
int par[17][MAXN], dep[MAXN], din[MAXN], dout[MAXN], piv;
int fnd[MAXN], n;

int up(int x){
	if(fnd[x] == x) return x;
	return fnd[x] = up(fnd[x]);
}

void dfs(int x, int p){
	din[x] = ++piv;
	for(auto &i : gph[x]){
		if(i == p) continue;
		par[0][i] = x;
		dep[i] = dep[x] + 1;
		dfs(i, x);
	}
	dout[x] = piv;
}

bool sub(int s, int e){
	return din[s] <= din[e] &&dout[e] <= dout[s];
}

int lca(int s, int e){
	if(dep[s] > dep[e]) swap(s, e);
	int dx = dep[e] - dep[s];
	for(int i=0; i<17; i++){
		if((dx >> i) & 1) e = par[i][e];
	}
	for(int i=16; i>=0; i--){
		if(par[i][s] != par[i][e]){
			s = par[i][s];
			e = par[i][e];
		}
	}
	if(s!=e)return par[0][s];
	return s;
}

void preprocess_tree(){
	iota(fnd, fnd + n + 1, 0);
	dfs(1, 0);
	for(int i=1; i<17; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
}

void add_edge(int s, int e){
	int l = lca(s, e);
	while(s != l){
		s = up(s);
		if(sub(s, l)) break;
		fnd[s] = par[0][s];
	}
	while(e != l){
		e = up(e);
		if(sub(e, l)) break;
		fnd[e] = par[0][e];
	}
}

bool query_fuck(int s, int e){
	int l = lca(s, e);
	s = up(s);
	e = up(e);
	return sub(s, l) && sub(e, l);
}

int m, q, s[MAXN], e[MAXN], x[MAXN];
qr query[MAXN];
vector<eg> edg;
char buf[5];

int main(){
	map<pi, int> mp;
	scanf("%d %d %d",&n,&m,&q);
	for(int i=0; i<m; i++){
		scanf("%d %d",&s[i],&e[i]);
		if(s[i] > e[i]) swap(s[i], e[i]);
	}
	for(int i=0; i<q; i++){
		scanf("%s",buf);
		if(*buf == 'Z'){
			int s, e;
			scanf("%d %d",&s,&e);
			if(s > e) swap(s, e);
			mp[pi(s, e)] = i;
			query[i] = {1, s, e};
		}
		else{
			int s, e;
			scanf("%d %d",&s,&e);
			query[i] = {2, s, e};
		}
	}
	for(int i=0; i<m; i++){
		if(mp.find(pi(s[i], e[i])) != mp.end()){
			x[i] = mp[pi(s[i], e[i])];
		}
		else x[i] = q;
		edg.push_back({s[i], e[i], x[i]});
	}
	sort(edg.rbegin(), edg.rend());
	disj.init(n);
	for(auto &i : edg){
		if(disj.uni(i.s, i.e)){
			gph[i.s].push_back(i.e);
			gph[i.e].push_back(i.s);
		}
	}
	for(int i=2; i<=n; i++){
		if(disj.uni(1, i)){
			gph[1].push_back(i);
			gph[i].push_back(1);
		}
	}
	disj.init(n);
	preprocess_tree();
	disj.init(n);
	vector<int> dap;
	int ptr = 0;
	for(int i=q-1; i>=0; i--){
		while(ptr < edg.size() && edg[ptr].x >= i){
			if(!disj.uni(edg[ptr].s, edg[ptr].e)){
				add_edge(edg[ptr].s, edg[ptr].e);
			}
			ptr++;
		}
		if(query[i].typ == 2){
			dap.push_back(query_fuck(query[i].x, query[i].y));
		}
	}
	reverse(dap.begin(), dap.end());
	for(auto &i : dap){
		if(i) puts("TAK");
		else puts("NIE");
	}
}