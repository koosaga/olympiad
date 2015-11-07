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

vector<int> lessons[10005][105];
vector<int> slopes[105];

int dp[10005][105];
int pmax[10005][105];
int t, n, m;

int main(){
	scanf("%d %d %d",&t,&n,&m);
	for(int i=0; i<=10004; i++){
		fill(dp[i] + 1, dp[i] + 105, -1e9);
		fill(pmax[i] + 1, pmax[i] + 105, -1e9);
	}
	dp[1][1] = 0;
	for(int i=0; i<n; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		lessons[s+e][x].push_back(s);
	}
	for(int i=0; i<m; i++){
		int c, d;
		scanf("%d %d",&c,&d);
		slopes[c].push_back(d);
	}
	for(int i=1; i<=t+1; i++){
		for(int j=1; j<=100; j++){
			dp[i][j] = max(dp[i][j], dp[i-1][j]);
			for(int k=0; k<lessons[i][j].size(); k++){
				dp[i][j] = max(dp[i][j], pmax[lessons[i][j][k]][1]);
			}
			for(int k=0; k<slopes[j].size(); k++){
				if(i < slopes[j][k]) continue;
				dp[i][j] = max(dp[i][j], pmax[i - slopes[j][k]][j] + 1);
			}
		}
		for(int j=100; j; j--){
			pmax[i][j] = max(pmax[i][j+1], dp[i][j]);
		}
	}
	printf("%d",pmax[t+1][1]);
}