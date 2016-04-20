#include <cstdio>
#include <algorithm>
using namespace std;
 
long long a[100005], b[100005], c[100005];
int n,m,iti[100005];
 
long long dx[100005];
 
int main(){
    scanf("%d %d",&n,&m);
    for (int i=0; i<m; i++) {
        scanf("%d",&iti[i]);
    }
    for (int i=1; i<n; i++) {
        scanf("%lld %lld %lld",&a[i],&b[i],&c[i]);
    }
    for (int i=0; i<m-1; i++) {
        int ps = min(iti[i],iti[i+1]);
        int pe = max(iti[i],iti[i+1]);
        dx[ps]++;
        dx[pe]--;
    }
    for (int i=1; i<=n; i++) {
        dx[i] += dx[i-1];
    }
    long long ret = 0;
    for (int i=1; i<=n; i++) {
        ret += min(a[i] * dx[i], c[i] + b[i] * dx[i]);
    }
    printf("%lld",ret);
}