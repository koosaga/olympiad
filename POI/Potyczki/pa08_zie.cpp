#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
using pi = pair<int, int>;
const int MAXN = 105;
const int mod = 1e9 + 7;
 
int ccw(pi a, pi b, pi c){
    int dx1 = b.first - a.first;
    int dy1 = b.second - a.second;
    int dx2 = c.first - a.first;
    int dy2 = c.second - a.second;
    return dx1 * dy2 - dy1 * dx2;
}
 
int n, k;
pi a[MAXN];
int dp[MAXN][MAXN];
 
int main(){
    cin >> n >> k;
    for(int i=0; i<n; i++) cin >> a[i].first >> a[i].second;
    int ans = 0;
    for(int i=2; i<n; i++) ans += ccw(a[0], a[i-1], a[i]);
    if(ans < 0) reverse(a, a+n);
    int dap = 0;
    for(int t=0; t<n; t++){
        rotate(a, a+1, a+n);
        memset(dp, 0, sizeof(dp));
        for(int i=1; i<=k-2; i++){
            for(int j=1; j<n; j++){
                for(int k=1; k<j; k++){
                    dp[i][j] = max(dp[i-1][k] + ccw(a[0], a[k], a[j]), dp[i][j]);
                }
            }
        }
        dap = max(dap, *max_element(dp[k-2] + 1, dp[k-2] + n));
    }
    printf("%.1f\n", 0.5 * dap);
}
 
