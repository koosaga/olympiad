#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 1000005;

int n, a[MAXN], deg[MAXN];
vector<int> gph[MAXN];
int lo, hi;
int cntv, cntl;

bool vis[MAXN];
void dfs(int x){
	if(vis[x]) return;
	vis[x] = 1;
	cntv++;
	if(gph[x].size() == 0) cntl++;
	for(auto &i : gph[x]) dfs(i);
}

int par[MAXN];
long long int dp[MAXN][2];

void ffffffff(int x){
	queue<int> que;
	vector<int> ord;
	que.push(x);
	while(!que.empty()){
		int x = que.front();
		ord.push_back(x);
		que.pop();
		for(auto &i : gph[x]){
			if(!vis[i]){
				que.push(i);
				vis[i] = 1;
				par[i] = x;
			}
		}
	}
	reverse(ord.begin(), ord.end());
	for(auto &x : ord){
		if(gph[x].size() == 0){
			dp[x][0] = -1e7;
			dp[x][1] = 1;
		}
		dp[x][1] = 1;
		for(auto &i : gph[x]){
			if(deg[i]) continue;
			dp[x][0] += max(dp[i][0], dp[i][1]);
			dp[x][1] += dp[i][0];
		}
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		gph[a[i]].push_back(i);
		deg[a[i]]++;
	}
	queue<int> que;
	for(int i=1; i<=n; i++){
		if(!deg[i]){
			que.push(i);
		}
	}
	while(!que.empty()){
		int x = que.front();
		que.pop();
		deg[a[x]]--;
		if(deg[a[x]] == 0) que.push(a[x]);
	}
	for(int i=1; i<=n; i++){
		if(deg[i] && !vis[i]){
			cntv = cntl = 0;
			dfs(i);
			if(cntl == 0){
				if(cntv == 1) hi += 1;
				else hi += cntv - 1;
			}
			else hi += cntv - cntl;
		}
	}
	memset(vis, 0, sizeof(vis));
	lo = n;
	for(int i=1; i<=n; i++){
		if(deg[i] && !vis[i]){
			vector<int> v;
			for(int j=i; !vis[j]; j=a[j]) v.push_back(j), vis[j] = 1;
			bool isCycle = 1;
			for(auto &j : v){
				for(auto &k : gph[j]){
					if(deg[k] == 0) isCycle = 0;
				}
				ffffffff(j);
			}
			if(isCycle){
				lo -= v.size() / 2;
				continue;
			}
			if(v.size() == 1){
				lo -= dp[i][0];
			}
			else{
				long long int cur[2] = {}, nxt[2] = {};
				for(auto &j : v){
					nxt[0] = max(cur[0], cur[1]) + dp[j][0];
					nxt[1] = cur[0] + dp[j][1];
					cur[0] = nxt[0];
					cur[1] = nxt[1];
				}
				long long int ret = cur[0];
				reverse(v.begin(), v.end());
				cur[0] = cur[1] = 0;
				for(auto &j : v){
					nxt[0] = max(cur[0], cur[1]) + dp[j][0];
					nxt[1] = cur[0] + dp[j][1];
					cur[0] = nxt[0];
					cur[1] = nxt[1];
				}
				ret = max(ret, cur[0]);
				lo -= ret;
			}
		}
	}
	printf("%d %d\n", lo, hi);
}
