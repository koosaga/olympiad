#include <cstdio>
#include <algorithm>
using namespace std;

struct ct{int a[30],k,n;}sum[100005];
int n,k,a[100005];

bool cmp(ct a, ct b){
    for (int i=0; i<a.k; i++) {
        if(a.a[i] != b.a[i]) return a.a[i] < b.a[i];
    }
    return a.n < b.n;
}

bool operator==(ct a, ct b){
    for (int i=0; i<a.k; i++) {
        if(a.a[i] != b.a[i]) return 0;
    }
    return 1;
}

int main(){
    scanf("%d %d",&n,&k);
    for (int i=1; i<=n; i++) {
        scanf("%d",&a[i]);
    }
    for (int i=0; i<=n; i++) {
        if(i == 0) sum[i].k = k;
        else{
            sum[i] = sum[i-1];
            for (int j=0; j<k; j++) {
                sum[i].a[j] += (a[i] >> j)&1;
            }
            sum[i].n = i;
        }
    }
    for (int i=1; i<=n; i++) {
        for (int j=1; j<k; j++) {
            sum[i].a[j] -= sum[i].a[0];
        }
        sum[i].a[0] = 0;
    }
    sort(sum,sum+n+1,cmp);
    int piv = 0, res = 0;
    for (int i=0; i<=n; ) {
        while(sum[i] == sum[piv] && piv <= n){
            piv++;
        }
        if(i == piv) piv++;
        res = max(res,sum[piv-1].n - sum[i].n);
        i = piv;
    }
    printf("%d",res);
}