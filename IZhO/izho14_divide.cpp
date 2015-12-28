#include <cstdio>
#include <algorithm>
using namespace std;
 
int n;
long long x[100005], g[100005], d[100005], p[100005];
 
int main(){
    scanf("%d",&n);
    for (int i=1; i<=n; i++) {
        scanf("%lld %lld %lld",&x[i],&g[i],&d[i]);
        d[i] += d[i-1];
        g[i] += g[i-1];
        p[i] = d[i] - x[i];
    }
    for (int i=n-1; i; i--) {
        p[i] = max(p[i],p[i+1]);
    }
    long long r = 0;
    for (int i=1; i<=n; i++) {
        int s = i, e = n;
        while (s != e) {
            int m = (s+e+1)/2;
            if(d[i-1] - x[i] <= p[m]) s = m;
            else e = m-1;
        }
        if(d[i-1] - x[i] <= p[s]){
            r = max(r,g[s] - g[i-1]);
        }
    }
    printf("%lld",r);
}