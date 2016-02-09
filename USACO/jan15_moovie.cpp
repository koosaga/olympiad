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
 
int n, wsum;
int dp[1<<20], sum[1<<20], w[20];
vector<int> v[20];
 
int main(){
	cin >> n >> wsum;
	for(int i=0; i<n; i++){
		int t;
		cin >> w[i] >> t;
		while(t--){
			int u;
			cin >> u;
			v[i].push_back(u);
		}
		v[i].push_back(1e9);
	}
	// d[i] -> max time that you can reach with such bs.
	for(int i=1; i<(1<<n); i++){
		dp[i] = -1e9;
		for(int j=0; j<n; j++){
			if((i >> j) & 1){
				int p = i ^ (1<<j);
				auto it = upper_bound(v[j].begin(), v[j].end(), dp[p]);
				if(it == v[j].begin()) continue;
				dp[i] = max(dp[i], *--it + w[j]);
			}
		}
	}
	int ret = 1e9;
	for(int i=1; i<(1<<n); i++){
		if(dp[i] >= wsum){
			int tmp = 0;
			for(int j=0; j<n; j++){
				if((i >> j) & 1) tmp++;
			}
			ret = min(ret, tmp);
		}
	}
	if(ret > 1e8) puts("-1");
	else printf("%d",ret);
}