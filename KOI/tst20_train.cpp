#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 250005;

vector<int> gph[MAXN];
int par[18][MAXN], dep[MAXN];
vector<pi> fars[MAXN];
int far[MAXN], pfar[MAXN];

void dfs(int x, int p){
	for(auto &y : gph[x]){
		if(y != p){
			par[0][y] = x;
			dep[y] = dep[x] + 1;
			dfs(y, x);
			far[x] = max(far[x], far[y] + 1);
		}
	}
}

void spread(int x, int p){
	fars[x].emplace_back(0, x);
	for(auto &y : gph[x]){
		if(y != p){
			fars[x].emplace_back(far[y] + 1, y);
		}
	}
	if(x > 1) fars[x].emplace_back(pfar[x], p);
	sort(all(fars[x]));
	reverse(all(fars[x]));
	for(auto &y : gph[x]){
		if(y != p){
			for(int j = 0; j < sz(fars[x]); j++){
				if(fars[x][j].second != y){
					pfar[y] = fars[x][j].first + 1;
					break;
				}
			}
			spread(y, x);
		}
	}
}

void init(int N, std::vector<int> X, std::vector<int> Y) {
	for(int i = 0; i < N - 1; i++){
		gph[X[i]].push_back(Y[i]);
		gph[Y[i]].push_back(X[i]);
	}
	dfs(1, 0);
	spread(1, 0);
	for(int i = 1; i < 18; i++){
		for(int j = 1; j <= N; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
}

int lca(int x, int y){
	if(dep[x] > dep[y]) swap(x, y);
	int dx = dep[y] - dep[x];
	for(int i = 0; dx; i++){
		if(dx & 1) y = par[i][y];
		dx >>= 1;
	}
	if(x == y) return x;
	for(int i = 17; i >= 0; i--){
		if(par[i][x] != par[i][y]){
			x = par[i][x];
			y = par[i][y];
		}
	}
	return par[0][x];
}

int dist(int x, int y){
	return dep[x] + dep[y] - 2 * dep[lca(x, y)];
}

int cent(int x, int y, int z){
	int p = lca(x, y);
	int q = lca(y, z);
	int r = lca(z, x);
	if(dep[p] < dep[q]) p = q;
	if(dep[p] < dep[r]) p = r;
	return p;
}

vector<int> getPath(int x, int y){
	int l = lca(x, y);
	vector<int> lp, rp;
	for(int i = x; i != l; i = par[0][i]) lp.push_back(i);
	for(int i = y; i != l; i = par[0][i]) rp.push_back(i);
	lp.push_back(l);
	reverse(all(rp));
	for(auto &x : rp) lp.push_back(x);
	return lp;
}

int get_far(int x, int p){
	for(auto &[l, v] : fars[x]){
		if(v == p) continue;
		return l;
	}
	return 0;
}

int goomtle(int r, int x, int y){
	if(r == x || r == y) return 0;
	auto v = getPath(x, y);
	int pos = -1;
	for(int i = 0; i < sz(v); i++){
		if(v[i] == r) pos = i;
	}
	if(pos == -1) return min(dist(r, x), dist(r, y));
	vector<int> far(sz(v)), dp(sz(v));
	for(int i = 0; i < sz(v); i++){
		if(i < pos) far[i] = get_far(v[i], v[i + 1]);
		else if(i > pos) far[i] = get_far(v[i], v[i - 1]);
	}
	int L = sz(v) - 1;
	int j = sz(v);
	vector<int> minReach(sz(v), 1e9);
	for(int i = 0; i < sz(v); i++){
		int w = i - far[i] + L;
		while(j > 0 && j > w){
			j--;
			minReach[j] = i;
		}
	}
	priority_queue<pi, vector<pi>, greater<pi> > pque;
	for(int i = pos + 1; i < sz(v); i++){
		pque.emplace(dp[i - 1] + 2 * minReach[i - 1] - (i - 1), minReach[i - 1]);
		while(sz(pque) && pque.top().second > i + far[i] - L) pque.pop();
		dp[i] = 1e9;
		if(pos + L - i <= far[i]){
			dp[i] = min(dp[i], pos + L - i);
		}
		if(sz(pque)){
			dp[i] = min(dp[i], pque.top().first + 2 * (L - i) + i);
		}
	}
	return dp.back();
}


long long train(std::vector<int> Z) {
	int v1 = cent(Z[0], Z[1], Z[2]);
	int v2 = cent(Z[2], Z[3], Z[0]);
//	cout << v1 << " " << v2 << endl;
	int ans = goomtle(v1, Z[0], Z[1]) + goomtle(v2, Z[2], Z[3]) + dist(v1, v2) + dist(Z[0], Z[1]);
	if(ans > 1e8) ans = -1;
	return ans;
}
