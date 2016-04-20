#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int a[10005],n;
int dp[2][5005][2];

int main(){
    scanf("%d",&n);
    for (int i=0; i<n-1; i++) {
        scanf("%d",&a[i]);
    }
    for (int j=1; j<=n/2; j++) {
        dp[0][j][0] = 1e9;
        dp[0][j][1] = 1e9;
    }
    for (int i=1; i<=n-1; i++) {
        for (int j=0; j<=n/2-1; j++) {
            dp[i%2][j][0] = min((j?dp[(i-1)%2][j-1][0]:987654321),dp[(i-1)%2][j][1] + a[i-1]);
            dp[i%2][j][1] = min(dp[(i-1)%2][j][1],(j?dp[(i-1)%2][j-1][0]:987654321) + a[i-1]);
        }
    }
    printf("%d",dp[(n-1)%2][n/2-1][0]);
}