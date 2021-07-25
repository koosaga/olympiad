#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 100005;

vector<int> gph[MAXN];

namespace CD {
	int siz[MAXN], msz[MAXN], vis[MAXN];
	vector<int> dfn;
	void dfsc(int x, int p) {
		dfn.push_back(x);
		siz[x] = 1;
		msz[x] = 0;
		for (auto &i : gph[x]) {
			if (i != p && !vis[i]) {
				dfsc(i, x);
				siz[x] += siz[i];
				msz[x] = max(msz[x], siz[i]);
			}
		}
	}
	int get_center(int x) {
		dfsc(x, -1);
		pi ret(1e9, 1e9);
		for (auto &i : dfn) {
			int val = max(msz[i], sz(dfn) - siz[i]);
			ret = min(ret, pi(val, i));
		}
		dfn.clear();
		return ret.second;
	}
	int dep[MAXN], par[MAXN], pae[MAXN];
	int dist[17][MAXN];
	vector<lint> dsum[MAXN];
	vector<lint> sub_dsum[MAXN];
	int dfs1(int x, int p, int d, int idx, int *arr) {
		int ret = d;
		arr[x] = d;
		for (auto &i : gph[x]) {
			if (!vis[i] && i != p) {
				ret = max(ret, dfs1(i, x, d + 1, idx, arr));
			}
		}
		return ret;
	}
	void dfs(int x, int pa, int pe) {
		static int piv = 0;
		x = get_center(x);
		par[x] = pa;
		pae[x] = pe;
		vis[x] = 1;
		if (par[x]) {
			dep[x] = dep[par[x]] + 1;
		}
		vector<pi> to_rec;
		int mySz = 1;
		for (auto &i : gph[x]) {
			if (!vis[i]) {
				to_rec.emplace_back(i, piv);
				int Sz = dfs1(i, x, 1, piv, dist[dep[x]]);
				sub_dsum[piv].resize(Sz + 1);
				mySz = max(mySz, Sz + 1);
				piv++;
			}
		}
		dsum[x].resize(mySz);
		for (auto &i : to_rec) {
			dfs(i.first, x, i.second);
		}
	}
	void init() {
		dfs(1, 0, -1);
	}
	void add(int x, lint v){
		int par_edge = -1;
		for(int j = x; j; j = par[j]){
			int distv = dist[dep[j]][x];
			if(sz(dsum[j]) > distv) dsum[j][distv] += v;
			if(par_edge != -1 && sz(sub_dsum[par_edge]) > distv){
				sub_dsum[par_edge][distv] += v;
			}
			par_edge = pae[j];
		}
	}
	lint get_val(vector<lint> &v, int w) {
		if (w >= sz(v)) return 0;
		if (w < 0) return 0;
		return v[w];
	}

	lint query(int x, int d) {
		int par_edge = -1;
		lint ret = 0;
		for (int j = x; j; j = par[j]) {
			int dist_btw = d - dist[dep[j]][x];
			ret += get_val(dsum[j], dist_btw);
			if (par_edge != -1) {
				ret -= get_val(sub_dsum[par_edge], dist_btw);
			}
			par_edge = pae[j];
		}
		return ret;
	}
}

struct balls{
	int v, d, c;
};

vector<int> dfn;
vector<balls> ball[MAXN];
int par[17][MAXN], dep[MAXN];
lint dp[MAXN];

void dfs(int x, int p){
	dfn.push_back(x);
	for(auto &y : gph[x]){
		if(y != p){
			par[0][y] = x;
			dep[y] = dep[x] + 1;
			dfs(y, x);
		}
	}
}

int anc(int x, int d){
	for(int i = 0; d; i++){
		if(d & 1) x = par[i][x];
		d >>= 1;
	}
	return x;
}

int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	for(int i = 1; i < n; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, -1);
	for(int i = 1; i < 17; i++){
		for(int j = 1; j <= n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	CD::init();
	for(int i = 0; i < m; i++){
		int v, d, c;
		scanf("%d %d %d",&v,&d,&c);
		int putV = anc(v, min(dep[v], d));
		ball[putV].push_back({v, d, c});
	}
	reverse(all(dfn));
	for(auto &i : dfn){
		for(auto &j : gph[i]){
			if(j != par[0][i]) dp[i] += dp[j];
		}
		for(auto &b : ball[i]){
			dp[i] = max(dp[i], b.c + CD::query(b.v, b.d+1));
		}
		CD::add(i, dp[i]);
	}
	cout << dp[1] << endl;
}
