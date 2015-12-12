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

vector<pi> graph[100005];
int n, c[100005], pae[100005], par[100005], sc[100005];
lint dp[100005], pdp[100005];
vector<int> dfn;

void dfs(int x, int p){
	sc[x] = c[x];
	dfn.push_back(x);
	for(auto &i : graph[x]){
		if(i.second == p) continue;
		par[i.second] = x;
		pae[i.second] = i.first;
		dfs(i.second, x);
		sc[x] += sc[i.second];
		dp[x] += dp[i.second] + 1ll * sc[i.second] * i.first;
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&c[i]);
	}
	for(int i=0; i<n-1; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		graph[s].push_back(pi(x, e));
		graph[e].push_back(pi(x, s));
	}
	dfs(1, 0);
	lint ret = 1e18;
	for(auto &i : dfn){
		int p = par[i];
		if(p == 0) pdp[i] = 0;
		else{
			pdp[i] = pdp[p] + dp[p] - dp[i] - 1ll * sc[i] * pae[i] + 1ll * pae[i] * (sc[1] - sc[i]);
		}
		//printf("%d %lld\n",i, dp[i] + pdp[i]);
		ret = min(ret, dp[i] + pdp[i]);
		// pdp[i] = pdp[par] + pdp's subtrees without me
	}
	printf("%lld",ret);
}