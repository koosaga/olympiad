#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
const int mod = 1000007;
 
int n, a[10005];
 
int dp[2][2][10005];
 
int main(){
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
    }
    for(int i=n+1; i; i--){
        for(int j=1; j<=i; j++){
            int C = i%2;
            int P = (i+1)%2;
            dp[C][0][j] = dp[C][1][j] = 0;
            if(i == n+1){
                dp[C][0][j] = dp[C][1][j] = 1;
                continue;
            }
            dp[C][0][j] = (1ll * dp[P][0][j] * j + dp[P][0][j+1]) % mod;
            if(j + 1 < a[i]){
                dp[C][1][j] += dp[P][0][j+1];
            }
            else if(j + 1 == a[i]){
                dp[C][1][j] += dp[P][1][j+1];
            }
            if(j >= a[i]){
                dp[C][1][j] = dp[P][1][j];
            }
            dp[C][1][j] += (1ll * min(a[i]-1,j) * dp[P][0][j]) % mod;
            dp[C][1][j] %= mod;
        }
    }
    printf("%d",dp[1][1][1]);
}