#include <cstdio>
#include <algorithm>
using namespace std;

const int sz = 250;

long long res[100005];

struct q{
    int s,e,num;
}qr[100005];
bool cmp(q a, q b){
    return a.s/sz == b.s/sz ? (a.e < b.e) : (a.s < b.s);
}

int n,q,a[100005];

int cnt[1000005];

void solve(){
    int s = 2, e = 1;
    long long r = 0;
    for (int i=0; i<q; i++) {
        while(s < qr[i].s){
            r -= 1ll * (2 * cnt[a[s]] - 1) * a[s];
            cnt[a[s]]--;
            s++;
        }
        while (s > qr[i].s) {
            s--;
            r += 1ll * (2 * cnt[a[s]] + 1) * a[s];
            cnt[a[s]]++;
        }
        while (e < qr[i].e) {
            e++;
            r += 1ll * (2 * cnt[a[e]] + 1) * a[e];
            cnt[a[e]]++;
        }
        while (e > qr[i].e) {
            r -= 1ll * (2 * cnt[a[e]] - 1) * a[e];
            cnt[a[e]]--;
            e--;
        }
        res[qr[i].num] = r;
    }
}

int main(){
    scanf("%d %d",&n,&q);
    for (int i=1; i<=n; i++) {
        scanf("%d",&a[i]);
    }
    for (int i=0; i<q; i++) {
        scanf("%d %d",&qr[i].s,&qr[i].e);
        qr[i].num = i;
    }
    sort(qr,qr+q,cmp);
    solve();
    for (int i=0; i<q; i++) {
        printf("%lld\n",res[i]);
    }
}