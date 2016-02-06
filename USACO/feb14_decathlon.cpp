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
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, b;
int arr[22][22];
vector<pi> bns[22];

int dp[1<<20];

int f(int x, int p){
	if(p == 0) return 0;
	if(~dp[x]) return dp[x];
	int ret = 0;
	for(int i=0; i<n; i++){
		if((x >> i) & 1){
			int tmp = f(x ^ (1<<i), p-1) + arr[i][p-1];
			for(auto &i : bns[p]){
				if(tmp >= i.first){
					tmp += i.second;
				}
			}
			ret = max(ret, tmp);
		}
	}
	return dp[x] = ret;
}

int main(){
	memset(dp, -1, sizeof(dp));
	cin >> n >> b;
	for(int i=0; i<b; i++){
		int p, q, r;
		cin >> p >> q >> r;
		bns[p].push_back(pi(q, r));
	}
	for(int i=1; i<=n; i++) sort(bns[i].begin(), bns[i].end());
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin >> arr[i][j];
		}
	}
	printf("%d",f((1<<n) - 1, n));
}