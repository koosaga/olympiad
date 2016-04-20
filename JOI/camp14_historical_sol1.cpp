#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int B = 150;

int n,q;
int a[100005];
long long buck[701][701];

vector<int> v;
vector<int> show[100005];

inline int range_count(int p, int q, int o){
    return (int)(upper_bound(show[o].begin(),show[o].end(),q) - lower_bound(show[o].begin(),show[o].end(),p));
}

void query(){
    int p,q;
    scanf("%d %d",&p,&q);
    p--;
    q--;
    if(p/B == q/B){
        long long mv = 0;
        for (int i=p; i<=q; i++) {
            mv = max(mv,1ll * v[a[i]] * range_count(p,q,a[i]));
        }
        printf("%lld\n",mv);
        return;
    }
    else{
        long long mv = 0;
        int i;
        for (i=p; i%B != 0; i++) {
            mv = max(mv,1ll * v[a[i]] * range_count(p,q,a[i]));
        }
        mv = max(mv,buck[i/B][q/B]);
        for (int i=q/B*B+1; i<=q; i++) {
            mv = max(mv,1ll * v[a[i]] * range_count(p,q,a[i]));
        }
        printf("%lld\n",mv);
    }
}

int main(){
    scanf("%d %d",&n,&q);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
        v.push_back(a[i]);
    }
    sort(v.begin(),v.end());
    v.resize(unique(v.begin(),v.end()) - v.begin());
    for (int i=0; i<n; i++) {
        a[i] = (int)(lower_bound(v.begin(),v.end(),a[i]) - v.begin());
        show[a[i]].push_back(i);
    }
    // buck[i][j] = i * B ~ j * B
    for (int i=0; i<n; i+=B) {
        long long cnt[100005] = {};
        long long maxv = 0;
        for (int j=i; j<n; j++) {
            cnt[a[j]] += v[a[j]];
            maxv = max(maxv,cnt[a[j]]);
            if(j % B== 0){
                buck[i/B][j/B] = maxv;
            }
        }
    }
    while (q--) {
        query();
    }
}