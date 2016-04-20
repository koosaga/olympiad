#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
 
int a[2005], n;
long long dp[2005][2005];
 
long long f(int s, int e);
 
int MINUS(int x){
    return (x + n - 1) % n;
}
 
int PLUS(int x){
    return (x + 1) % n;
}
 
long long g(int s, int e){
    if(PLUS(e) == s) return 0;
    if(a[MINUS(s)] > a[PLUS(e)]) return f(MINUS(s),e);
    else return f(s,PLUS(e));
}
 
long long f(int s, int e){
    if(PLUS(e) == s) return 0;
    if(~dp[s][e]) return dp[s][e];
    return dp[s][e] = max(a[MINUS(s)] + g(MINUS(s),e), a[PLUS(e)] + g(s,PLUS(e)));
}
 
int main(){
    memset(dp,-1,sizeof(dp));
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
    }
    long long ret = 0;
    for (int i=0; i<n; i++) {
        ret = max(ret,a[i] + g(i,i));
    }
    printf("%lld",ret);
}