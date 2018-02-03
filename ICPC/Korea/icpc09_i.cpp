#include <bits/stdc++.h>
using namespace std;

int n, k, a[105];
double dp[105][105];

int main(){
    int t;
    cin >> t;
    while(t--){
        cin >> n >> k;
        for(int i=1; i<=n; i++) cin >> a[i], dp[0][i] = 1e9;
        sort(a+1, a+n+1);
        reverse(a+1, a+n+1);
        for(int i=1; i<=n; i++) a[i] += a[i-1];
        for(int i=1; i<=k; i++){
            for(int j=0; j<=n; j++){
                dp[i][j] = 1e9;
                for(int l=0; l<j; l++){
                    dp[i][j] = min(dp[i-1][l] + 1.0 * (a[j] - a[l]) * j / a[n], dp[i][j]);
                }
            }
        }
        printf("%.4f\n", dp[k][n]);
    }
}

