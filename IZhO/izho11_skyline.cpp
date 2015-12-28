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
 
int a[305], n;
int dp[305][205][205];
 
int f(int pos, int t1, int t2){
    if(t1 < 0 || t2 < 0) return 1e9;
    if(pos == n) return 0;
    if(~dp[pos][t1][t2]) return dp[pos][t1][t2];
    int ret = min(f(pos, t1 - 1, t2) + 3, f(pos, t1 - 1, t2 - 1) + 5);
    ret = min(ret, f(pos+1, t2-t1, a[pos+2] - t1) + t1 * 7);
    return dp[pos][t1][t2] = ret;
}
 
int main(){
    scanf("%d",&n);
    memset(dp,-1,sizeof(dp));
    for(int i=0; i<n; i++){
        scanf("%d",&a[i]);
    }
    printf("%d",f(0, a[0], a[1]));
}