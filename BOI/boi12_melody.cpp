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

int n, s, g, q, a[100005];
char str[105][105];
int adj[105][105];
int dp[100005], cmpmax[105];

int main(){
	scanf("%d %d %d",&n,&s,&g);
	for(int i=0; i<n; i++){
		scanf("%s",str[i]);
	}
	scanf("%d",&q);
	for(int i=1; i<=q; i++){
		scanf("%d",&a[i]);
		a[i]--;
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			int cnt = 0;
			for(int k=0; k<s; k++){
				if(str[i][k] != str[j][k]) cnt++;
			}
			adj[i][j] = (cnt <= g ? 1 : 1e9);
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			for(int k=0; k<n; k++){
				adj[j][k] = min(adj[j][k], adj[j][i] + adj[i][k]);
			}
		}
	}
	int rmax = 0;
	for(int i=1; i<=q; i++){
		for(int j=0; j<n; j++){
			if(adj[a[i]][j] <= n) dp[i] = max(dp[i], cmpmax[j]);
		}
		for(int j=i-1; j>=max(1,i-n); j--){
			if(adj[a[i]][a[j]] <= i - j){
				dp[i] = max(dp[i], dp[j]);
			}
		}
		if(i > n) cmpmax[a[i-n]] = max(cmpmax[a[i-n]], dp[i-n]);
		dp[i]++;
	}
	printf("%d",q - *max_element(dp, dp + q + 1));
}