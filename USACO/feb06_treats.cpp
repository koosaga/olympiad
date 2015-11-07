#include <cstdio>
#include <algorithm>
using namespace std;

int a[2005],n,r,dp[2005][2005];

int f(int s, int e, int x){
    if(s == e) return x*a[s];
    if(dp[s][e]) return dp[s][e];
    return dp[s][e] = max(f(s+1,e,x+1) + x*a[s], f(s,e-1,x+1) + x*a[e]);
}
int main(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d",&a[i]);
    }
    printf("%d",f(0,n-1,1));
}