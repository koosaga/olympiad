#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

struct disj{
	int pa[200005];
	void init(int n){
		for(int i=1; i<=n; i++) pa[i] = i;
	}
	int find(int x){
		return pa[x] = (pa[x]== x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

struct edg{int s, e, x;};
vector<edg> v;

int n, m;
int l[200005], r[200005];
int tl[200005], tr[200005];

vector<pi> gph[200005];

int dist[200005];

void dfs(int x, int p){
	for(auto &i : gph[x]){
		if(i.second == p) continue;
		dist[i.second] = min(dist[x], i.first);
		dfs(i.second, x);
	}
}

int main(){
	memset(dist, -1, sizeof(dist));
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		scanf("%d %d",&l[i],&r[i]);
		tl[i] = tr[i] = 1e9;
	}
	for(int i=0; i<m; i++){
		int p, q;
		scanf("%d %d",&p,&q);
		if(q == 1){
			tl[p] = min(tl[p], i);
		}
		else{
			tr[p] = min(tr[p], i);
		}
	}
	for(int i=1; i<=n; i++){
		if(~l[i]){
			v.push_back({i, l[i], tl[i]});
		}
		if(~r[i]){
			v.push_back({i, r[i], tr[i]});
		}
	}
	disj.init(n);
	sort(v.begin(), v.end(), [&](const edg &a, const edg &b){
		return a.x > b.x;
	});
	for(int i=0; i<v.size(); i++){
		if(disj.uni(v[i].s, v[i].e)){
			gph[v[i].s].push_back({v[i].x, v[i].e});
			gph[v[i].e].push_back({v[i].x, v[i].s});
		}
	}
	dist[1] = 1e9;
	dfs(1, -1);
	for(int i=1; i<=n; i++){
		if(dist[i] > 1e8) puts("-1");
		else printf("%d\n", dist[i]);
	}
}
