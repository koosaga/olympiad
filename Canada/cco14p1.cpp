#include <cstdio>
#include <algorithm>
using namespace std;

char str[2005][2005];
int dp[2005][2005];
int n, m;

int main(){
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        scanf("%s",str[i] + 1);
    }
    long long ret = 0;
    for(int i=n; i; i--){
        for(int j=1; j<=n; j++){
            if(str[i][j] == '#'){
                dp[i][j] = min(dp[i+1][j-1], min(dp[i+1][j], dp[i+1][j+1])) + 1;
                ret += dp[i][j];
            }
        }
    }
    printf("%lld",ret);
}