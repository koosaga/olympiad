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
const int offset = 1e4;

int n, t, a[105];
int dp[105][20005], tra[105][20005];

bool f(int pos, int sum){
	if(pos == n) return (sum == t);
	if(~dp[pos][sum + offset]) return dp[pos][sum + offset];
	if(f(pos + 1, sum + a[pos])){
		tra[pos][sum + offset] = 1;
		return dp[pos][sum + offset] = 1;
	}
	else if(f(pos + 1, sum - a[pos])){
		tra[pos][sum + offset] = -1;
		return dp[pos][sum + offset] = 1;
	}
	return dp[pos][sum + offset] = 0;
}

int sgn[105];

int main(){
	scanf("%d %d",&n,&t);
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
	}
	if(n == 1){
		return 0;
	}
	memset(dp,-1,sizeof(dp));
	f(2, a[0] - a[1]);
	int sum = a[0] - a[1];
	sgn[1] = -1;
	for(int i=2; i<n; i++){
		int t = tra[i][sum + offset];
		sgn[i] = t;
		if(t > 0) sum += a[i];
		else sum -= a[i];
	}
	int cnt = 0;
	for(int i=n-1; i>1; i--){
		int p = i;
		while(p > 1 && sgn[p] >= 1) p--;
		for(int j=i-1; j>=p; j--){
			printf("%d\n",p+1);
			cnt++;
		}
		i = p;
	}
	for(int i=cnt; i<n-1; i++){
		puts("1");
	}
}