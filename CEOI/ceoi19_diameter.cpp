#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using lint = long long;
using pi = pair<int, int>;
 
struct edg{
	int pos; lint cst;
	int idx;
};
 
int n, q; lint w;
vector<edg> gph[MAXN];
vector<int> updList[MAXN];
bool vis[MAXN];

struct segtree{
	vector<lint> tree, lazy;
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		tree.resize(2 * lim);
		lazy.resize(2 * lim);
	}
	void lazydown(int p){
		lint cur = lazy[p]; lazy[p] = 0;
		for(int j=0; j<2; j++){
			lazy[2*p+j] += cur;
			tree[2*p+j] += cur;
		}
	}
	void add(int s, int e, int ps, int pe, int p, lint v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p] += v;
			lazy[p] += v;
			return;
		}
		int pm = (ps+pe)/2;
		lazydown(p);
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		tree[p] = max(tree[2*p], tree[2*p+1]);
	}
	lint query(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return -1e18;
		if(s <= ps && pe <= e) return tree[p];
		int pm = (ps + pe) / 2;
		lazydown(p);
		return max(query(s, e, ps, pm, 2*p), query(s, e, pm+1, pe, 2*p+1));
	}
};

struct dcmp{
	int idx;
	map<int, int> din, dout;
	int piv;
	vector<lint> ds;
	vector<pi> intv;
	vector<lint> assoc;
	multiset<lint> maxVal;
	lint ans;

	segtree DS;
}cd[MAXN];

priority_queue<pair<lint, int>> pq;

lint query(){
	while(!pq.empty() && cd[pq.top().second].ans != pq.top().first){
		pq.pop();
	}
	if(pq.empty()) return 0;
	return pq.top().first;
}
 
void update(int e, int x, int y, lint d){
	for(auto &i : updList[e]){
		if(cd[i].din[x] > cd[i].din[y]) swap(x, y);
		int l = cd[i].din[y];
		int r = cd[i].dout[y];

		cd[i].DS.add(l, r - 1, 0, cd[i].piv - 1, 1, d);

		int pos = lower_bound(cd[i].intv.begin(), cd[i].intv.end(), pi(l, 1e9)) 
		- cd[i].intv.begin() - 1;
		cd[i].maxVal.erase(cd[i].maxVal.find(cd[i].assoc[pos]));

		cd[i].assoc[pos] = 
		cd[i].DS.query(cd[i].intv[pos].first, cd[i].intv[pos].second - 1, 
		0, cd[i].piv - 1, 1);

		cd[i].maxVal.insert(cd[i].assoc[pos]);
		assert(cd[i].maxVal.size());
		if(cd[i].maxVal.size() == 1) cd[i].ans = *cd[i].maxVal.rbegin();
		else{
			auto cur = prev(cd[i].maxVal.end());
			cd[i].ans = *cur + *prev(cur);
		}
		pq.emplace(cd[i].ans, i);
	}
}
 
void dfs(int x, int p, dcmp &cd){
	cd.din[x] = cd.piv++;
	for(auto &i : gph[x]){
		if(i.pos != p && !vis[i.pos]){
			updList[i.idx].push_back(cd.idx);
			dfs(i.pos, x, cd);
		}
	}
	cd.dout[x] = cd.piv;
}

void sangsoo(int x, int p, dcmp &cd){
	for(auto &i : gph[x]){
		if(i.pos != p && !vis[i.pos]){
			cd.DS.add(cd.din[i.pos], cd.dout[i.pos] - 1, 0, cd.piv - 1, 1, i.cst);
			sangsoo(i.pos, x, cd);
		}
	}
}

void build(int v, dcmp &cd){
	cd.idx = v;
	dfs(v, -1, cd);
	cd.DS.init(cd.piv);
	sangsoo(v, -1, cd);
	for(auto &i : gph[v]){
		if(vis[i.pos]) continue;
		cd.intv.emplace_back(cd.din[i.pos], cd.dout[i.pos]);
	}
	sort(cd.intv.begin(), cd.intv.end());
	for(int i=0; i<cd.intv.size(); i++){
		int l = cd.intv[i].first, r = cd.intv[i].second;
		lint ans = cd.DS.query(l, r - 1, 0, cd.piv - 1, 1);
		cd.maxVal.insert(ans);
		cd.assoc.push_back(ans);
	}
	if(cd.maxVal.size() == 0) cd.ans = 0;
	else if(cd.maxVal.size() == 1) cd.ans = *cd.maxVal.rbegin();
	else{
		auto cur = prev(cd.maxVal.end());
		cd.ans = *cur + *prev(cur);
	}
	pq.emplace(cd.ans, v);
}

vector<int> dfn;
int sz[MAXN], msz[MAXN];
 
void dfsc(int x, int p){
	dfn.push_back(x);
	sz[x] = 1;
	msz[x] = 0;
	for(auto &i : gph[x]){
		if(!vis[i.pos] && i.pos != p){
			dfsc(i.pos, x);
			sz[x] += sz[i.pos];
			msz[x] = max(msz[x], sz[i.pos]);
		}
	}
}
 
int get_center(int x){
	dfsc(x, -1);
	pi ret(1e9, 1e9);
	for(auto &i : dfn){
		int mxv = max(msz[i], (int)dfn.size() - sz[i]);
		ret = min(ret, pi(mxv, i));
	}
	dfn.clear();
	return ret.second;
}
 
int main(){
	lint w;
	scanf("%d %d %lld",&n,&q,&w);
	vector<int> S(n - 1), E(n - 1); 
	vector<lint> X(n - 1);
	for(int i=0; i<n-1; i++){
		int s, e; lint x;
		scanf("%d %d %lld",&s,&e,&x);
		gph[s].push_back({e, x, i});
		gph[e].push_back({s, x, i});
		tie(S[i], E[i], X[i]) = make_tuple(s, e, x);
	}
	queue<int> que;
	que.push(1);
	while(!que.empty()){
		int x = que.front(); que.pop();
		x = get_center(x);
		build(x, cd[x]);
		vis[x] = 1;
		for(auto &i : gph[x]){
			if(!vis[i.pos]){
				que.push(i.pos);
			}
		}
	}
	lint last = 0;
	while(q--){
		lint d, e; scanf("%lld %lld",&d,&e);
		d = (d + last) % (n - 1);
		e = (e + last) % w;
		update(d, S[d], E[d], e - X[d]);
		X[d] = e;
		last = query();
		printf("%lld\n", last);
	}
}

