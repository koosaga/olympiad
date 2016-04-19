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
 
char str[2005][2005];
bool vis[2005][2005];
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
 
int n, m;
int arr[2005][2005], dp[2005][2005];
 
vector<pi> pnt;
queue<int> qx, qy;
 
void bfs(int x, int y){
    qx.push(x);
    qy.push(y);
    vis[x][y] = 1;
    while(!qx.empty()){
        int x = qx.front();
        int y = qy.front();
        qx.pop(), qy.pop();
        pnt.push_back(pi(y, str[x][y] - '0'));
        for(int i=0; i<4; i++){
            if(x + dx[i] < 0 || x + dx[i] >= n || y + dy[i] < 0 || y + dy[i] >= m){
                continue;
            }
            if(str[x+dx[i]][y+dy[i]] == '.') continue;
            if(vis[x + dx[i]][y + dy[i]]) continue;
            vis[x + dx[i]][y + dy[i]] = 1;
            qx.push(x + dx[i]);
            qy.push(y + dy[i]);
        }
    }
}
 
inline int cost(int i, int j){
    return arr[j][j] - arr[i-1][j] - arr[j][i-1] + arr[i-1][i-1];
}
 
void solve(int *pdp, int *dp, int s, int e, int ps, int pe){
    if(ps > pe) return;
    int pm = (ps + pe) / 2;
    int opt = -1;
    for(int i=s; i<=min(e, pm-1); i++){
        if(dp[pm] > pdp[i] + cost(i+1, pm-1)){
            dp[pm] = pdp[i] + cost(i+1, pm-1);
            opt = i;
        }
    }
    solve(pdp, dp, s, opt, ps, pm-1);
    solve(pdp, dp, opt, e, pm+1, pe);
}
 
int main(){
    scanf("%d %d",&n,&m);
    for(int i=0; i<n; i++){
        scanf("%s",str[i]);
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(!vis[i][j] && str[i][j] != '.'){
                pnt.clear();
                bfs(i, j);
                int ret = 0, sy = 1e9, ey = 0;
                for(auto &i : pnt){
                    ret += i.second;
                    sy = min(sy, i.first);
                    ey = max(ey, i.first);
                }
                arr[sy+1][ey+1] += ret;
            }
        }
    }
    for(int i=1; i<=m+1; i++){
        for(int j=1; j<=m+1; j++){
            arr[i][j] += arr[i][j-1] + arr[i-1][j] - arr[i-1][j-1];
        }
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;
    solve(dp[0], dp[1], 0, m, 1, m+1);
    for(int i=2; i<=m+1; i++){
        solve(dp[i-1], dp[i], 0, m+1, 0, m+1);
        printf("%d\n", arr[m][m] - dp[i][m+1]);
    }
}