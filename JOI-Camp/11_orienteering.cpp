#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
 
int n, m;
int topo[1005], rtopo[1005];
int btw[1005], tmp[1005];
int dp[1005][1005];
 
vector<pi> graph[1005];
 
int f(int x, int y){
	if(x > y) return f(y, x);
	if(~dp[x][y]) return dp[x][y];
	if(x == n && y == n) return 0;
	int ret = 1e9;
	for(auto &i : graph[rtopo[x]]){
		int psum = btw[topo[i.second] - 1] - btw[max(x,y)];
		if(psum > 0) continue;
		if(max(x, y) <= topo[i.second]){
			ret = min(ret, f(topo[i.second], y) + i.first);
		}
	}
	for(auto &i : graph[rtopo[y]]){
		int psum = btw[topo[i.second] - 1] - btw[max(x,y)];
		if(psum > 0) continue;
		if(max(x, y) <= topo[i.second]){
			ret = min(ret, f(topo[i.second], x) + i.first);
		}
	}
	return dp[x][y] = ret;
}
 
bool vis[1005];
vector<int> dfn;
 
void dfs(int x){
	if(vis[x]) return;
	vis[x] = 1;
	for(auto &i : graph[x]){
		dfs(i.second);
	}
	dfn.push_back(x);
}
 
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		scanf("%d",&tmp[i]);
	}
	for(int i=1; i<=m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		graph[s].push_back(pi(x, e));
	}
	for(int i=1; i<=n; i++){
		if(!vis[i]) dfs(i);
	}
	reverse(dfn.begin(), dfn.end());
	for(int i=1; i<=dfn.size(); i++){
		int pos = dfn[i-1];
		topo[pos] = i;
		rtopo[i] = pos;
	}
	for(int i=1; i<=n; i++){
		btw[topo[i]] = tmp[i];
	}
	for(int i=1; i<=n; i++){
		btw[i] += btw[i-1];
	}
	memset(dp,-1,sizeof(dp));
	printf("%d\n",f(1,1));
}