#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
using real_t = long double;
using pi = pair<int, int>;
const int MAXN = 105;

struct scc{
	vector<int> gph[MAXN];
	vector<int> rev[MAXN];
	vector<int> dfn;
	int vis[MAXN], comp[MAXN], piv;
	void add_edge(int l, int r){
		gph[l].push_back(r);
		rev[r].push_back(l);
	}
	void clear(){
		memset(vis, 0, sizeof(vis));
		memset(comp, 0, sizeof(comp));
		piv = 0;
		for(int i=0; i<MAXN; i++) gph[i].clear(), rev[i].clear();
		dfn.clear();
	}
	void dfs(int x){
		if(vis[x]) return;
		vis[x] = 1;
		for(auto &i : gph[x]) dfs(i);
		dfn.push_back(x);
	}
	void rdfs(int x, int p){
		if(comp[x]) return;
		comp[x] = p;
		for(auto &i : rev[x]) rdfs(i, p);
	}
	void get_scc(int n){
		for(int i=1; i<=n; i++){
			if(!vis[i]) dfs(i);
		}
		reverse(dfn.begin(), dfn.end());
		for(auto &i : dfn){
			if(!comp[i]) rdfs(i, ++piv);
		}
	}
}scc;

int dp[MAXN][10005];
int sex[MAXN];
vector<int> v[MAXN];
vector<int> gph[MAXN];
int n, m, T, p[MAXN], t[MAXN], k[MAXN];
pi a[1005];

int main(){
	while(true){
		scanf("%d %d %d",&n,&m,&T);
		if(n + m + T == 0) break;
		for(int i=1; i<=n; i++) scanf("%d %d %d",&p[i],&t[i],&k[i]);
		for(int i=0; i<m; i++){
			scanf("%d %d",&a[i].first,&a[i].second);
			scc.add_edge(a[i].first,a[i].second);
		}
		scc.get_scc(n);
		for(int i=1; i<=n; i++){
			v[scc.comp[i]].push_back(i);
		}
		for(int i=0; i<m; i++){
			int l = scc.comp[a[i].first];
			int r = scc.comp[a[i].second];
			if(a[i].first == a[i].second){
				sex[l] = 1;
			}
			assert(l <= r);
			if(l < r) gph[l].push_back(r);
		}
		memset(dp, 0, sizeof(dp));
		int ret = 0;
		for(int i=scc.piv; i; i--){
			for(auto &j : gph[i]){
				for(int k=0; k<=T; k++) dp[i][k] = max(dp[i][k], dp[j][k]);
			}
			if(v[i].size() == 1 && !sex[i]){
				k[v[i][0]] = 1;
			}
			vector<pi> item;
			for(auto &j : v[i]){
				int pw = 1;
				while(pw < k[j]){
					k[j] -= pw;
					item.emplace_back(p[j] * pw, t[j] * pw);
					pw *= 2;
				}
				pw = k[j];
				item.emplace_back(p[j] * pw, t[j] * pw);
			}
			for(auto &j : item){
				for(int k=T; k>=j.second; k--) dp[i][k] = max(dp[i][k], dp[i][k-j.second] + j.first);
			}
			ret = max(ret, dp[i][T]);
		}
		for(int i=1; i<=n; i++) {
			sex[i] = 0;
			v[i].clear();
			gph[i].clear();
		}
		scc.clear();
		cout << ret << endl;
	}
}
