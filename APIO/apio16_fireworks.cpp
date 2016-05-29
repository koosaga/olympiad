#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const lint inf = 1e16;

int n, m, sz[250005];
lint dep[250005], c[250005];

vector<int> gph[250005];

struct func{
	priority_queue<lint> pq;
	lint cost;
	int slope;
	void init(){
		cost = 0;
		slope = -1;
		pq.push(0);
		pq.push(0);
	}
	void upperize(int x){
		cost += c[x];
		while(slope + (int)pq.size() > 1){
			pq.pop();
		}
		vector<lint> v;
		while(!pq.empty() && slope + (int)pq.size() >= 0){
			v.push_back(pq.top());
			pq.pop();
		}
		while(!v.empty()){
			pq.push(v.back() + c[x]);
			v.pop_back();
		}
	}
}dp[250005];

bool cmp(int a, int b){
	return sz[a] > sz[b];
}

void dfs(int x){
	if(x > n){
		sz[x] = 1;
		return;
	}
	for(int i=0; i<gph[x].size(); i++){
		dep[gph[x][i]] = dep[x] + c[gph[x][i]];
		dfs(gph[x][i]);
		sz[x] += sz[gph[x][i]];
	}
	sort(gph[x].begin(), gph[x].end(), cmp);
}

int solve(int x){
	if(x > n){
		dp[x].init();
		return x;
	}
	int ret = solve(gph[x][0]);
	dp[ret].upperize(gph[x][0]);
	for(int i=1; i<gph[x].size(); i++){
		int t = solve(gph[x][i]);
		dp[t].upperize(gph[x][i]);
		dp[ret].cost += dp[t].cost;
		dp[ret].slope += dp[t].slope;
		while(!dp[t].pq.empty()){
			dp[ret].pq.push(dp[t].pq.top());
			dp[t].pq.pop();
		}
	}
	return ret;
}

int main(){
	cin >> n >> m;
	for(int i=2; i<=n+m; i++){
		int p;
		scanf("%d %lld",&p,&c[i]);
		gph[p].push_back(i);
	}
	dfs(1);
	func ret = dp[solve(1)];
	ret.upperize(0);
	lint ansp = ret.pq.top();
	lint ans = ret.cost + ansp * ret.slope;
	while(!ret.pq.empty()){
		ans += ansp - ret.pq.top();
		ret.pq.pop();
	}
	printf("%lld",ans);
}