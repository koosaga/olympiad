#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int oo = 1e9;

int n, m, a[100005];
vector<pi> intv[100005];
vector<int> ins[100005], del[100005];

struct rmq{
	struct node{
		int fmin, fminf, smin, sminf;
	}tree[270000];
	node merge(node x, node y){
		if(x.fminf == 0) return y;
		if(y.fminf == 0) return x;
		node ret;
		if(x.fminf == y.fminf){
			ret.fminf = x.fminf;
			ret.fmin = min(x.fmin, y.fmin);
			if(x.smin < y.smin){
				ret.smin = x.smin;
				ret.sminf = x.sminf;
			}
			else{
				ret.smin = y.smin;
				ret.sminf = y.sminf;
			}
		}
		else{
			if(x.fmin > y.fmin) swap(x, y);
			ret.fmin = x.fmin;
			ret.fminf = x.fminf;
			if(y.fmin < x.smin){
				ret.smin = y.fmin;
				ret.sminf = y.fminf;
			}
			else{
				ret.smin = x.smin;
				ret.sminf = x.sminf;
			}
		}	
		return ret;
	}
	int lim;
	void init(int n, int *a, int *comp){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 270000, (node){oo, 0, oo, 0});
		for(int i=1; i<=n; i++){
			tree[i + lim] = {a[i], comp[i], oo, 0};
		}
		for(int i=lim; i; i--){
			tree[i] = merge(tree[2*i], tree[2*i+1]);
		}
	}
	node query(int s, int e){
		s += lim;
		e += lim;
		node ret = {oo, 0, oo, 0};
		while(s < e){
			if(s%2 == 1) ret = merge(ret, tree[s++]);
			if(e%2 == 0) ret = merge(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = merge(ret, tree[s]);
		return ret;
	}
}seg;

struct seg2{
	multiset<int> danmal[100005];
	pi tree[270000];
	int lim;
	void init(int n){
		for(int i=1; i<=n; i++) danmal[i].clear();
		fill(tree, tree + 270000, pi(1e9, 1e9));
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void add(int x, int v){
		danmal[x].insert(v);
		tree[x + lim] = pi(*danmal[x].begin(), x);
		x += lim;
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	void del(int x, int v){
		danmal[x].erase(danmal[x].find(v));
		tree[x + lim].first = (danmal[x].size() ? *danmal[x].begin() : oo);
		tree[x + lim].second = x;
		x += lim;
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(1e9, 1e9);
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}seg2;

pi ans[100005];
int comp[100005];

void get_closest(){
	seg.init(n, a, comp);
	seg2.init(n);
	fill(ans + 1, ans + n + 1, pi(1e9, 1e9));
	for(int i=1; i<=n; i++){
		for(auto &j : intv[i]){
			auto w = seg.query(j.first, j.second);
			if(w.fminf == comp[i]){
				ans[comp[i]] = min(ans[comp[i]], pi(a[i] + w.smin, w.sminf));
			}
			else{
				ans[comp[i]] = min(ans[comp[i]], pi(a[i] + w.fmin, w.fminf));
			}
		}
		for(auto &j : ins[i]){
			seg2.add(comp[j], a[j]);
		}
		for(auto &j : del[i]){
			seg2.del(comp[j], a[j]);
		}
		auto w = min(seg2.query(1, comp[i] - 1), seg2.query(comp[i] + 1, n));
		ans[comp[i]] = min(ans[comp[i]], pi(a[i] + w.first, w.second));
	}
}

struct disj{
	int pa[100005];
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

int main(){
	scanf("%d %d",&n,&m);
	disj.init(n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	for(int i=0; i<m; i++){
		int x, s, e;
		scanf("%d %d %d",&x,&s,&e);
		intv[x].push_back(pi(s, e));
		ins[s].push_back(x);
		del[e+1].push_back(x);
	}
	lint ret = 0;
	int conn = 0;
	while(conn < n-1){
		for(int i=1; i<=n; i++){
			comp[i] = disj.find(i);
		}
		get_closest();
		for(int i=1; i<=n; i++){
			if(comp[i] != i) continue;
			if(disj.uni(i, ans[i].second)){
				conn++;
				ret += ans[i].first;
			}
		}
	}
	cout << ret;
}

