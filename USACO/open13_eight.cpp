#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
int n;
char a[305][305];
int low[305][305], low2[305][305];
 
short dp[305][305][305];
 
int dp2[305][305];
 
int solve2(int low, int p, int q){
    return dp2[p][q];
}
 
void make_dp(int p){
    memset(dp2,0,sizeof(dp2));
    for(int i=1; i<n; i++){
        for(int j=1; j+i<=n; j++){
            dp2[j][i+j] = max(dp2[j][i+j-1],max(dp2[j+1][i+j], (i - 1) * (p - dp[p][j][i+j] - 1)));
        }
    }
}
 
int solve(int p, int q){
    int ret = 0;
    for(int i=1; i<=n; i++){
        if(a[p][i] == '*' || a[q][i] == '*') continue;
        int e = i;
        while(e <= n && a[p][e] == '.' && a[q][e] =='.'){
            e++;
        }
        int st = i, ed = e-1;
        while(st < e && low[p][st] != low[q][st]){
            st++;
        }
        while(st < ed && low[p][ed] != low[q][ed]){
            ed--;
        }
        if(st + 1 < ed){
            ret = max(ret, solve2(p, st, ed) * (q - p - 1) * (ed - st - 1));
        }
        i = e;
    }
    return ret;
}
 
int main(){
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        for(int j=i+2; j<=n; j++){
            dp[0][i][j] = 1e4;
        }
    }
    for(int i=1; i<=n; i++){
        scanf("%s",a[i]+1);
        for(int j=1; j<=n; j++){
            low[i][j] = low[i-1][j] + (a[i][j] == '*');
            low2[i][j] = low2[i][j-1] + (a[i][j] == '*');
        }
        for(int j=1; j<=n; j++){
            for(int k=j+2; k<=n; k++){
                if(a[i][j] == '*' || a[i][k] == '*'){
                    dp[i][j][k] = 1e4;
                }
                else{
                    dp[i][j][k] = dp[i-1][j][k];
                }
                if(low2[i][j-1] == low2[i][k]){
                    dp[i][j][k] = min(dp[i][j][k], (short)i);
                }
            }
        }
    }
    int ret = 0;
    for(int i=1; i<=n; i++){
        make_dp(i);
        for(int j=i+2; j<=n; j++){
            ret = max(ret,solve(i,j));
        }
    }
    if(ret == 0) ret = -1;
    printf("%d", ret);
}