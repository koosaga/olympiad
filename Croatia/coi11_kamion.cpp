#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
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
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 10007;
 
int n, m, k;
char adj[55][55];
 
bool isalpha(char t){
    return (t >= 'a' && t <= 'z') || (t >= 'A' && t <= 'Z');
}
 
int f(int s, int e, int x);
int g(int s, int e, int x);
 
int dp1[55][55][55];
int dp2[55][55][55];
int dp3[55][55][55];
 
int g(int s, int e, int x){
    if(~dp1[s][e][x]) return dp1[s][e][x];
    int ret = 0;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(isalpha(adj[s][i]) && isalpha(adj[j][e]) && adj[s][i] - 'A' == adj[j][e] - 'a'){
                ret += f(i, j, x-2);
            }
        }
    }
    ret %= mod;
    return dp1[s][e][x] = ret;
}
 
int f(int s, int e, int x){
    if(~dp2[s][e][x]) return dp2[s][e][x];
    if(x == 0) return s == e;
    int ret = 0;
    for(int i=1; i<=n; i++){
        if(adj[s][i] == '-'){
            ret += f(i, e, x-1);
        }
        for(int j=2; j<=x; j++){
            ret += g(s, i, j) * f(i, e, x-j) % mod;
        }
        ret %= mod;
    }
    return dp2[s][e][x] = ret;
}
 
int f2(int s, int e, int x){
    if(x < 0) return 0;
    if(~dp3[s][e][x]) return dp3[s][e][x];
    int ret = (s == e);
    for(int i=1; i<=n; i++){
        if(adj[s][i] == '-'){
            ret += f2(i, e, x-1);
        }
        if(adj[s][i] <= 'Z' && adj[s][i] >= 'A'){
            ret += f2(i, e, x-1);
        }
        for(int j=2; j<=x; j++){
            ret += g(s, i, j) * f2(i, e, x-j) % mod;
        }
        ret %= mod;
    }
    return dp3[s][e][x] = ret;
}
 
int main(){
    memset(adj, -1, sizeof(adj));
    memset(dp1, -1, sizeof(dp1));
    memset(dp2, -1, sizeof(dp2));
    memset(dp3, -1, sizeof(dp3));
    scanf("%d %d %d\n",&n,&m,&k);
    for(int i=0; i<m; i++){
        char buf[55];
        fgets(buf, 55, stdin);
        int l = strlen(buf);
        if(isalpha(buf[l-2])){
            int x, y;
            sscanf(buf,"%d %d",&x,&y);
            adj[x][y] = buf[l-2];
        }
        else{
            int x, y;
            sscanf(buf,"%d %d",&x,&y);
            adj[x][y] = '-';
        }
    }
    cout << f2(1, n, k);
}