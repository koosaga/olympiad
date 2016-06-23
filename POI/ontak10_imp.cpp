#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int inv2 = 5e8 + 4;
 
int n, w[46], adj[46][46];
lint bt[46];
int mx[1<<23];
int cnt[1<<23];
int cen;
 
int ret;
lint way;
 
void dfs(int x, int b, lint l, int cost){
	if(x == cen){
		int p = mx[l >> cen];
		int wayt = cnt[l >> cen];
		if(p + cost > ret){
			ret = p + cost;
			way = 0;
		}
		if(p + cost == ret){
			way += wayt;
		}
		return;
	}
	dfs(x+1, b, l, cost);
	if((l >> x) & 1) dfs(x+1, b|(1<<x), l & (~bt[x]), cost + w[x]);
}
 
void dfs2(int x, lint b, lint l, int cost){
	if(x == n){
		mx[b >> cen] = cost;
		cnt[b >> cen] = 1;
		return;
	}
	dfs2(x+1, b, l, cost);
	if((l >> x) & 1) dfs2(x+1, b|(1ll<<x), l & (~bt[x]), cost + w[x]);
}
 
void input();
 
int main(){
	input();
	if(n == 0){
		puts("0 1");
		return 0;
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(adj[i][j]) bt[i] |= (1ll << j);
		}
	}
	dfs2(cen, 0, (1ll << n) - 1, 0);
	for(int i=0; i<n-cen; i++){
		for(int j=0; j<(1<<(n - cen)); j++){
			if((j >> i) & 1){
				if(mx[j] < mx[j ^ (1<<i)]){
					mx[j] = mx[j ^ (1<<i)];
					cnt[j] = 0;
				}
				if(mx[j] == mx[j ^ (1<<i)]){
					cnt[j] += cnt[j ^ (1<<i)];
				}
			}
		}
	}
	dfs(0, 0, (1ll << n) - 1, 0);
	printf("%d %lld", ret, way);
}
 
struct disj{
	int pa[255], sz[255], mark[255];
	void init(int n){
		for(int i=0; i<=n; i++){
			pa[i] = i, sz[i] = 1, mark[i] = 0;
		}
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p, sz[p] += sz[q], mark[p] |= mark[q];
		return 1;
	}
}disj;
 
void input(){
	int nn, m, p;
	cin >> nn >> m >> p;
	disj.init(nn);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		disj.uni(s, e);
	}
	vector<pi> unr;
	for(int i=0; i<p; i++){
		int s, e;
		scanf("%d %d",&s, &e);
		unr.push_back({s, e});
		if(disj.find(s) == disj.find(e)){
			disj.mark[disj.find(s)] = 1;
		}
	}
	map<int, int> mp;
	for(int i=1; i<=nn; i++){
		int p = disj.find(i);
		if(disj.mark[p]) continue;
		if(mp.find(p) != mp.end()) continue;
		int x = mp.size();
		mp[p] = x;
		w[x] = disj.sz[p];
	}
	for(auto &i : unr){
		if(mp.find(disj.find(i.first)) == mp.end()) continue;
		int p = mp[disj.find(i.first)], q = mp[disj.find(i.second)];
		adj[p][q] = adj[q][p] = 1;
	}
	n = mp.size();
	cen = n/2;
}