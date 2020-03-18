#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
typedef long long lint;
typedef pair<int, int> pi;

double cur_pos;

struct circ{
	int x, y, r, t, idx;
};

double func(circ c){
	double dx = abs(c.x - cur_pos);
	double r = (c.r - 0.001);
	double y = sqrt(r * r - dx * dx);
	if(c.t == 0) return c.y - y;
	return c.y + y;
}

bool same(circ a, circ b){
	return a.idx == b.idx && a.t == b.t;
}

auto cmp = [](circ a, circ b){ return func(a) < func(b); };
set<circ, decltype(cmp)> s(cmp);

struct event{
	circ val;
	int pos, mode;
	bool operator<(const event &e)const{
		return pi(pos, mode) < pi(e.pos, e.mode);
	}
};

vector<event> v;
int n, q;
int x[MAXN], y[MAXN], r[MAXN];
int par[MAXN];

bool in(int v, int w){
	int dx = x[v] - x[w];
	int dy = y[v] - y[w];
	return 1ll * dx * dx + 1ll * dy * dy <= 1ll * r[v] * r[v];
}


vector<int> gph[MAXN];
int dp[MAXN][2], dap[MAXN];

void dfs(int x){
	for(auto &i : gph[x]){
		dfs(i);
		dp[x][1] += dp[i][0];
		dp[x][0] += dp[i][1];
	}
	dp[x][1] += 1;
	dp[x][1] = max(dp[x][1], dp[x][0]);
	if(x > n){
		dap[x] = max(dp[x][0], dp[x][1]);
		dp[x][0] = dp[x][1] = 0;
		for(auto &i : gph[x]){
			dp[x][0] += dp[i][0];
			dp[x][1] += dp[i][1];
		}
	}
}

void add_edge(int x, int y){
	if(~par[y] || y == 0) return;
	if(!in(x, y)) x = par[x];
	assert(in(x, y));
	par[y] = x;
	gph[x].push_back(y);
}

int main(){
	memset(par, -1, sizeof(par));
	scanf("%d %d",&n,&q);
	for(int i=1; i<=n+q; i++){
		scanf("%d %d %d",&x[i],&y[i],&r[i]);
	}
	r[0] = 1e8;
	for(int i=0; i<=n+q; i++){
		circ c1 = {x[i], y[i], r[i], 0, i};
		circ c2 = {x[i], y[i], r[i], 1, i};
		v.push_back({c1, x[i] - r[i], 1});
		v.push_back({c2, x[i] - r[i], 1});
		v.push_back({c1, x[i] + r[i], 0});
		v.push_back({c2, x[i] + r[i], 0});
	}
	sort(v.begin(), v.end());
	for(auto &i : v){
		if(i.mode == 0){
			cur_pos = i.pos - 0.01;
			auto l = s.lower_bound(i.val);
			if(l == s.end() || !same(*l, i.val)) l--;
			assert(same(*l, i.val));
			s.erase(l);
		}
		else{
			cur_pos = i.pos + 0.01;
			auto l = s.lower_bound(i.val);
			if(l != s.end()){
				add_edge(l->idx, i.val.idx);
			}
			if(l != s.begin()){
				add_edge(prev(l)->idx, i.val.idx);
			}
			s.insert(i.val);
		}
	}
	dfs(0);
	for(int i=n+1; i<=n+q; i++) printf("%d\n", dap[i]);
}

