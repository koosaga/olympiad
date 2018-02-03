#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct disj{
	int pa[2005], sz[2005];
	void init(int n){
		for(int i=1; i<=n; i++){
			pa[i] = i;
			sz[i] = 1;
		}
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p;
		sz[p] += sz[q];
		return 1;
	}
}disj;

int n, m, d, sz[2005];
lint* dp[2005][2];
lint cst[2005];
vector<pi> gph[2005];

void pre(int x, int p){
	sz[x] = 1;
	for(auto &i : gph[x]){
		if(i.second == p) continue;
		pre(i.second, x);
		sz[x] += sz[i.second];
	}
	dp[x][0] = new lint[sz[x] + 1];
	dp[x][1] = new lint[sz[x] + 1];
	for(int i=0; i<=sz[x]; i++){
		dp[x][0][i] = dp[x][1][i] = 1e18;
	}
}


lint nxt0[2005], nxt1[2005];

void dfs(int x, int p){
	dp[x][0][0] = 0;
	int cur = 0;
	for(auto &i : gph[x]){
		if(i.second == p) continue;
		dfs(i.second, x);
		for(int j=0; j<=sz[i.second]; j++){
			dp[i.second][0][j] = min(dp[i.second][0][j], 
					dp[i.second][1][j] - i.first);
		}
		memset(nxt0, 0x3f, sizeof(nxt0));
		memset(nxt1, 0x3f, sizeof(nxt1));
		for(int j=0; j<=cur; j++){
			for(int k=0; k<=sz[i.second]; k++){
				nxt0[j+k] = min(nxt0[j+k], dp[x][0][j] + dp[i.second][0][k]);
				nxt1[j+k] = min(nxt1[j+k], dp[x][1][j] + dp[i.second][0][k]);
				nxt1[j+k] = min(nxt1[j+k], dp[x][0][j] + dp[i.second][1][k]);
			}
		}
		cur += sz[i.second];
		for(int j=0; j<=cur; j++){
			dp[x][0][j] = nxt0[j];
			dp[x][1][j] = nxt1[j];
		}
	}
	for(int j=1; j<=cur+1; j++){
		dp[x][1][j] = min(dp[x][1][j], dp[x][0][j-1] + cst[x]);
	}
}

struct edg{int s, e, x;};
vector<edg> v;

int main(){
	freopen("highway.in", "r", stdin);
	scanf("%d %d %d",&n,&m,&d);
	memset(cst, 0x3f, sizeof(cst));
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		if(s > e) swap(s, e);
		if(s == 1) cst[e] = min(cst[e], 1ll * x);
		else v.push_back({s, e, x});
	}
	sort(v.begin(), v.end(), [&](const edg &a, const edg &b){
		return a.x < b.x;
	});
	disj.init(n);
	lint mst = 0;
	for(auto &i : v){
		if(disj.uni(i.s, i.e)){
			gph[i.s].push_back(pi(i.x, i.e));
			gph[i.e].push_back(pi(i.x, i.s));
			mst += i.x;
		}
	}
	lint ans[2005];
	memset(ans, 0x3f, sizeof(ans));
	ans[0] = 0;
	int cur = 0;
	for(int i=2; i<=n; i++){
		if(!sz[i]){
			pre(i, 1);
			dfs(i, 1);
			lint nxt[2005] = {};
			memset(nxt, 0x3f, sizeof(nxt));
			for(int j=1; j<=sz[i]; j++){
				for(int k=0; k<=cur; k++){
					nxt[j+k] = min(nxt[j+k], dp[i][1][j] + ans[k]);
				}
			}
			memcpy(ans, nxt, sizeof(ans));
			cur += sz[i];
		}
	}
	cout << *min_element(ans, ans + d + 1) + mst;
}
