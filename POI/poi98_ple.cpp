#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
 
int t,a,n,ts[1005],as[1005],ws[1005];
 
int dp[22][80][1005];
int f(int t, int a, int pos){
    if(t == 0 && a == 0) return 0;
    if(pos == n) return 1e9;
    if(~dp[t][a][pos]) return dp[t][a][pos];
    return dp[t][a][pos] = min(f(t,a,pos+1),f(max(t-ts[pos],0),max(a-as[pos],0),pos+1) + ws[pos]);
}
void solve(){
    memset(dp,-1,sizeof(dp));
    scanf("%d %d %d",&t,&a,&n);
    for (int i=0; i<n; i++) {
        scanf("%d %d %d",&ts[i],&as[i],&ws[i]);
    }
    printf("%d\n",f(t,a,0));
}
int main(){
    int t;
    scanf("%d",&t);
    while (t--) {
        solve();
    }
}