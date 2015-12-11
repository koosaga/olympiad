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

int n, m, k;
vector<pi> graph[1005];
int dp[1005][105];

int main(){
	cin >> n >> m >> k;
	for(int i=0; i<m; i++){
		int s, e, x;
		cin >> s >> e >> x;
		graph[s].push_back(pi(x, e));
	}
	memset(dp,0x3f,sizeof(dp));
	dp[1][0] = 0;
	for(int i=2; i<=n; i++){
		vector<int> pt(graph[i].size(), 0);
		for(int j=0; j<k; j++){
			int minp = -1, minv = 1e9;
			for(int l=0; l<pt.size(); l++){
				if(minv > dp[graph[i][l].second][pt[l]] + graph[i][l].first){
					minv = dp[graph[i][l].second][pt[l]] + graph[i][l].first;
					minp = l;
				}
			}
			if(minp == -1) continue;
			dp[i][j] = minv;
			pt[minp]++;
		}
	}
	for(int i=0; i<k; i++){
		if(dp[n][i] >= 1e9) puts("-1");
		else printf("%d\n",dp[n][i]);
	}
}