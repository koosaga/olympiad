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

int n;
lint k, dp[22];

void solve(int offset, int sz, lint pos){
	if(sz == 0) return;
	for(int i=0; i<sz; i++){
		if(pos < dp[i] * dp[sz-i-1]){
			printf("%c", offset + i + 'a');
			solve(offset, i, pos / dp[sz-i-1]);
			solve(offset + i + 1, sz-i-1, pos % dp[sz-i-1]);
			return;
		}
		pos -= dp[i] * dp[sz-i-1];
	}
}
int main(){
	cin >> k >> n;
	dp[0] = 1;
	for(int i=1; i<=n; i++){
		for(int j=0; j<i; j++){
			dp[i] += dp[j] * dp[i-j-1];
		}
	}
	solve(0, n, k-1);
}

