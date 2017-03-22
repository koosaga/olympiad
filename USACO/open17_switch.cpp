#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;

struct disj{
	int pa[200005];
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

struct bkt{
	priority_queue<int, vector<int>, greater<int> > pq;
	int a[200005];
	void toggle(int x){
		a[x] ^= 1;
		if(a[x]) pq.push(x);
	}
	bool on(int x){
		return a[x];
	}
	int query(){
		while(!a[pq.top()]) pq.pop();
		return pq.top();
	}
}bkt;

struct edg{
	int s, e, x;
}a[200005];

int c[200005];
int n, m, k, q;
vector<pi> gph[200005];
int par[200005], pae[200005];
set<pi> h[200005];

void dfs(int x){
	for(auto &i : gph[x]){
		gph[i.second].erase(find(gph[i.second].begin(), gph[i.second].end(), pi(i.first, x)));
		par[i.second] = x;
		pae[i.second] = i.first;
		dfs(i.second);
	}
}

int main(){
	freopen("grass.in", "r", stdin);
	freopen("grass.out", "w", stdout);
	scanf("%d %d %d %d",&n,&m,&k,&q);
	for(int i=0; i<m; i++){
		scanf("%d %d %d",&a[i].s,&a[i].e,&a[i].x);
	}
	sort(a, a+m, [&](const edg &a, const edg &b){
		return a.x < b.x;
	});
	vector<edg> aux;
	int p = 0;
	disj.init(n);
	for(int i=0; i<m; i++){
		if(disj.uni(a[i].s, a[i].e)){
			aux.push_back(a[i]);
			gph[a[i].s].push_back(pi(p, a[i].e));
			gph[a[i].e].push_back(pi(p, a[i].s));
			p++;
		}
	}
	m = n-1;
	for(int i=0; i<m; i++) a[i] = aux[i];
	dfs(1);
	for(int i=1; i<=n; i++){
		scanf("%d",&c[i]);
	}
	for(int i=1; i<=n; i++){
		for(auto &j : gph[i]){
			h[i].insert(pi(c[j.second], j.first));
		}
		int prv = -1;
		for(auto &j : h[i]){
			if(j.first == prv) continue;
			prv = j.first;
			if(c[i] != prv) bkt.toggle(j.second);
		}
	}
	while(q--){
		int x, d;
		scanf("%d %d",&x,&d);
		if(c[x] == d){
			printf("%d\n", a[bkt.query()].x);
			continue;
		}
		int prv = c[x];
		int nxt = d;
		c[x] = d;
		auto l = h[x].lower_bound(pi(prv, -1));
		if(l != h[x].end() && l->first == prv){
			bkt.toggle(l->second);
		}
		l = h[x].lower_bound(pi(nxt, -1));
		if(l != h[x].end() && l->first == nxt){
			bkt.toggle(l->second);
		}
		if(x != 1){
			int p = par[x];
			int e = pae[x];
			h[p].erase(pi(prv, e));
			if(bkt.on(e)) bkt.toggle(e);

			l = h[p].lower_bound(pi(prv, -1));
			if(l != h[p].end() && l->first == prv){
				if(!bkt.on(l->second)) bkt.toggle(l->second);
			}

			l = h[p].lower_bound(pi(nxt, -1));
			if(l != h[p].end() && l->first == nxt){
				if(bkt.on(l->second)) bkt.toggle(l->second);
			}

			h[p].insert(pi(nxt, e));

			l = h[p].lower_bound(pi(nxt, -1));
			if(l != h[p].end() && l->first == nxt){
				if(!bkt.on(l->second)) bkt.toggle(l->second);
			}

			l = h[p].lower_bound(pi(c[p], -1));
			if(l != h[p].end() && l->first == c[p]){
				if(bkt.on(l->second)) bkt.toggle(l->second);
			}
		}
		printf("%d\n", a[bkt.query()].x);
	}
}
