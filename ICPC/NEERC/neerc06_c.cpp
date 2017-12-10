#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

lint dp[30][505], ans[505];
int n, m, d, k, a[505];

int main(){
    cin >> n >> m >> d >> k;
    for(int i=0; i<n; i++){
        scanf("%d",&a[i]);
        if(min(i, n-i) <= d) dp[0][i] = 1;
    }
    ans[0] = 1;
    for(int i=0; i+1<30; i++){
        for(int j=0; j<n; j++){
            for(int k=0; k<n; k++){
                dp[i+1][(j+k)%n] += dp[i][j] * dp[i][k] % m;
                dp[i+1][(j+k)%n] %= m;
            }
        }
        if((k >> i) & 1){
            lint prv[505];
            memcpy(prv, ans, sizeof(prv));
            memset(ans, 0, sizeof(ans));
            for(int j=0; j<n; j++){
                for(int k=0; k<n; k++){
                    ans[(j+k)%n] += prv[j] * dp[i][k] % m;
                    ans[(j+k)%n] %= m;
                }
            }
        }
    }
    for(int i=0; i<n; i++){
        lint ret = 0;
        for(int j=0; j<n; j++){
            ret += a[j] * ans[(i - j + n) % n];
            ret %= m;
        }
        printf("%lld ", ret);
    }
}
