#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
 
int n,p,q,a[2005];
int nxt[2005], nxt2[2005];
 
int dp[2005][2005];
 
bool trial(int x){
    for (int i=0; i<n; i++) {
        nxt[i] = (int)(lower_bound(a,a+n,a[i]+x) - a);
        nxt2[i] = (int)(lower_bound(a,a+n,a[i]+2*x) - a);
    }
    nxt[n] = nxt2[n] = n;
    for (int i=p; i>=0; i--) {
        for (int j=q; j>=0; j--) {
            if(i == p && j == q) continue;
            int ret = 0;
            if(i != p) ret = max(ret,nxt[dp[i+1][j]]);
            if(j != q) ret = max(ret,nxt2[dp[i][j+1]]);
            dp[i][j] = ret;
        }
    }
    return dp[0][0] >= n;
}
 
int main(){
    scanf("%d %d %d",&n,&p,&q);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
    }
    p = min(p,n);
    q = min(q,n);
    sort(a,a+n);
    int s = 0, e = 5e8;
    while (s != e) {
        int m = (s+e)/2;
        if(trial(m)) e = m;
        else s = m+1;
    }
    printf("%d",s);
}