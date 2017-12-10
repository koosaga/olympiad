#include <cstdio>
#include <algorithm>
using namespace std;

long long sum(long long x){
    return x * (x+1) / 2;
}

int main(){
    long long n,k,r = 0;
    scanf("%lld %lld",&n,&k);
    r = n * k;
    for (int i=1; i<=100000; i++) {
        r -= 1ll * i * (sum(min(n,k/i)) - sum(min(n,k/(i+1))));
    }
    for (int i=1; i<=k/100001 && i<=n; i++) {
        r -= k/i * i;
    }
    printf("%lld",r);
}