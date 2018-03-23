#include <cstdio>
#include <cstring>
typedef long long lint;

lint bino[25][25], dp[25][25];
lint fact[25];

lint f(int len, int peak){
    if(~dp[len][peak]) return dp[len][peak];
    if(len < peak || peak < 0) return 0;
    if(len == 0) return peak == 0;
    lint ret = 0;
    for(int i=0; i<len; i++){
        ret += f(i,peak-1) * bino[len-1][i] * fact[len-1-i];
    }
    return dp[len][peak] = ret;
}

int main(){
    fact[0] = 1;
    for(int i=1; i<=20; i++){
        fact[i] = fact[i-1] * i;
    }
    for(int i=0; i<=20; i++){
        bino[i][0] = 1;
        for(int j=1; j<=i; j++){
            bino[i][j] = bino[i-1][j] + bino[i-1][j-1];
        }
    }
    int t;
    scanf("%d",&t);
    while(t--){
        memset(dp,-1,sizeof(dp));
        int n, l, r;
        scanf("%d %d %d",&n,&l,&r);
        lint ret = 0;
        for(int i=1; i<=n; i++){
            ret += f(i-1,l-1) * f(n-i,r-1) * bino[n-1][i-1];
        }
        printf("%lld\n",ret);
    }

}