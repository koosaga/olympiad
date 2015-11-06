#include <cstdio>
#include <algorithm>
using namespace std;
 
int a[2005], b[2005];
int dp[2005][2005];
int lmin[2005][2005], rmin[2005][2005];
 
int main(){
    int n, m;
    scanf("%d %d",&n,&m);
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
    }
    for(int i=1; i<=m; i++){
        scanf("%d",&b[i]);
    }
    for(int i=1; i<=n; i++) a[i]--, a[i] += a[i-1];
    for(int i=1; i<=m; i++) b[i]--, b[i] += b[i-1];
    for(int i=0; i<=n; i++){
        fill(dp[i], dp[i] + m + 1, 2e9);
        fill(lmin[i], lmin[i] + m + 1, 2e9);
        fill(rmin[i], rmin[i] + m + 1, 2e9);
    }
    dp[0][0] = lmin[1][0] = rmin[0][1] = 0;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            dp[i][j] = min(lmin[i][j-1] + (a[i] - a[i-1]) * b[j], rmin[i-1][j] + (b[j] - b[j-1]) * a[i]);
            lmin[i][j] = min(lmin[i][j-1], dp[i-1][j] - b[j] * (a[i] - a[i-1]));
            rmin[i][j] = min(rmin[i-1][j], dp[i][j-1] - a[i] * (b[j] - b[j-1]));
        }
    }
    printf("%d",dp[n][m]);
}