#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
int a[100005], n, k;
int coin[20];
int dp[1<<16];
 
int f(int bit){
    if(~dp[bit]) return dp[bit];
    int ret = 0;
    for(int j=0; j<k; j++){
        if((bit >> j) & 1){
            int pos = f(bit^(1<<j));
            ret = max(ret,(int)(upper_bound(a+1,a+n+1,a[pos] + coin[j]) - a - 1));
        }
    }
    return dp[bit] = ret;
}
 
int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%d %d",&k,&n);
    for(int i=0; i<k; i++){
        scanf("%d",&coin[i]);
    }
    for(int i=1; i<=n; i++){
        scanf("%d",&a[i]);
        a[i] += a[i-1];
    }
    int ret = -1;
    for(int i=0; i<(1<<k); i++){
        int cnt = 0;
        for(int j=0; j<k; j++){
            if((i >> j) & 1) continue;
            cnt += coin[j];
        }
        if(f(i) == n) ret = max(ret,cnt);
    }
    printf("%d",ret);
}