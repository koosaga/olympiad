#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
using ll = long long;
const int MAXN = 50005;
const int B = 800;

struct qry{
	int x, y, k, l, idx;
	bool operator<(const qry &q)const{
		return k < q.k;
	}
};

int n;

vector<int> gph[MAXN];
vector<int> ord;
int cpar[MAXN];
int par[16][MAXN], dep[MAXN], A[MAXN];
int ret[MAXN];

int up(int x, int v){
	if(v >= n) return 0;
	for(int i=0; v; i++){
		if(v & 1) x = par[i][x];
		v >>= 1;
	}
	return x;
}

void dfs(int x, int p){
	ord.push_back(x);
	for(auto &i : gph[x]){
		if(i != p){
			par[0][i] = x;
			dep[i] = dep[x] + 1;
			dfs(i, x);
		}
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&A[i]);
	for(int i=1; i<n; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	vector<int> a(n), b(n - 1);
	for(auto &i : a) scanf("%d",&i);
	for(auto &i : b) scanf("%d",&i);
	dfs(1, 0);
	for(int i=1; i<16; i++){
		for(int j=1; j<=n; j++) par[i][j] = par[i-1][par[i-1][j]];
	}
	auto lca = [&](int x, int y){
		if(dep[x] > dep[y]) swap(x, y);
		y = up(y, dep[y] - dep[x]);
		for(int i=15; i>=0; i--){
			if(par[i][x] != par[i][y]){
				x = par[i][x];
				y = par[i][y];
			}
		}
		if(x != y) return par[0][x];
		return x;
	};
	vector<qry> v;
	for(int i=1; i<n; i++){
		int l = a[i-1], r = a[i];
		int m = b[i-1];
		v.push_back({l, r, m, lca(l, r), i});
	}
	sort(all(v));
	vector<int> cpar(n + 1);
	vector<int> dp(n + 1);
	iota(all(cpar), 0);
	int ptr = 0;
	dep[0] = -1;
	auto get_path = [&](int x, int l, int k, int flag){
		if(!flag){
			int up_dist = (dep[x] - dep[l]) / k + 1;
			return dp[x] - dp[up(x, up_dist * k)];
		}
		int ret = 0;
		while(dep[x] >= dep[l]){
			ret += A[x];
			x = up(x, k);
		}
		return ret;
	};
	for(int i=1; i<=n; i++){
		if(i <= B){
			for(int j=1; j<=n; j++){
				cpar[j] = par[0][cpar[j]];
			}
			for(auto &i : ord){
				dp[i] = dp[cpar[i]] + A[i];
			}
		}
		while(ptr < sz(v) && v[ptr].k == i){
			ret[v[ptr].idx] 
			+= get_path(v[ptr].x, v[ptr].l, v[ptr].k, i > B)
			 + get_path(v[ptr].y, v[ptr].l, v[ptr].k, i > B)
			 - (dep[v[ptr].x] % i == dep[v[ptr].l] % i ? A[v[ptr].l] : 0);
			ptr++;
		}
	}
	for(int i=1; i<n; i++) printf("%d\n", ret[i]);
}
