#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, int> pi;
#define sz(v) ((int)(v).size())
const int MAXN = 200005;
const int mod = 998244353;
const lint oo = 2e18;
 
struct bit{
	int tree[MAXN];
	void mark(int x){
		for(int i=x; i<MAXN; i+=i&-i){
			tree[i] ^= 1;
		}
	}
	int query(int x){
		int ret = 0;
		for(int i=x; i; i-=i&-i){
			ret ^= tree[i];
		}
		return ret;
	}
}bit;
 
struct edge{
	int dir; // 1: down, 0:up
	lint cost;
}pae[MAXN];
 
int n, typ[MAXN], par[MAXN];
int chn[MAXN], sz[MAXN], din[MAXN], dout[MAXN], rev[MAXN], clen[MAXN], piv;
vector<int> ord;
vector<pi> gph[MAXN];
 
void dfs(int x){
	sz[x] = 1;
	for(auto &i : gph[x]){
		gph[i.second].erase(find(gph[i.second].begin(), gph[i.second].end(), pi(i.first, x)));
		par[i.second] = x;
		typ[i.second] = 3 - typ[x];
		pae[i.second] = {typ[x] == 1, typ[x] == 1 ? -i.first : i.first};
		dfs(i.second);
		sz[x] += sz[i.second];
	}
	sort(gph[x].begin(), gph[x].end(), [&](const pi &a, const pi &b){
		return sz[a.second] > sz[b.second];
	});
}
 
void hld(int x){
	ord.push_back(x);
	clen[chn[x]]++;
	din[x] = ++piv;
	rev[din[x]] = x;
	if(sz(gph[x])){
		chn[gph[x][0].second] = chn[x];
		hld(gph[x][0].second);
		for(int i=1; i<sz(gph[x]); i++){
			chn[gph[x][i].second] = gph[x][i].second;
			hld(gph[x][i].second);
		}
	}
	dout[x] = piv;
}
 
struct optAnswer{
	lint ans; 
	int src, snk;
	bool operator==(const optAnswer &o)const{
		return make_tuple(ans, src, snk) == make_tuple(o.ans, o.src, o.snk);
	}
	bool operator<(const optAnswer &o)const{
		return ans < o.ans;
	}
};
 
struct node{
	pi dp_value;
	int fromX, fromY;
	bool operator<(const node &n)const{
		return dp_value < n.dp_value;
	}
};
 
priority_queue<pair<optAnswer, optAnswer*> > pq;
priority_queue<node> sonMax[MAXN][2];
pi dp[MAXN][2];
pi chainDP[MAXN][2];
optAnswer chainOpt[MAXN], vtxOpt[MAXN];
 
struct seg{
	struct node{
		pi L[2], R[2];
		optAnswer opt[2];
		int dir_sum;
		int node_sum; // count sum of "nodes" (just subtree)
		lint length_sum; // count sum of lengths (just subtree)
		int leftist; // left border's ACTUAL direction
		int diffL, diffR;
		int lazy;
	};
	void lazydown(int p){
		if(tree[p].lazy){
			for(int j=2*p; j<2*p+2; j++){
				tree[j].lazy ^= 1;
				tree[j].leftist ^= 1;
				tree[j].dir_sum = tree[j].node_sum - tree[j].dir_sum;
				swap(tree[j].opt[0], tree[j].opt[1]);
			}
			tree[p].lazy = 0;
		}
	}
	node make(int v){
		node ret;
		ret.L[0] = ret.R[0] = dp[rev[v]][0];
		ret.L[1] = ret.R[1] = dp[rev[v]][1];
		ret.L[0].first += pae[rev[v]].cost;
		ret.L[1].first -= pae[rev[v]].cost;
		ret.opt[0] = ret.opt[1] = {-oo, -1, -1};
		int qr1 = bit.query(v);
		int qr2 = bit.query(v + 1);
		ret.dir_sum = qr1;
		ret.node_sum = 1;
		ret.length_sum = pae[rev[v]].cost;
		ret.leftist = qr1;
		ret.diffL = qr1 != qr2;
		ret.diffR = qr1 != qr2;
		ret.lazy = 0;
		return ret;
	}
	node merge(node L, node R){
		auto optAnswer_merge = [&](pi x, pi y){
			return (optAnswer){x.first + y.first, x.second, y.second};
		};
		node ret;
		ret.lazy = 0;
		ret.dir_sum = L.dir_sum + R.dir_sum;
		ret.node_sum = L.node_sum + R.node_sum;
		ret.length_sum = L.length_sum + R.length_sum;
		ret.leftist = L.leftist;
		ret.diffL = L.diffL;
		ret.diffR = R.diffR;
		if(!L.diffL && !L.diffR && (L.dir_sum == 0 || L.dir_sum == L.node_sum)){
			for(int j = 0; j < 2; j++){
				auto RG = R.L[j];
				if(j == 0) RG.first += L.length_sum;
				else RG.first -= L.length_sum;
				ret.L[j] = max(L.L[j], RG);
			}
		}
		else{
			tie(ret.L[0], ret.L[1]) = make_pair(L.L[0], L.L[1]);
		}
		if(!R.diffR && (R.dir_sum == 0 || R.dir_sum == R.node_sum)){
			for(int j = 0; j < 2; j++){
				auto LG = L.R[j];
				if(j == 0) LG.first -= R.length_sum;
				else LG.first += R.length_sum;
				ret.R[j] = max(R.R[j], LG);
			}
		}
		else{
			tie(ret.R[0], ret.R[1]) = make_pair(R.R[0], R.R[1]);
		}
		ret.opt[0] = max(L.opt[0], R.opt[0]);
		ret.opt[1] = max(L.opt[1], R.opt[1]);
		if(R.leftist){
			swap(L.R[0], L.R[1]);
			swap(R.L[0], R.L[1]);
		}
		{
			auto LG = L.R[1];
			auto RG = R.L[0];
			ret.opt[0] = max(ret.opt[0], optAnswer_merge(LG, RG));
		}
		{
			auto LG = L.R[0];
			auto RG = R.L[1];
			ret.opt[1] = max(ret.opt[1], optAnswer_merge(LG, RG));
		}
		return ret;
	}
	vector<node> tree;
	void init(int s, int e, int p){
		if(s == e){
			if(sz(tree) <= p) tree.resize(p + 1);
			tree[p] = make(s);
			return;
		}
		int m = (s + e) / 2;
		init(s, m, 2 * p);
		init(m + 1, e, 2 * p + 1);
		tree[p] = merge(tree[2*p], tree[2*p+1]);
	}
	void update(int pos, int s, int e, int p){
		if(s == e){
			tree[p] = make(pos);
			return;
		}
		int m = (s + e) / 2;
		lazydown(p);
		if(pos <= m) update(pos, s, m, 2*p);
		else update(pos, m + 1, e, 2*p+1);
		tree[p] = merge(tree[2*p], tree[2*p+1]);
	}
	void reverse(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p].lazy ^= 1;
			tree[p].leftist ^= 1;
			tree[p].dir_sum = tree[p].node_sum - tree[p].dir_sum;
			swap(tree[p].opt[0], tree[p].opt[1]);
			return;
		}
		int pm = (ps + pe) / 2;
		lazydown(p);
		reverse(s, e, ps, pm, 2*p);
		reverse(s, e, pm+1, pe, 2*p+1);
		tree[p] = merge(tree[2*p], tree[2*p+1]);
	}
}seg[MAXN];
 
void recompute(int x){
	chainOpt[x] = seg[x].tree[1].opt[0];
	int dir = bit.query(din[x]);
	chainDP[din[x]][dir] = seg[x].tree[1].L[dir];
	if(x != 1){
		sonMax[par[x]][dir].push({chainDP[din[x]][dir], din[x], dir});
	}
	pq.emplace(chainOpt[x], &chainOpt[x]);
}
 
void relax(int i){
	auto merge = [&](pi x, pi y){
		return (optAnswer){x.first + y.first, x.second, y.second};
	};
	auto valid_son = [&](node x){
		return bit.query(x.fromX) == x.fromY && chainDP[x.fromX][x.fromY] == x.dp_value;
	};
	dp[i][0] = pi(-oo, i);
	dp[i][1] = pi(-oo, i);
	if(typ[i] != 3) dp[i][typ[i] - 1].first = 0;
	for(int j=0; j<2; j++){
		while(!sonMax[i][j].empty() && !valid_son(sonMax[i][j].top())){
			sonMax[i][j].pop();
		}
		if(!sonMax[i][j].empty()) dp[i][j] = max(dp[i][j], sonMax[i][j].top().dp_value);
	}
	vtxOpt[i] = merge(dp[i][0], dp[i][1]);
	pq.emplace(vtxOpt[i], &vtxOpt[i]);
	seg[chn[i]].update(din[i], din[chn[i]], din[chn[i]] + clen[chn[i]] - 1, 1);
	recompute(chn[i]);
}
 
void path_reverse(int x){
	for(int i=x; i; i=par[chn[i]]){
		int st = din[chn[i]];
		int ed = din[i];
		bit.mark(st);
		bit.mark(ed + 1);
		seg[chn[i]].reverse(st, ed, st, st + clen[chn[i]] - 1, 1);
		relax(i);
	}
}
 
lint aug(){
	auto valid_dp = [&](pair<optAnswer, optAnswer*> x){
		return *x.second == x.first;
	};
	while(!pq.empty() && !valid_dp(pq.top())) pq.pop();
	if(pq.empty()) return -oo;
	optAnswer ret = pq.top().first;
	int src = ret.src, snk = ret.snk;
	if(ret.ans < -1e17) return -oo;
	typ[src] = typ[snk] = 3;
	path_reverse(src);
	path_reverse(snk);
	return ret.ans;
}
 
int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int s, e, x; scanf("%d %d %d",&s,&e,&x);
		gph[s].emplace_back(x, e);
		gph[e].emplace_back(x, s);
	}
	typ[1] = 1;
	chn[1] = 1;
	dfs(1);
	hld(1);
	for(int i=1; i<=n; i++){
		if(chn[i] == i) seg[i].init(din[i], din[i] + clen[i] - 1, 1);
		if(pae[i].dir){
			bit.mark(din[i]);
			bit.mark(din[i] + 1);
		}
	}
	for(int i=sz(ord)-1; i>=0; i--) relax(ord[i]);
	vector<lint> dap;
	lint ans = 0;
	for(int i=1; i<=n-1; i++){
		ans += aug();
		if(ans < -1e17){
			ans = 0;
			printf("? ");
		}
		else printf("%lld ", ans);
	}
}
