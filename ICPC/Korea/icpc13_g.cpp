#include <cstdio>

long long dp[105];
long long f(int x){
    if(dp[x]) return dp[x];
    return dp[x] = f(x-1) + f(x-5);
}

int main(){
    int t,x;
    scanf("%d",&t);
    dp[1] = dp[2] = dp[3] = 1;
    dp[4] = dp[5] = 2;
    while (t--) {
        scanf("%d",&x);
        printf("%lld\n",f(x));
    }
}