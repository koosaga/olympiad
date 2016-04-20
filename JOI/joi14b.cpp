#include <cstdio>
#include <cstring>
#include <algorithm>
 
int m,n,a[10005];
int sm[10005];
 
int bv[505],bc[505];
int dp[505][10005];
 
int cmp(int a, int b){return a>b;}
 
int f(int pos, int got){
    if(pos == n || got >= m) return sm[got<m?got:m];
    if(dp[pos][got]) return dp[pos][got];
    return dp[pos][got]=std::max(f(pos+1,got),f(pos+1,got+bv[pos])-bc[pos]);
}
 
int main(){
    scanf("%d %d",&m,&n);
    for (int i=0; i<m; i++) {
        scanf("%d",&a[i]);
    }
    std::sort(a,a+m,cmp);
    for (int i=1; i<=m; i++) {
        sm[i]=sm[i-1]+a[i-1];
    }
    for (int i=0; i<n; i++) {
        scanf("%d %d",&bv[i],&bc[i]);
    }
 //   memset(dp,-1,sizeof(dp));
    printf("%d",f(0,0));
}