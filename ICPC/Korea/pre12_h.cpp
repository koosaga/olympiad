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
 
int n, k;
int a[100005];
int dfn[100005], rev[100005], piv, sz[100005];
vector<int> graph[100005];
 
void dfs(int x){
    dfn[x] = piv;
    rev[piv] = x;
    sz[x] = 1;
    piv++;
    for(auto &i : graph[x]){
        dfs(i);
        sz[x] += sz[i];
    }
}
 
int dp[100005][101][2];
 
void solve(){
    scanf("%d %d",&n,&k);
    for(int i=0; i<n; i++){
        scanf("%d",&a[i]);
    }
    for(int i=1; i<n; i++){
        int p;
        scanf("%d",&p);
        graph[p].push_back(i);
    }
    if(*max_element(a, a+n) < 0){
        printf("%d\n",*max_element(a,a+n));
        return;
    }
    memset(dp,0,sizeof(dp));
    dfs(0);
    for(int i=n-1; i>=0; i--){
        int pos = rev[i];
        dp[pos][1][1] = max(0, a[pos]);
        for(auto &j : graph[pos]){
            for(int l=min(k, sz[pos]); l>=0; l--){
                int p1 = 0, p2 = 0;
                for(int m=0; m<=l; m++){
                    p1 = max(p1, dp[pos][m][0] + dp[j][l-m][1]);
                    p2 = max(p2, dp[pos][m][1] + dp[j][l-m][0]);
                }
                dp[pos][l][0] = p1;
                dp[pos][l][1] = max(p1, p2);
            }
        }
    }
    int ret = 0;
    for(int i=1; i<=k; i++){
        ret = max(ret, dp[0][i][1]);
    }
    printf("%d\n",ret);
}
 
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        solve();
        piv = 0;
        for(int i=0; i<n; i++) graph[i].clear();
    }
}