#include <cstdio>
#include <cstring>

int cnt1[1005], cnt2[1005];
int n;

void solve(){
    memset(cnt1,0,sizeof(cnt1));
    memset(cnt2,0,sizeof(cnt2));
    scanf("%d",&n);
    for (int i=1; i<n; i++) {
        for (int j=i+1; j<=n; j++) {
            int t;
            scanf("%d",&t);
            if(t == 1) cnt1[i]++, cnt1[j]++;
            else cnt2[i]++, cnt2[j]++;
        }
    }
    int r = n * (n-1) * (n-2) / 3;
    for (int i=1; i<=n; i++) {
        r -= cnt1[i] * cnt2[i];
    }
    printf("%d\n",r/2);
}
int main(){
    int t;
    scanf("%d",&t);
    while (t--) {
        solve();
    }
}