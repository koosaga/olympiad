#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct disj{
	int pa[500005];
	void init(int n){
		for(int i=1; i<=n; i++) pa[i] = i;
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

int n, q, a[500005];
int deg[500005], dep[500005], idx[500005], comp[500005];
int par[19][500005], sz[500005];
vector<int> gph[500005];

void dfs(int x, int p, int c){
	comp[x] = c;
	for(auto &i : gph[x]){
		if(i != p){
			par[0][i] = x;
			dep[i] = dep[x] + 1;
			dfs(i, x, c);
		}
	}
}

int getpar(int x, int c){
	for(int i=0; i<19; i++){
		if((c >> i) & 1) x = par[i][x];
	}
	return x;
}

int lca(int s, int e){
	if(dep[s] < dep[e]) e = getpar(e, dep[e] - dep[s]);
	else s = getpar(s, dep[s] - dep[e]);
	for(int i=18; i>=0; i--){
		if(par[i][s] != par[i][e]){
			s = par[i][s];
			e = par[i][e];
		}
	}
	if(s != e) return par[0][s];
	return s;
}

void solve(int s, int e){
	int p1 = dep[s];
	int p2 = dep[e];
	s = getpar(s, dep[s]);
	e = getpar(e, dep[e]);
	int dx = (idx[e] - idx[s] + sz[s]) % sz[s];
	pi c1 = pi(p1 + dx, p2);
	pi c2 = pi(p1, p2 + sz[e] - dx);
	pi t = min(c1, c2, [&](const pi &a, const pi &b){
		if(max(a.first, a.second) != max(b.first, b.second)){
			return max(a.first, a.second) < max(b.first, b.second);
		}
		if(min(a.first, a.second) != min(b.first, b.second)){
			return min(a.first, a.second) < min(b.first, b.second);
		}
		return a.first - a.second >= b.first - b.second;
	});
	printf("%d %d\n", t.first, t.second);
}

int main(){
	scanf("%d %d",&n,&q);
	disj.init(n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		disj.uni(i, a[i]);
		deg[a[i]]++;
	}
	queue<int> que;
	for(int i=1; i<=n; i++){
		if(!deg[i]) que.push(i);
	}
	while(!que.empty()){
		int x = que.front();
		que.pop();
		deg[a[x]]--;
		gph[a[x]].push_back(x);
		if(!deg[a[x]]) que.push(a[x]);
	}
	int c = 0;
	for(int i=1; i<=n; i++){
		if(deg[i]){
			dfs(i, -1, ++c);
		}
	}
	for(int i=1; i<19; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	for(int i=1; i<=n; i++){
		if(!idx[i] && deg[i]){
			int cur = i, p = 0;
			while(!idx[cur]){
				idx[cur] = ++p;
				cur = a[cur];
			}
			for(int i=0; i<p; i++){
				sz[cur] = p;
				cur = a[cur];
			}
		}
	}
	for(int i=0; i<q; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		if(disj.find(s) != disj.find(e)) puts("-1 -1");
		else{
			if(comp[s] != comp[e]) solve(s, e);
			else{
				int l = lca(s, e);
				printf("%d %d\n", dep[s] - dep[l], dep[e] - dep[l]);
			}
		}
	}
}
