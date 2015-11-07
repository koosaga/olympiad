#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

int dp[100005][105];
int n,c,a[100005];

int main(){
    scanf("%d %d",&n,&c);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
    }
    memset(dp,0x3f,sizeof(dp));
    for (int i=a[0]; i<=100; i++) {
        dp[0][i] = (i - a[0]) * (i - a[0]);
    }
    for (int i=1; i<n; i++) {
        // low table
        int tab_low[105], tab_high[105];
        tab_low[0] = dp[i-1][0] - 0 * c;
        for (int j=1; j<=100; j++) {
            tab_low[j] = min(tab_low[j-1],dp[i-1][j] - j * c);
        }
        tab_high[100] = dp[i-1][100] + 100 * c;
        for (int j=99; j>=0; j--) {
            tab_high[j] = min(tab_high[j+1],dp[i-1][j] + j * c);
        }
        for (int j=a[i]; j<=100; j++) {
            dp[i][j] = min(dp[i][j],tab_low[j] + j*c + (j - a[i]) * (j - a[i]));
            dp[i][j] = min(dp[i][j],tab_high[j] - j*c + (j - a[i]) * (j - a[i]));
        }
    }
    printf("%d",*min_element(dp[n-1],dp[n-1]+101));
}