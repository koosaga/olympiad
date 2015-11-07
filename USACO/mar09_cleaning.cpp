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

int n, m, bef[40005], dp[40005], nxt[40005], t;

int find(int x){
	return nxt[x] = (nxt[x] == x ? x : find(nxt[x]));
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		nxt[i] = i;
	}
	memset(bef, -1, sizeof(bef));
	for(int i=1; i<=n; i++){
		scanf("%d",&t);
		if(bef[t] != -1) nxt[bef[t]] = nxt[bef[t] - 1];
		bef[t] = i;	
		nxt[i] = i;
		dp[i] = i;
		int cnt = 0, pos = i;
		while(pos > 1 && cnt * cnt < i){
			pos = find(pos - 1);
			cnt++;
			dp[i] = min(dp[i], dp[pos] + cnt * cnt);
		}
	}
	printf("%d",dp[n]);
}