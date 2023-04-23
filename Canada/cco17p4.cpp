#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

bitset<25005> dp[505];
int n, cnt[55], psum[55];
int main(){
    cin >> n;
    int ans = 0;
    for(int i=0; i<n; i++){
        int x;
        cin >> x;
        ans += x;
        cnt[x]++;
    }
    for(int i=50; i>=0; i--){
        psum[i] = psum[i+1] + cnt[i];
    }
    dp[n].set(0);
    for(int i=1; i<=50; i++){
        if(cnt[i] == 0){
            for(int j=0; j<=n; j++) dp[j] = (dp[j] << j);
            continue;
        }
        bitset<25005> prv[505], tot;
        for(int j=0; j<=n; j++){
            prv[j] = (dp[j] << j);
            dp[j].reset();
        }
        int cur = n;
        for(int j=n; j>=0; j--){
            while(cur >= max(j, psum[i])){
                tot |= prv[cur--];
            }
            if(j == 0 && cnt[i] == 1){
                if(cnt[i] == 1 && max(j, psum[i]) <= 1) dp[j] = prv[1];
            }
            else{
                dp[j] = tot;
            }
        }
    }
    for(int i=0; i<=50*n; i++){
        if(dp[0].test(i)) printf("%d ", i - ans);
    }
}
