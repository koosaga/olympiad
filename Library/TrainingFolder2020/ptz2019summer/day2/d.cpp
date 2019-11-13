#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 25005;
const int MAXK = 30;
const int mod = 998244353;
 
lint ipow(lint x, lint p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}
 
namespace GE{
	int n, inv;
	vector<int> basis[MAXK];
	lint gyesu = 1;
 
	bool insert(vector<int> v){
		for(int i=0; i<n; i++){
			if(basis[i].size()) inv ^= 1; // inversion num increases
			if(v[i] && basis[i].empty()){
				basis[i] = v;
				return 0;
			}
			if(v[i]){
				lint minv = ipow(basis[i][i], mod - 2) * v[i] % mod;
				for(auto &j : basis[i]) j = (j * minv) % mod;
				gyesu *= minv;
				gyesu %= mod;
				for(int j=0; j<basis[i].size(); j++){
					v[j] += mod - basis[i][j];
					while(v[j] >= mod) v[j] -= mod;
				}
			}
		}
		return 1;
	}
 
	lint det(vector<vector<int>> x){
		n = sz(x);
		inv = 0;
		gyesu = 1;
		for(int i=0; i<n; i++) basis[i].clear();
		for(int i=0; i<n; i++){
			if(i % 2 == 1) inv ^= 1;
			if(insert(x[i])) return 0;
		}
		if(inv) gyesu = mod - gyesu;
		gyesu = ipow(gyesu, mod - 2);
		for(int i=0; i<n; i++) gyesu = gyesu * basis[i][i] % mod;
		return gyesu % mod;
	}
}
 
int n, m;
vector<int> gph[MAXN];
vector<int> cmp[MAXN];
int dfn[MAXN], low[MAXN], piv;
int idx[MAXN], bcc[MAXN], c;
 
void dfs(int x, int p){
	dfn[x] = low[x] = ++piv;
	for(auto &i : gph[x]){
		if(i == p) continue;
		if(!dfn[i]){
			dfs(i, x);
			low[x] = min(low[x], low[i]);
		}
		else low[x] = min(low[x], dfn[i]);
	}
}
 
void color(int x, int p){
	bcc[x] = p;
	cmp[bcc[x]].push_back(x);
	for(auto &i : gph[x]){
		if(bcc[i]) continue;
		if(low[i] > dfn[x]){
			color(i, ++c);
		}
		else color(i, p);
	}
}
 
lint dp[MAXN][2];
lint adj[MAXK][MAXK];
 
lint det(int s, int e){
	vector<vector<int>> v;
	for(int i=s; i<=e; i++){
		vector<int> w;
		for(int j=s; j<=e; j++) w.push_back(adj[i][j]);
		v.push_back(w);
	}
	return GE::det(v);
}
 
int main(){
	scanf("%d %d %*d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, 0);
	color(1, ++c);
	for(int i=c; i; i--){
		memset(adj, 0, sizeof(adj));
		for(int j=0; j<cmp[i].size(); j++){
			idx[cmp[i][j]] = j + 1;
		}
		for(int j=0; j<cmp[i].size(); j++){
			int v = cmp[i][j];
			vector<pi> arg;
			for(auto &k : gph[v]){
				if(bcc[k] > bcc[v]){
					arg.emplace_back(dp[k][0], dp[k][1]);
				}
			}
			dp[v][0] = 1;
			for(auto &k : arg){
				dp[v][0] = dp[v][0] * k.second % mod;
			}
			vector<lint> pfx(sz(arg));
			vector<lint> sfx(sz(arg));
			for(int i=0; i<sz(arg); i++){
				pfx[i] = sfx[i] = arg[i].second;
			}
			for(int i=1; i<sz(arg); i++) pfx[i] = pfx[i-1] * pfx[i] % mod;
			for(int i=sz(arg)-2; i>=0; i--) sfx[i] = sfx[i+1] * sfx[i] % mod;
			for(int i=0; i<sz(arg); i++){
				lint tmp = arg[i].first;
				if(i > 0) tmp = tmp * pfx[i - 1] % mod;
				if(i + 1 < sz(arg)) tmp = tmp * sfx[i + 1] % mod;
				dp[v][1] += tmp;
				if(dp[v][1] >= mod) dp[v][1] -= mod;
			}
			dp[v][1] = (mod - dp[v][1]) % mod;
		}
		for(auto &j : cmp[i]){
			adj[idx[j]][idx[j]] = dp[j][1];
			for(auto &k : gph[j]){
				if(bcc[j] == bcc[k]){
					adj[idx[j]][idx[k]] = dp[j][0];
				}
			}
		}
		dp[cmp[i][0]][1] = det(1, sz(cmp[i]));
		for(int j=2; j<=sz(cmp[i]); j++) adj[1][j] = adj[j][1] = 0;
		adj[1][1] = dp[cmp[i][0]][0];
		dp[cmp[i][0]][0] = det(1, sz(cmp[i]));
	}
	cout << dp[1][1] << endl;
}
 
