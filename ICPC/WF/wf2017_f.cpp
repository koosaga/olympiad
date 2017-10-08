#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
const int mod = 1e9 + 7;
typedef pair<int, int> pi;

int d, k, a[300];
lint dp[300][300];
lint cost[300][300];

int main(){
    cin >> d >> k;
    for(int i=0; i<d; i++){
        int x;
        cin >> x;
        cin >> a[x];
    }
    for(int i=0; i<256; i++){
        for(int j=i; j<256; j++){
            lint sum = 0;
            for(int k=i; k<=j; k++) sum += a[k];
            if(sum == 0) continue;
            sum = (sum + 1) / 2;
            lint s1 = 0, s2 = 0;
            for(int k=i; k<=j; k++){
                s1 += 1ll * a[k] * k;
                s2 += a[k];
            }
            lint med = s1 / s2;
            s1 %= s2;
            if(s1 > s2 / 2) med++;
            for(int k=i; k<=j; k++){
                cost[i][j] += 1ll * a[k] * (k - med) * (k - med);
            }
        }
    }
    for(int i=0; i<256; i++) dp[1][i] = cost[0][i];
    for(int i=2; i<=k; i++){
        for(int j=0; j<256; j++){
            dp[i][j] = 1e18;
            for(int k=0; k<j; k++){
                dp[i][j] = min(dp[i][j], dp[i-1][k] + cost[k+1][j]);
            }
        }
    }
    cout << dp[k][255];
}
