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
const int mod = 1e9 + 7;

int n, a[305], b[305];
int cnt[305];

lint dp[305][305][305]; // (pos, used, oblige)

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d %d",&b[i],&a[i]); 
	}
	sort(a+1,a+n+1); 
	sort(b+1,b+n+1);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(b[i] < a[j]) cnt[i]++;
		}
	}
	dp[n][0][0] = 1;
	for(int i=n; i; i--){
		for(int j=0; j<=cnt[i]; j++){
			for(int k=0; k<=cnt[i]-j; k++){
				if(cnt[i] >= j) dp[i-1][j][cnt[i] - j] += dp[i][j][k]; // fill obliged ones
				if(k) dp[i-1][j+1][k-1] += dp[i][j][k] * k; // use obliged ones
				dp[i-1][j+1][k] += dp[i][j][k] * (cnt[i] - j - k); // use unobliged ones
			}
		}
		for(int j=0; j<=cnt[i]; j++){
			for(int k=0; k<=cnt[i]-j; k++){
				dp[i-1][j][k] %= mod;
			}
		}
	}
	int ret = 0;
	for(int i=0; i<=n; i++){
		ret += dp[0][i][0];
		ret %= mod;
	}
	printf("%d",ret);
}