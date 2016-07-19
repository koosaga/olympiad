#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
 
struct disj{
	int pa[100005];
	void init(int n){
		for(int i=1; i<=n; i++){
			pa[i] = i;
		}
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;
 
struct edg{
	int s, e, x;
	bool operator<(const edg &e)const{
		return x < e.x;
	}
}a[300005];
 
int n, m, k, s[22], e[22], c[100005];
vector<int> gph[100005];
 
vector<edg> resi;
int p, comp[100005];
lint csize[25];
 
int par[25], pae[25], chk[25], dep[25];
lint sz[25];
vector<pi> gph2[25];
 
void dfs2(int x, int p){
	sz[x] = csize[x];
	for(auto &i : gph2[x]){
		if(i.first == p) continue;
		chk[i.first] = i.second;
		dep[i.first] = dep[x] + 1;
		pae[i.first] = 1e9;
		par[i.first] = x;
		dfs2(i.first, x);
		sz[x] += sz[i.first];
	}
}
 
lint solve(int b){
	for(int i=1; i<=p; i++){
		gph2[i].clear();
	}
	disj.init(p);
	for(int i=0; i<k; i++){
		if((b >> i) & 1){
			if(!disj.uni(s[i], e[i])){
				return -1;
			}
			gph2[s[i]].push_back({e[i], 1});
			gph2[e[i]].push_back({s[i], 1});
		}
	}
	vector<edg> resi2;
	for(auto &i : resi){
		if(disj.uni(i.s, i.e)){
			gph2[i.s].push_back({i.e, 0});
			gph2[i.e].push_back({i.s, 0});
		}
		else{
			resi2.push_back(i);
		}
	}
	dfs2(1, -1);
	for(auto &i : resi2){
		if(dep[i.s] < dep[i.e]) swap(i.s, i.e);
		while(dep[i.s] > dep[i.e]){
			pae[i.s] = min(pae[i.s], i.x);
			i.s = par[i.s];
		}
		while(i.s != i.e){
			pae[i.s] = min(pae[i.s], i.x);
			pae[i.e] = min(pae[i.e], i.x);
			i.s = par[i.s];
			i.e = par[i.e];
		}
	}
	lint ret = 0;
	for(int i=2; i<=p; i++){
		if(chk[i]) ret += sz[i] * pae[i];
	}
	return ret;
}
 
void dfs(int x, int p){
	if(comp[x]) return;
	csize[p] += c[x];
	comp[x] = p;
	for(auto &i : gph[x]){
		dfs(i, p);
	}
}
 
void compress(){
	disj.init(n);
	for(int i=0; i<k; i++){
		disj.uni(s[i], e[i]);
	}
	for(int i=0; i<n-1; i++){
		if(disj.uni(a[i].s, a[i].e)){
			gph[a[i].e].push_back(a[i].s);
			gph[a[i].s].push_back(a[i].e);
		}
		else{
			resi.push_back(a[i]);
		}
	}
	for(int i=1; i<=n; i++){
		if(!comp[i]){
			dfs(i, ++p);
		}
	}
	for(auto &i : resi){
		i.s = comp[i.s];
		i.e = comp[i.e];
	}
	for(int i=0; i<k; i++){
		s[i] = comp[s[i]];
		e[i] = comp[e[i]];
	}
}
 
int main(){
	scanf("%d %d %d",&n,&m,&k);
	for(int i=0; i<m; i++){
		scanf("%d %d %d",&a[i].s, &a[i].e, &a[i].x);
	}
	for(int i=0; i<k; i++){
		scanf("%d %d",&s[i],&e[i]);
	}
	for(int i=1; i<=n; i++){
		scanf("%d",&c[i]);
	}
	sort(a, a+m);
	disj.init(n);
	vector<edg> tree;
	for(int i=0; i<m; i++){
		if(disj.uni(a[i].s, a[i].e)){
			tree.push_back(a[i]);
		}
	}
	for(int i=0; i<n-1; i++){
		a[i] = tree[i];
	}
	compress();
	lint ret = 0;
	for(int i=1; i<(1<<k); i++){
		ret = max(ret, solve(i));
	}
	cout << ret;
}