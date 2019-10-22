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
const int offset = 505;
 
#define whatthe(i,j,k) (255000 * i + 505 * j + k)
 
int dp[offset * offset * offset];
bool can[505][505];
int n, c[505], a[505], v[505];
 
inline void f(int s1, int s2, int peak){
	int ret = 0;
	bool sw = 0;
	int pop = (s1 > s2 ? peak : s2) + 1;
	if(s1 > s2) swap(s1, s2), sw = 1;
	if(can[s1][peak]){
		int t = dp[whatthe(s2, pop, s1)];
		if(t == -1) f(s2, pop, s1), t = dp[whatthe(s2, pop, s1)];
		ret = max(ret, v[s1] + t);
	}
	if(can[pop][peak]){
		int t = dp[whatthe(s2, s1, pop)];
		if(t == -1) f(s2, s1, pop), t = dp[whatthe(s2, s1, pop)];
		ret = max(ret, v[pop] + t);
	}
	if(sw) swap(s1, s2);
	dp[whatthe(s1, s2, peak)] = ret;
}
 
int main(){
	memset(dp,-1,sizeof(dp));
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d %d %d",&c[i],&a[i],&v[i]);
	}
	for(int i=1; i<=n; i++){
		can[i][0] = 1;
		for(int j=1; j<=n; j++){
			can[i][j] = (a[i] == a[j] || c[i] == c[j]);
		}
	}
	f(1, 2, 0);
	printf("%d\n",dp[whatthe(1, 2, 0)]);
}
