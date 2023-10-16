#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
const int MAXN = 250005;
using lint = long long;
using pi = pair<lint, int>;

int n, vis[MAXN];
int csz[MAXN], msz[MAXN];
vector<pi> gph[3][MAXN];

void dfsc(int x, int p, vector<int> &dfn){
	csz[x] = 1;
	msz[x] = 0;
	dfn.push_back(x);
	for(auto &i : gph[0][x]){
		if(i.second != p && !vis[i.second]){
			dfsc(i.second, x, dfn);
			csz[x] += csz[i.second];
			msz[x] = max(msz[x], csz[i.second]);
		}
	}
}

int get_center(int x){
	vector<int> dfn;
	dfsc(x, -1, dfn);
	pi ret(1e9, 1e9);
	for(auto &i : dfn){
		int foo = max(msz[i], sz(dfn) - csz[i]);
		ret = min(ret, pi(foo, i));
	}
	return ret.second;
}

struct edg{ int s, e; lint x; };

namespace tree{
	int lg[2*MAXN], din[MAXN], dout[MAXN], piv;
	int lev[MAXN];
	lint dep[MAXN];
	pi spt[19][MAXN * 2];
	void dfs(int x, int p){
		din[x] = ++piv;
		spt[0][din[x]] = pi(lev[p], p);
		for(auto &i : gph[1][x]){
			if(i.second != p){
				lev[i.second] = lev[x] + 1;
				dep[i.second] = dep[x] + i.first;
				dfs(i.second, x);
			}
		}
		dout[x] = ++piv;
		spt[0][dout[x]] = pi(lev[p], p);
	}
	void init(){
		dfs(1, 0);
		for(int i=1; i<=2*n; i++){
			lg[i] = lg[i-1];
			while((2 << lg[i]) <= i) lg[i]++;
		}
		for(int i=1; i<19; i++){
			for(int j=1; j<=2*n; j++){
				spt[i][j] = spt[i-1][j];
				if(j + (1<<(i-1)) <= 2*n) spt[i][j] = min(spt[i][j], spt[i-1][j + (1<<(i-1))]);
			}
		}
	}
	int lca(int x, int y){
		if(din[x] > din[y]) swap(x, y);
		if(dout[y] <= dout[x]) return x;
		// [dout[y], din[x]]
		int l = lg[din[y] - dout[x] + 1];
		return min(spt[l][dout[x]], spt[l][din[y] - (1<<l) + 1]).second;
	}
	vector<edg> compress(vector<int> &v){
		auto in = [&](int x, int y){
			return din[x] <= din[y] && dout[y] <= dout[x];
		};
		v.resize(unique(v.begin(), v.end()) - v.begin());
		vector<int> stk;
		vector<edg> dap;
		for(auto &i : v){
			while(sz(stk) && !in(stk.back(), i)) stk.pop_back();
			if(sz(stk)){
				dap.push_back({stk.back(), i, dep[i] - dep[stk.back()]});
			}
			stk.push_back(i);
		}
		return dap;
	}
}

lint dap[MAXN];
lint dp[MAXN], val[MAXN], pdp[MAXN];

void get_shortest_path(vector<pi> cnd, vector<int> dfn){
	for(auto &i : cnd) val[i.second] = dp[i.second] = i.first;
	reverse(dfn.begin(), dfn.end());
	for(auto &i : dfn){
		for(auto &j : gph[2][i]){
			dp[i] = min(dp[i], dp[j.second] + j.first);
		}
	}
	reverse(dfn.begin(), dfn.end());
	for(auto &i : dfn){
		if(sz(gph[2][i]) == 0) continue;
		lint curMin = min(pdp[i], val[i]);
		reverse(gph[2][i].begin(), gph[2][i].end());
		for(auto &j : gph[2][i]){
			pdp[j.second] = min(pdp[j.second], j.first + curMin);
			curMin = min(curMin, dp[j.second] + j.first);
		}
		curMin = min(pdp[i], val[i]);
		reverse(gph[2][i].begin(), gph[2][i].end());
		for(auto &j : gph[2][i]){
			pdp[j.second] = min(pdp[j.second], j.first + curMin);
			curMin = min(curMin, dp[j.second] + j.first);
		}
	}
	for(auto &i : cnd){
		lint ans = pdp[i.second];
		for(auto &j : gph[2][i.second]){
			ans = min(ans, dp[j.second] + j.first);
		}
		dap[i.second] = min(dap[i.second], i.first + ans);
	}
}

void dfs(int x, int p, lint d, vector<pi> &dfn){
	dfn.emplace_back(d, x);
	for(auto &i : gph[0][x]){
		if(i.second != p && !vis[i.second]){
			dfs(i.second, x, d + i.first, dfn);
		}
	}
}

vector<int> toComp[MAXN];
vector<pi> dfn[MAXN];

pi cnt[MAXN * 40];
int ptr[MAXN * 2];

void SORT(){
	memset(ptr, 0, sizeof(ptr));
	for(int i=1; i<=n; i++){
		for(auto &j : toComp[i]){
			ptr[tree::din[j]]++;
		}
	}
	for(int i=1; i<=n*2; i++){
		ptr[i] += ptr[i-1];
	}
	int sum = ptr[2*n];
	for(int i=1; i<=n; i++){
		for(auto &j : toComp[i]){
			cnt[--ptr[tree::din[j]]] = pi(i, j);
		}
		toComp[i].clear();
	}
	for(int i=0; i<sum; i++){
		toComp[cnt[i].first].push_back(cnt[i].second);
	}
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<2; i++){
		for(int j=1; j<n; j++){
			int s, e, x; scanf("%d %d %d",&s,&e,&x);
			gph[i][s].emplace_back(x, e);
			gph[i][e].emplace_back(x, s);
		}
	}
	tree::init();
	memset(dap, 0x3f, sizeof(dap));
	memset(dp , 0x3f, sizeof(dp ));
	memset(pdp, 0x3f, sizeof(pdp));
	memset(val, 0x3f, sizeof(val));
	queue<int> que;
	que.push(1);
	while(!que.empty()){
		int x = que.front(); que.pop();
		x = get_center(x);
		vis[x] = 1;
		dfs(x, 0, 0, dfn[x]);
		if(sz(dfn[x]) == 1) continue;
		for(auto &i : dfn[x]){
			toComp[x].push_back(i.second);
		}
		for(auto &i : gph[0][x]){
			if(!vis[i.second]){
				que.push(i.second);
			}
		}
	}
	SORT();
	for(int i=1; i<=n; i++){
		int foo = sz(toComp[i]);
		for(int j=1; j<foo; j++){
			int bar = tree::lca(toComp[i][j-1], toComp[i][j]);
			toComp[i].push_back(bar);
		}
	}
	SORT();
	for(int i=1; i<=n; i++){
		if(sz(toComp[i]) == 0) continue;
		auto edgList = tree::compress(toComp[i]);
		for(auto &i : edgList){
			gph[2][i.s].emplace_back(i.x, i.e);
		}
		get_shortest_path(dfn[i], toComp[i]);
		for(auto &i : toComp[i]){
			gph[2][i].clear();
			dp[i] = pdp[i] = val[i] = 1e18;
		}
	}
	for(int i=1; i<=n; i++) printf("%lld\n", dap[i]);
}


