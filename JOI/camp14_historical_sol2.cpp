#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int sz = 450;

struct q{int s,e,n;}qr[100005];
bool cmp(q a, q b){return a.s / sz == b.s / sz ? (a.e < b.e) : (a.s < b.s);}

int a[100005],n,q;
vector<int> p;
long long res[100005];
int lim;

inline void add(int pos, int val, long long* tree){
    pos += lim;
    tree[pos] += 1ll * val * p[pos-lim];
    while(pos > 1){
        pos >>= 1;
        tree[pos] = max(tree[2*pos],tree[2*pos+1]);
    }
}

inline void solve(){
    long long tree[270000] = {};
    for(lim = 1; lim <= p.size(); lim <<= 1);
    int s = 1, e = 0;
    for (int i=0; i<q; i++) {
        while (s < qr[i].s) {
            add(a[s],-1,tree);
            s++;
        }
        while (qr[i].s < s) {
            s--;
            add(a[s],1,tree);
        }
        while (e < qr[i].e) {
            e++;
            add(a[e],1,tree);
        }
        while (qr[i].e < e) {
            add(a[e],-1,tree);
            e--;
        }
        res[qr[i].n] = tree[1];
    }
}

int main(){
    scanf("%d %d",&n,&q);
    for (int i=1; i<=n; i++) {
        scanf("%d",&a[i]);
        p.push_back(a[i]);
    }
    for (int i=0; i<q; i++) {
        scanf("%d %d",&qr[i].s,&qr[i].e);
        qr[i].n = i;
    }
    sort(qr,qr+q,cmp);
    sort(p.begin(),p.end());
    p.resize(unique(p.begin(),p.end()) - p.begin());
    for (int i=1; i<=n; i++) {
        a[i] = (int)(lower_bound(p.begin(),p.end(),a[i]) - p.begin());
    }
    solve();
    for (int i=0; i<q; i++) {
        printf("%lld\n",res[i]);
    }
}