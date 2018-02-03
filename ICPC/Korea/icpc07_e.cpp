#include <cstdio>

int dp[33];

int main(){
    dp[0] = 1;
    dp[1] = 1;
    for(int i=2; i<=30; i++){
        dp[i] = dp[i-1] + 2ll * dp[i-2];
    }
    int n;
    scanf("%d",&n);
    if(n % 2 == 1) printf("%d", (dp[n] + dp[n/2]) / 2);
    else printf("%d",(dp[n] + dp[n/2] + 2 * dp[n/2 - 1]) / 2);
}