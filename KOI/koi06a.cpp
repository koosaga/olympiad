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
  
int n;
pi a[10005];
int dp[10005];
int main(){
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        scanf("%d %d",&a[i].first, &a[i].second);
        a[i].second = 2 * abs(a[i].second);
    }
    sort(a+1,a+n+1);
    for(int i=1; i<=n; i++){
        int maxp = a[i].second;
        dp[i] = 1e9;
        for(int j=i-1; j>=0; j--){
            dp[i] = min(dp[i], dp[j] + max(a[i].first - a[j+1].first, maxp));
            maxp = max(a[j].second, maxp);
        }
    }
    printf("%d",dp[n]);
}