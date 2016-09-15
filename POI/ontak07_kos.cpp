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
#include <assert.h>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

lint dp[66][66], b;
int n, m;

lint f(int x, int y){
	if(x == n) return 1;
	if(~dp[x][y]) return dp[x][y];
	lint ret = 0;
	for(int i=y; i<=m; i++){
		ret += f(x+1, i);
		ret = min(ret, b+1);
	}
	return dp[x][y] = ret;
}

void trace(int x, int y, lint b){
	if(x == n) return;
	for(int i=y; i<=m; i++){
		lint v = f(x+1, i);
		if(b > v) b -= v;
		else{
			printf("%d ", i);
			trace(x+1, i, b);
			return;
		}
	}
}

int main(){
	memset(dp, -1, sizeof(dp));
	cin >> n >> m >> b;
	f(0, 1);
	trace(0, 1, b);
}

