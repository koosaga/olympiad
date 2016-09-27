#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, x, a[2005];
vector<int> gph[2005];

int dp[2005][2005];
int aux[2005], sz[2005];
int tra[2005][2005], cuz[2005][2005];

void dfs(int x, int p){
	dp[x][0] = 0;
	for(auto &i : gph[x]){
		if(i == p) continue;
		dfs(i, x);
		memset(aux, 0x3f, sizeof(aux));
		for(int j=0; j<=sz[x]; j++){
			for(int k=0; k<=sz[i]; k++){
				if(aux[j+k] > dp[x][j] + dp[i][k]){
					aux[j+k] = dp[x][j] + dp[i][k];
					tra[i][j+k] = k;
				}
			}
		}
		sz[x] += sz[i];
		for(int j=0; j<=sz[x]; j++){
			dp[x][j] = aux[j];
		}
	}
	for(int j=0; j<=sz[x]; j++){
		dp[x][j] += a[x];
	}
	sz[x]++;
	if(p != -1){
		for(int j=sz[x]; j; j--){
			if(dp[x][j-1] <= 0 && dp[x][j] > 0){
				dp[x][j] = 0;
				cuz[x][j] = 1;
			}
		}
	}
}

vector<pi> later;
void trace(int x, int v, int p){
	if(cuz[x][v]){
		later.push_back(pi(x, p));
		v--;
	}
	for(auto &i : gph[x]){
		if(i == p) continue;
		int ct = tra[i][v];
		trace(i, ct, x);
		v -= ct;
	}
}

int sum[2005], vis[2005], indeg[2005];
vector<int> dirg[2005], dfn;

void dfs2(int x, int p){
	vis[x] = 1;
	sum[x] = a[x];
	dfn.push_back(x);
	for(auto &i : gph[x]){
		if(i == p) continue;
		dfs2(i, x);
		if(sum[i] <= 0){
			dirg[x].push_back(i);
			indeg[i]++;
		}
		else{
			dirg[i].push_back(x);
			indeg[x]++;
		}
		sum[x] += sum[i];
	}
}

int dfs3(int x, int p){
	int ret = a[x];
	for(auto &i : gph[x]){
		if(i == p) continue;
		ret += dfs3(i, x);
	}
	return ret;
}

struct edg{int first, second, x;};

void solve(){
	vector<edg> v;
	for(int i=1; i<=n; i++){
		if(vis[i]) continue;
		dfn.clear();
		dfs2(i, -1);
		queue<int> que;
		for(auto &i : dfn){
			if(indeg[i] == 0) que.push(i);
		}
		while(!que.empty()){
			auto x = que.front();
			que.pop();
			for(auto &j : dirg[x]){
				v.push_back({x, j, 0});
				indeg[j]--;
				if(indeg[j] == 0) que.push(j);
			}
		}
	}
	for(auto &i : v){
		gph[i.first].erase(find(gph[i.first].begin(), gph[i.first].end(), i.second));
		gph[i.second].erase(find(gph[i.second].begin(), gph[i.second].end(), i.first));
		int mod = min(-dfs3(i.second, i.first), a[i.first]);
		a[i.first] -= mod;
		a[i.second] += mod;
		i.x = mod;
	}
	reverse(v.begin(), v.end());
	for(auto &i : v){
		printf("%d %d %d\n", i.second, i.first, i.x);
	}
}

int main(){
	cin >> n >> x;
	for(int i=1; i<=n; i++){
		cin >> a[i];
		a[i] -= x;
	}
	for(int i=0; i<n-1; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	memset(dp, 0x3f, sizeof(dp));
	dfs(1, -1);
	for(int i=n-1; i>=0; i--){
		if(dp[1][i] <= 0){
			printf("%d\n", n-1-i);
			for(int j=1; j<=n; j++){
				reverse(gph[j].begin(), gph[j].end());
			}
			trace(1, i, -1);
			for(auto &i : later){
				gph[i.first].erase(find(gph[i.first].begin(), gph[i.first].end(), i.second));
				gph[i.second].erase(find(gph[i.second].begin(), gph[i.second].end(), i.first));
			}
			solve();
			return 0;
		}
	}
}
