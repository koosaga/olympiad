#include <cstdio>
#include <algorithm>
using namespace std;
const int mod = 1e9 + 9;
 
char str[30005];
int n;
int dp[2][15005];
 
int main(){
    scanf("%d %s",&n,str); 
    dp[n%2][0] = 1;
    for(int i=n-1; i>=0; i--){
        for(int j=0; j<=min(n - i,i); j++){
            if(str[i] == ')'){
                dp[i%2][j] = 0;
                if(j) dp[i%2][j] = dp[(i+1)%2][j-1];
                continue;
            }
            dp[i%2][j] = dp[(i+1)%2][j+1];
            if(j) dp[i%2][j] += dp[(i+1)%2][j-1];
            dp[i%2][j] %= mod;
        }
    }
    printf("%d",dp[0][0]);
}