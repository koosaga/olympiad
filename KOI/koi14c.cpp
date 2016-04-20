#include <cstdio>
#include <algorithm>
#include <cstdlib>
typedef long long lint;
using namespace std;

struct cht{
    int s,e;
    lint la[1000005], lb[1000005];
    double cross(int p, int q){
        return (double)(lb[q] - lb[p])/(la[p] - la[q]);
    }
    void insert(lint p, lint q){
        la[e] = p;
        lb[e] = q;
        while(s+1 < e && (lb[e-2] - lb[e-1]) * (la[e] - la[e-1]) >= (lb[e-1] - lb[e]) * (la[e-1] - la[e-2]) ){
            la[e-1] = la[e];
            lb[e-1] = lb[e];
            e--;
        }
        e++;
    }
    lint query(lint x){
        while(s+1 < e && (lb[s+1] - lb[s]) >= x * (la[s] - la[s+1])) s++;
        return la[s] * x + lb[s];
    }
}hull1, hull2;
int n,x;

int main(){
    int t;
    lint a[1000005],dp = 0;
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d",&t);
        if(t) a[++x] = i+1;
    }
    hull1.insert(0,0);
    hull2.insert(0,0);
    for (int i=1; i<=x; i++) {
        lint res1, res2;
        res1 = -hull1.query(a[i]) + a[i] * (i+1);
        res2 = -hull2.query(i) + (n+1LL)*i;
        dp = min(res1,res2);
        hull1.insert(i,-dp);
        hull2.insert(a[i+1],-dp -(a[i+1]-n-1)*(i-1));
    }
    printf("%lld",dp);
}