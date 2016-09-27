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

int dp[405][405][405];
int n, a[405], b[405];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	for(int i=1; i<=n; i++){
		scanf("%d",&b[i]);
	}
	for(int i=0; i<=n; i++){
		for(int j=0; j<=n; j++){
			for(int k=0; k<=n; k++){
				if(i + j == 0) continue;
				dp[i][j][k] = -1e9;
				if(i && k >= (a[i] != 0)) dp[i][j][k] = max(dp[i-1][j][k - (a[i] != 0)], dp[i][j][k]);
				if(j && k >= (b[j] != 0)) dp[i][j][k] = max(dp[i][j-1][k - (b[j] != 0)], dp[i][j][k]);
				if(i && j && k >= (a[i] != 0 || b[j] != 0)) dp[i][j][k] = max(dp[i-1][j-1][k - (a[i] != 0 || b[j] != 0)] + a[i] * b[j], dp[i][j][k]);
			}
		}
	}
	printf("%d",dp[n][n][n]);
}
