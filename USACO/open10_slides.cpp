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
 
int n, m, k;
vector<pi> graph[50005];
lint dp[50005][11];
 
lint f(int x, int y){
    if(x == n) return 0;
    if(~dp[x][y]) return dp[x][y];
    lint ret = 0, maxv = 1e18;
    for(auto &i : graph[x]){
        if(y) maxv = min(maxv, f(i.second, y-1) + i.first);
        ret = max(ret, f(i.second, k) + i.first);
    }
    if(y) ret = min(ret, maxv);
    return dp[x][y] = ret;
}
 
int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%d %d %d",&n,&m,&k);
    for(int i=0; i<m; i++){
        int s, e, x;
        scanf("%d %d %d",&s,&e,&x);
        graph[s].push_back(pi(x, e));
    }
    cout << f(1, k);
}