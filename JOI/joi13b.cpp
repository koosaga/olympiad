#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
int n,m;
char s[2005],t[2005];
int dp[2005][2005][2];
 
int f(int x, int y, int isI){
    if(x == n && y == m) return isI == 0? 0 : -123456;
    if(dp[x][y][isI]) return dp[x][y][isI];
    int res = 0;
    if(isI == 1){
        if(x < n && s[x] == 'I') res = max(res,f(x+1,y,0)+1);
        if(y < m && t[y] == 'I') res = max(res,f(x,y+1,0)+1);
        if(res == 0) return -123456;
    }
    else{
        if(x < n &&s[x] == 'O') res = max(res,f(x+1,y,1)+1);
        if(y < m &&t[y] == 'O') res = max(res,f(x,y+1,1)+1);
        if(res == 0) return 0;
    }
    return dp[x][y][isI] = res;
}
 
int main(){
    int res = 0;
    scanf("%d %d %s %s",&n,&m,s,t);
    for (int i=0; i<=n; i++) {
        for (int j=0; j<=m; j++) {
            res = max(res,f(i,j,1));
        }
    }
    printf("%d",res);
}