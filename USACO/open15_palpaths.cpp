#include <cstdio>
 
int n;
char str[505][505];
int dp[2][505][505];
const int mod = 1e9 + 7;
 
int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%s",str[i]);
    }
    if(str[0][0] != str[n-1][n-1]){
        puts("0");
        return 0;
    }
    dp[0][0][0] = 1;
    int ret = 0;
    for (int i=1; i<n; i++) {
        for (int j=0; j<=i; j++) {
            for (int k=0; k<=i; k++) {
                int px = i - j, py = j;
                int qx = n - 1 + k - i, qy = n - 1 - k;
                if(str[px][py] == str[qx][qy]){
                    dp[i%2][j][k] = dp[(i-1)%2][j][k];
                    if(j) dp[i%2][j][k] += dp[(i-1)%2][j-1][k];
                    dp[i%2][j][k] %= mod;
                    if(k) dp[i%2][j][k] += dp[(i-1)%2][j][k-1];
                    dp[i%2][j][k] %= mod;
                    if(j && k) dp[i%2][j][k] += dp[(i-1)%2][j-1][k-1];
                    dp[i%2][j][k] %= mod;
                }
                else dp[i%2][j][k] = 0;
            }
        }
    }
    for (int i=0; i<n; i++) {
        ret += dp[(n-1)%2][n-i-1][i];
        ret %= mod;
    }
    printf("%d",ret);
}