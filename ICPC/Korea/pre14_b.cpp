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

int dp[105][105][105][2];
int a[105][105], b[105][105];
int m, n, l, g;

int f(int x, int y, int t, int state_bef){
    if(t < 0) return 1e9;
    if(y == n || x == m) return 1e9;
    if(y == n-1 && x == m-1) return 0;
    if(~dp[x][y][t][state_bef]) return dp[x][y][t][state_bef];
    int ret = 1e9;
    if(state_bef == 0){
        ret = min(ret, f(x+1, y, t, state_bef) + b[x][y]);
        ret = min(ret, f(x, y+1, t-1, !state_bef) + a[x][y]);
    }
    if(state_bef == 1){
        ret = min(ret, f(x, y+1, t, state_bef) + a[x][y]);
        ret = min(ret, f(x+1, y, t-1, !state_bef) + b[x][y]);
    }
    return dp[x][y][t][state_bef] = ret;
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d %d %d %d",&m,&n,&l,&g);
        for(int i=0; i<m; i++){
            for(int j=0; j<n-1; j++){
                scanf("%d",&a[i][j]);
            }
        }
        for(int i=0; i<m-1; i++){
            for(int j=0; j<n; j++){
                scanf("%d",&b[i][j]);
            }
        }
        memset(dp,-1,sizeof(dp));
        bool fnd = 0;
        for(int i=0; i<=max(n, m); i++){
            if(min(f(0, 0, i,0),f(0,0,i,1)) <= g){
                printf("%d\n",i + (n+m-2) * l);
                fnd = 1;
                break;
            }
        }
        if(!fnd) puts("-1");
    }
}