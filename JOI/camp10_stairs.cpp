#include <cstdio>
#include <algorithm>
int n,t;
long long sum[500003],g;
long long sumdp[500003];
int piv;

int main(){
    scanf("%d %lld",&n,&g);
    for (int i=1; i<=n; i++){
        scanf("%d",&t);
        sum[i] = sum[i-1] + t;
    }
    sumdp[n+1] = 1;
    for (int i=n; i; i--) {
        long long *p = std::upper_bound(sum,sum+n+1,sum[i-1]+g);
        sumdp[i] = sumdp[i+1] + (sumdp[i+1]-sumdp[p-sum+1])%1234567;
    }
    printf("%lld",(sumdp[1]-sumdp[2])%1234567);
}