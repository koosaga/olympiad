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

vector<pi> gph[10005];

int col[10005];
int bad, cnt;

void dfs(int x, int c){
	if(col[x]){
		if(col[x] != c){
			bad = 1;
		}
		return;
	}
	col[x] = c;
	if(c == 1) cnt++;
	else cnt--;
	for(int ii=0; ii<gph[x].size(); ii++){ pi i = gph[x][ii];
		if(i.second == 1) dfs(i.first, 3-c);
		else dfs(i.first, c);
	}
}

int dp[20005];
int n, m;

void solve(){
	cin >> n >> m;
	for(int i=0; i<m; i++){
		int x, y, z;
		scanf("%d %d %d",&x,&y,&z);
		x = (1-x)/2;
		gph[y].emplace_back(z, x);
		gph[z].emplace_back(y, x);
	}
	vector<int> v;
	for(int i=1; i<=n; i++){
		if(col[i]) continue;
		cnt = 0;	
		dfs(i, 1);
		if(bad){
			puts("-1");
			return;
		}
		cnt = abs(cnt);
		v.push_back(cnt);
	}
	dp[10000] = 1;
	for(int i=0; i<v.size(); i++){
		int dp2[20005] = {};
		for(int j=0; j<=20000; j++){
			if(j + v[i] <= 20000) dp2[j] |= dp[j + v[i]];
			if(j >= v[i]) dp2[j] |= dp[j - v[i]];
		}
		for(int j=0; j<=20000; j++){
			dp[j] = dp2[j];
		}
	}
	for(int i=10000; ; i++){
		if(dp[i]){
			printf("%d\n",i - 10000);
			return;
		}
	}
}

int main(){
	for(int i=0; i<5; i++){
		solve();
		for(int i=0; i<=n; i++) gph[i].clear();
		bad = cnt = 0;
		memset(col, 0, sizeof(col));
		memset(dp, 0, sizeof(dp));
	}
}