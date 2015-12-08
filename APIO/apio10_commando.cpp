#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long lint;
 
struct cht{
    lint la[1000005], lb[1000005];
    int p, sz;
    void insert(lint a, lint b){
        la[sz] = a;
        lb[sz] = b;
        while(sz - 2 >= p && (lb[sz-1] - lb[sz]) * (la[sz-1] - la[sz-2]) < (lb[sz-2] - lb[sz-1]) * (la[sz] - la[sz-1])){
            la[sz-1] = la[sz];
            lb[sz-1] = lb[sz];
            sz--;
        }
        sz++;
    }
    lint query(lint x){
        while(p+1 < sz && (lb[p] - lb[p+1]) < (la[p+1] - la[p]) * x){
            p++;
        }
        return la[p] * x + lb[p];
    }
}hull;
 
int n,a,b,c;
lint d[1000005];
int main(){
    lint dp = 0;
    scanf("%d %d %d %d",&n,&a,&b,&c);
    for (int i=1; i<=n; i++) {
        scanf("%lld",&d[i]);
        d[i] += d[i-1];
    }
    hull.insert(0,0);
    for (int i=1; i<=n; i++) {
        dp = hull.query(d[i]) + 1ll * a * d[i] * d[i] + 1ll * b * d[i] + c;
        hull.insert(-2 * a * d[i], d[i] * d[i] * a - d[i] * b + dp);
    }
    printf("%lld",dp);
}