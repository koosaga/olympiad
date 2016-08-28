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
int adj[105][105], mid[105][105];
int dp[100005], cmpmax[105], cmppos[105];
int trace[100005];

void tracksp(int s, int e){
	if(adj[s][e] == 1){
		printf("%d ", e + 1);
		return;
	}
	int m = mid[s][e];
	tracksp(s, m);
	tracksp(m, e);
}

void track(int p){
	if(trace[p] == 0){
		for(int i=1; i<=p; i++){
			printf("%d ", a[i] + 1);
		}
		return;
	}
	track(trace[p]);
	tracksp(a[trace[p]], a[p]);
	int lef = p - trace[p] - adj[a[trace[p]]][a[p]];
	while(lef > 0){
		lef--;
		printf("%d ", a[p] + 1);
	}
}

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
				if(adj[j][k] > adj[j][i] + adj[i][k]){
					adj[j][k] = adj[j][i] + adj[i][k];
					mid[j][k] = i;
				}
			}
		}
	}
	int rmax = 0;
	for(int i=1; i<=q; i++){
		dp[i] = -1;
		for(int j=0; j<n; j++){
			if(adj[a[i]][j] <= n && dp[i] < cmpmax[j]){
				dp[i] = cmpmax[j];
				trace[i] = cmppos[j];
			}
		}
		for(int j=i-1; j>=max(1,i-n); j--){
			if(adj[a[i]][a[j]] <= i - j){
				if(dp[i] < dp[j]){
					dp[i] = dp[j];
					trace[i] = j;
				}
			}
		}
		if(i > n && cmpmax[a[i-n]] < dp[i-n]){
			cmpmax[a[i-n]] = dp[i-n];
			cmppos[a[i-n]] = i-n;
		}
		dp[i]++;
	}
	int pos = max_element(dp, dp + q + 1) - dp;
	printf("%d\n",q - dp[pos]);
	track(pos);
	for(int i=pos+1; i<=q; i++) printf("%d ",a[pos] + 1);
}