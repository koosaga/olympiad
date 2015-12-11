#include <cstdio>
#include <cstring>
const int mod = 2012;
 
char str[1005];
int dp[1005][1005];
 
int f(int pos, int h, int g){
    if(str[pos] == 0) return (h == 0 && g == 0);
    if(~dp[pos][h]) return dp[pos][h];
    int ret = 0;
    if(str[pos] == '(') ret += f(pos+1,h+1,g) + f(pos+1,h,g+1);
    if(str[pos] == ')'){
        if(h) ret += f(pos+1,h-1,g);
        if(g) ret += f(pos+1,h,g-1);
    }
    ret %= mod;
    return dp[pos][h] = ret;
}
 
int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%s",str);
    printf("%d",f(0,0,0));
}