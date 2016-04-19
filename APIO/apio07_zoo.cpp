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
const int oo = 1e9;

int n, c;
vector<pi> ppl[10005];
int dp[10005][32];

int solve(int b){
	for(int i=0; i<32; i++){
		if(i != b) dp[n+1][i] = -1e9;
		else dp[n+1][i] = 0;
	}
	for(int i=n; i; i--){
		for(int j=0; j<32; j++){
			dp[i][j] = max(dp[i+1][j>>1], dp[i+1][(j>>1)|16]);
			for(int ii=0; ii<ppl[i].size(); ii++){ pi k = ppl[i][ii];
				if((k.first & (31 - j)) || (k.second & j)){
					dp[i][j]++;
				}
			}
		}
	}
	return dp[1][b];
}
int main(){
	cin >> n >> c;
	for(int i=0; i<c; i++){
		int p, a, b, bs1 = 0, bs2 = 0;
		scanf("%d %d %d",&p,&a,&b);
		for(int i=0; i<a; i++){
			int t;
			scanf("%d",&t);
			if(t < p) t += n;
			bs1 |= (1 << (t - p)); 
		}
		for(int i=0; i<b; i++){
			int t;
			scanf("%d",&t);
			if(t < p) t += n;
			bs2 |= (1 << (t - p));
		}
		ppl[p].emplace_back(bs1, bs2);
	}
	int ret = 0;
	for(int i=0; i<32; i++){
		ret = max(ret, solve(i));
	}
	cout << ret;
}