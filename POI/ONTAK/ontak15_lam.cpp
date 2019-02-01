#include <bits/stdc++.h>
typedef long long lint;
using namespace std;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

lint ipow(lint x, lint p){
	lint ret = 1, piv = x % mod;
	while(p){
		if(p&1) ret *= piv;
		piv *= piv;
		ret %= mod;
		piv %= mod;
		p >>= 1;
	}
	return ret % mod;
}

int n, m, c, root;
int torun[100005], adj[10][10], col[100005], cnt1;
int dep[100005], vis[100005], deg[100005];
vector<int> gph[100005], v;
vector<int> cgph[100005];

lint dp[100005][10];
lint cnt_same[100005], cnt_diff[100005];

void dfs2(int x, int m){
	for(int j=0; j<=m; j++){
		dp[x][j] = 1;
	}
	for(auto &j : cgph[x]){
		if(dep[j] > dep[x]){
			dfs2(j, m);
			for(int k=0; k<m; k++){
				lint cur = 0;
				for(int l=0; l<=m; l++){
					lint dpv = dp[j][l];
					if(l == m) dpv = dpv * (c - m) % mod;
					if(k == l) cur += dpv * cnt_same[dep[j] - dep[x] - 1] % mod;
					else cur += dpv * cnt_diff[dep[j] - dep[x] - 1] % mod;
				}
				cur %= mod;
				dp[x][k] *= cur;
				dp[x][k] %= mod;
			}
			lint cur = 0;
			for(int l=0; l<m; l++){
				lint dpv = dp[j][l] * cnt_diff[dep[j] - dep[x] - 1] % mod;
				cur += dpv;
			}
			if(c != m){
				cur += (dp[j][m] * (c - m - 1) % mod) * cnt_diff[dep[j] - dep[x] - 1] % mod;
				cur += dp[j][m] * cnt_same[dep[j] - dep[x] - 1] % mod;
			}
			cur %= mod;
			dp[x][m] *= cur;
			dp[x][m] %= mod;
		}
	}
	for(auto &j : cgph[x]){
		if(dep[j] < dep[x]){
			dp[x][col[j]] = 0;
		}
	}
	if(~torun[x]){
		for(int j=0; j<=m; j++){
			if(j != col[x]) dp[x][j] = 0;
		}
	}
}

lint bktk(int x, int mx){
	if(c < mx) return 0;
	if(x == v.size()){
		dfs2(root, mx);
		lint ret = 0;
		for(int j=0; j<=mx; j++){
			ret += dp[root][j] * (j == mx ? (c - mx) : 1);
		}
		ret %= mod;
		for(int j=0; j<mx; j++){
			ret *= c - j;
			ret %= mod;
		}
		return ret;
	}
	lint ret = 0;
	int ban[10] = {};
	for(int j=0; j<x; j++){
		if(adj[j][x]){
			ban[col[v[j]]] = 1;
		}
	}
	for(int j=0; j<=mx; j++){
		if(ban[j]) continue;
		col[v[x]] = j;
		ret += bktk(x+1, max(j+1, mx));
		ret %= mod;
	}
	return ret;
}

int par[17][100005], dfn[100005], sz[100005], piv;

bool in_sub(int x, int y){
	return dfn[x] <= dfn[y] && dfn[y] + sz[y] <= dfn[x] + sz[x];
}

void dfs(int x, int p){
	vis[x] = 1;
	dfn[x] = ++piv;
	sz[x] = 1;
	for(auto &i : gph[x]){
		if(i == p) continue;
		if(!vis[i]){
			par[0][i] = x;
			dep[i] = dep[x] + 1;
			dfs(i, x);
			sz[x] += sz[i];
		}
		else if(dep[i] < dep[x]){
			if(torun[i] == -1){
				torun[i] = cnt1++;
				v.push_back(i);
			}
		}
	}
}

void gph_compress(){
	for(int i=1; i<=16; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	auto lca = [&](int a, int b){
		if(dep[a] < dep[b]) swap(a, b);
		int dx = dep[a] - dep[b];
		for(int i=0; i<17; i++){
			if((dx >> i) & 1) a = par[i][a];
		}
		for(int i=16; i>=0; i--){
			if(par[i][a] != par[i][b]){
				a = par[i][a];
				b = par[i][b];
			}
		}
		if(a != b) a = par[0][a];
		return a;
	};
	vector<int> v;
	set<int> s;
	for(int i=1; i<=n; i++){
		for(auto &j : gph[i]){
			if(dep[i] > dep[j] && par[0][i] != j){
				v.push_back(i);
				v.push_back(j);
				s.insert(i);
				s.insert(j);
				cgph[i].push_back(j);
			}
		}
	}
	sort(v.begin(), v.end(), [&](const int &a, const int &b){
		return dfn[a] < dfn[b];
	});
	for(int i=0; i<v.size()-1; i++){
		s.insert(lca(v[i], v[i+1]));
	}
	s.insert(root);
	v.clear();
	for(auto &i : s) v.push_back(i);
	sort(v.begin(), v.end(), [&](const int &a, const int &b){
		return dfn[a] < dfn[b];
	});
	stack<int> stk;
	for(auto &i : v){
		while(!stk.empty() && !in_sub(stk.top(), i)){
			stk.pop();
		}
		if(!stk.empty()){
			cgph[stk.top()].push_back(i);
		}
		stk.push(i);
	}
}

int main(){
	set<pi> edg;
	cin >> n >> m >> c;
	int cnt = 0;
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		if(s == e){
			cout << 0;
			return 0;
		}
		if(s > e) swap(s, e);
		if(edg.find(pi(s, e)) != edg.end()) continue;
		edg.insert(pi(s, e));
		gph[s].push_back(e);
		gph[e].push_back(s);
		deg[s]++;
		deg[e]++;
		cnt++;
	}
	if(cnt == n-1){
		cout << c * ipow(c-1, n-1) % mod;
		return 0;
	}
	for(int i=0; i<=n; i++){
		cnt_same[i] = (ipow(c-1, i+1) + ipow(mod-1, i+1) * (c-1) % mod) * ipow(c, mod-2) % mod;
		cnt_diff[i] = (ipow(c-1, i) - cnt_same[i] * ipow(c-1, mod-2) % mod + mod) % mod;
	}
	queue<int> que;
	cnt = 0;
	for(int i=1; i<=n; i++){
		if(deg[i] == 1){
			que.push(i);
		}
	}
	while(!que.empty()){
		int x = que.front();
		que.pop();
		deg[x]--;
		for(auto &i : gph[x]){
			if(deg[i] > 0){
				deg[i]--;
				if(deg[i] == 1){
					que.push(i);
				}
			}
		}
		cnt++;
	}
	for(int i=1; i<=n; i++){
		if(!deg[i]) gph[i].clear();
		else{
			root = i;
			vector<int> w = gph[i];
			gph[i].clear();
			for(auto &j : w){
				if(deg[j]) gph[i].push_back(j);
			}
		}
	}
	memset(torun, -1, sizeof(torun));
	dfs(root, 0);
	gph_compress();
	for(auto &i : edg){
		if(~torun[i.first] && ~torun[i.second]){
			adj[torun[i.first]][torun[i.second]] = 1;
			adj[torun[i.second]][torun[i.first]] = 1;
		}
	}
	cout << bktk(0, 0) * ipow(c-1, cnt) % mod;
}
