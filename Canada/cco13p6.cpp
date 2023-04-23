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

int dp[2][10005];

char a[10005];
int n, mod;

int main(){
    scanf("%s %d",a+1,&mod);
    n = (int)strlen(a+1);
    fill(dp[0], dp[0] + n + 1, 1);
    for(int i=1; i<=n; i++){
        dp[i&1][0] = 1;
        int sum[130] = {};
        for(int j=1; j<=n; j++){
            sum[a[j]] = (sum[a[j]] + dp[(i-1)&1][j-1]) % mod;
            dp[i&1][j] = (dp[(i-1)&1][j] + sum[a[i]]) % mod;
        }
    }
    printf("%d",dp[n&1][n]);
}