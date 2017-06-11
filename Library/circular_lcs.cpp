#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <complex>
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
typedef complex<double> pnt;
 
string s1, s2;
 
int dp[4005][2005];
int nxt[4005][2005];
int n, m;
 
void reroot(int px){
    int py = 1;
    while(py <= m && nxt[px][py] != 2) py++;
    nxt[px][py] = 1;
    while(px < 2 * n && py < m){
        if(nxt[px+1][py] == 3){
            px++;
            nxt[px][py] = 1;
        }
        else if(nxt[px+1][py+1] == 2){
            px++;
            py++;
            nxt[px][py] = 1;
        }
        else py++;
    }
    while(px < 2 * n && nxt[px+1][py] == 3){
        px++;
        nxt[px][py] = 1;
    }
}
 
int track(int x, int y, int e){
    int ret = 0;
    while(y != 0 && x != e){
        if(nxt[x][y] == 1) y--;
        else if(nxt[x][y] == 2) ret += (s1[x] == s2[y]), x--, y--;
        else if(nxt[x][y] == 3) x--;
    }
    return ret;
}
 
int solve(string a, string b){
    s1 = a, s2 = b;
    n = s1.size(), m = s2.size();
    s1 = s1 + s1;
    s1 = '#' + s1;
    s2 = '#' + s2;
    for(int i=0; i<=2*n; i++){
        for(int j=0; j<=m; j++){
            if(j == 0){
                nxt[i][j] = 3;
                continue;
            }
            if(i == 0){
                nxt[i][j] = 1;
                continue;
            }
            dp[i][j] = -1;
            if(dp[i][j] < dp[i][j-1]){
                dp[i][j] = dp[i][j-1];
                nxt[i][j] = 1;
            }
            if(dp[i][j] < dp[i-1][j-1] + (s1[i] == s2[j])){
                dp[i][j] = dp[i-1][j-1] + (s1[i] == s2[j]);
                nxt[i][j] = 2;
            }
            if(dp[i][j] < dp[i-1][j]){
                dp[i][j] = dp[i-1][j];
                nxt[i][j] = 3;
            }
        }
    }
    int ret = dp[n][m];
    for(int i=1; i<n; i++){
        reroot(i);
        ret = max(ret, track(n+i, m, i));
    }
    return ret;
}
 
int main(){
    string a, b;
    cin >> a >> b;
    int ret = solve(a, b);
    reverse(b.begin(), b.end());
    ret = max(ret, solve(a, b));
    cout << ret;
}