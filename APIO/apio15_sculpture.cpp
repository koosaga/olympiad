#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long lint;
 
int n,s,e;
lint a[2005];
 
char dp[101][101];
lint criteria;
 
int f(int pos, int grp){
    if(pos == 0) return grp <= e && grp >= s;
    if(~dp[pos][grp]) return dp[pos][grp];
    int t = 0;
    for(int j=pos-1; j>=0; j--){
        if(((~criteria) & (a[pos] - a[j])) == 0){
            t |= f(j,grp+1);
        }
    }
    return dp[pos][grp] = t;
}
 
int dp2[2001];
 
int f2(int x){
    if(x == 0) return 0;
    if(~dp2[x]) return dp2[x];
    int ret = 1e9;
    for(int j=x-1; j>=0; j--){
        if(((~criteria) & (a[x] - a[j])) == 0){
            ret = min(ret,f2(j) + 1);
        }
    }
    return dp2[x] = ret;
}
 
void solve2(){
    criteria = (1ll << 50) - 1;
    for(int i=49; i>=0; i--){
        criteria ^= (1ll<<i);
        memset(dp,-1,sizeof(dp));
        if(!f(n,0)){
            criteria ^= (1ll<<i);
        }
    }
    printf("%lld",criteria);
}
 
void solve3(){
    criteria = (1ll << 50) - 1;
    for(int i=49; i>=0; i--){
        criteria ^= (1ll<<i);
        memset(dp2,-1,sizeof(dp2));
        if(f2(n) > e){
            criteria ^= (1ll<<i);
        }      
    }
    printf("%lld",criteria);
}
 
int main(){
    scanf("%d %d %d",&n,&s,&e);
    for(int i=1; i<=n; i++){
        scanf("%lld",&a[i]);
        a[i] += a[i-1];
    }
    if(s != 1){
        solve2();
    }
    else{
        solve3();
    }
    puts("");
}