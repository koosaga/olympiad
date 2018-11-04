#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;

int m, n;
int msk[30], cnt[30], k;

void bktk(int ccnt, int pos, int cmsk){
    if(pos == m){
        msk[k] = cmsk;
        cnt[k] = ccnt;
        k++;
        return;
    }
    bktk(ccnt, pos + 1, cmsk);
    if(pos + 3 <= m) bktk(ccnt + 1, pos + 3, cmsk | (7 << pos));
}

int dp[1005][30][30], a[1005];

int main(){
    int t;
    cin >> t;
    while(t--){
        cin >> m >> n;
        k = 0;
        memset(a, 0, sizeof(a));
        bktk(0, 0, 0);
        msk[k] = (1<<m) - 1, cnt[k] = (m + 2) / 3, k++;
        int q;
        cin >> q;
        while(q--){
            int x, y;
            scanf("%d %d",&x,&y);
            a[y-1] |= (1<<(x-1));
        }
        memset(dp, 0x3f, sizeof(dp));
        dp[n][0][0] = 0;
        for(int i=n-1; i>=0; i--){
            for(int j=0; j<k; j++){
                for(int l=0; l<k; l++){
                    for(int m=0; m<k; m++){
                        if(a[i] & ~(msk[j] | msk[l] | msk[m])) continue;
                        dp[i][j][l] = min(dp[i][j][l], dp[i+1][l][m] + cnt[m]);
                    }
                }
            }
        }
        cout << dp[0][0][0] << endl;
    }
}
