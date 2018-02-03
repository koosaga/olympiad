#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, k;
int a[5][10005];
int dp[10005][32][5];

void solve(){
    memset(dp,0,sizeof(dp));
    scanf("%d %d",&n,&k);
    for(int i=1; i<=n; i++){
        for(int j=0; j<5; j++){
            scanf("%d",&a[j][i]);
        }
    }
    if(k >= 5){
        int cnt = 0;
        for(int i=0;i<5; i++){
            cnt += *max_element(a[i] + 1, a[i] + 1 + n);
        }
        printf("%d\n",cnt);
        return;
    }
    for(int i=1; i<=n; i++){
        for(int j=0; j<32; j++){
            for(int k=1; k<5; k++){
                dp[i][j][k]= dp[i-1][j][k];
                for(int l=0; l<=j; l++){
                    if(l & (~j)) continue;
                    int p = dp[i-1][l][k-1];
                    int bit = (j & (~l));
                    for(int m=0; m<5; m++){
                        if((bit >> m) & 1) p += a[m][i];
                    }
                    dp[i][j][k] = max(dp[i][j][k], p);
                }
            }
        }
    }
    printf("%d\n",dp[n][31][k]);
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        solve();
    }
}