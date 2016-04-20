#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
int n,t,s,a[3005],b[3005];
int dp[3005][3005];
 
int f(int pos, int x){
    if(pos == n) return 0;
    if(~dp[pos][x]) return dp[pos][x];
    int r = f(pos+1,x);
    if(x < s && s < x+b[pos]){
        if(s+b[pos] <= t) r = max(r, f(pos+1,s+b[pos]) + a[pos]);
    }
    else if(x+b[pos] <= t) r = max(r,f(pos+1,x+b[pos]) + a[pos]);
    return dp[pos][x] = r;
}
 
int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%d %d %d",&n,&t,&s);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&a[i],&b[i]);
    }
    printf("%d",f(0,0));
}