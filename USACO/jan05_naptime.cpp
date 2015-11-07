#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
int n, b, a[3005];
int dp[3005][3005][2];
 
int f(int pos, int seg, int in_seg){
    if(seg < 0) return -1e9;
    if(seg == 0 || pos > n) return 0;
    if(~dp[pos][seg][in_seg]) return dp[pos][seg][in_seg];
    if(in_seg){
        return dp[pos][seg][in_seg] = max(f(pos+1,seg-1,1),f(pos+1,seg,0)) + a[pos];
    }
    else{
        return dp[pos][seg][in_seg] = max(f(pos+2,seg-2,1),f(pos+1,seg,0));
    }
}
 
int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%d %d",&n,&b);
    for (int i=1; i<=n; i++) {
        scanf("%d",&a[i]);
    }
    printf("%d",f(0,b+1,0));
}
