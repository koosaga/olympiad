#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n;
pi a[100005];
vector<pi> cgrp;
int is[100005], ie[100005], sum[200005];

pi vec(int p, int q){
    p = (p + n) % n;
    q = (q + n) % n;
    return pi(a[q].first - a[p].first, a[q].second - a[p].second);
}

lint ccw(pi a, pi b, pi c){
    int dx1 = b.first - a.first;
    int dy1 = b.second - a.second;
    int dx2 = c.first - a.first;
    int dy2 = c.second - a.second;
    return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

bool isColinear(int st, int ed){
    return sum[ed - 1] - sum[st] == 0;
}

struct bit{
    int tree[200005];
    void clear(){ memset(tree, 0, sizeof(tree)); }
    void add(int x, int v){
        x++;
        while(x <= 2 * n){
            tree[x] += v;
            x += x & -x;
        }
    }
    int query(int x){
        int ret = 0;
        while(x){
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
    int query(int s, int e){
        return query(e+1) - query(s);
    }
}bit;

void solve(){
    scanf("%d",&n);
    for(int i=n-1; i>=0; i--){
        scanf("%d %d",&a[i].first,&a[i].second);
    }
    rotate(a, min_element(a, a+n), a+n);
    bool line = 1;
    for(int i=2; i<n; i++){
        if(ccw(a[0], a[1], a[i]) != 0) line = 0;
    }
    if(line){
        printf("%lld\n", 1ll * n * (n - 1) / 2);
        return;
    }
    a[n] = a[0];
    lint ans = 0;
    memset(sum,0, sizeof(sum));
    for(int i=0; i<n; i++){
        if(ccw(a[(i+n-1)%n], a[i], a[i+1]) != 0) sum[i]++, sum[i + n]++;
    }
    for(int i=1; i<2*n; i++) sum[i] += sum[i-1];
    for(int i=0; i<n; ){
        int e = i;
        while(e < n && ccw(a[i], a[i+1], a[e+1]) == 0) e++;
        if(ccw(pi(0, 0), vec(e, e+1), vec(i, i-1)) <= 0){
            ans += 1ll * (e - i) * (e - i + 1);
        }
        cgrp.push_back(pi(i, e));
        i = e;
    }
    bit.clear();
    vector<pi> evs, eve;
    for(int i=0; i<n; i++){
        int s = i, e = i+n-1;
        while(s != e){
            int m = (s+e+1)/2;
            if(!isColinear(m, i + n) && ccw(pi(0, 0), vec(i, i+1), vec(m-1, m)) >= 0) s = m;
            else e = m-1;
        }
        ie[i] = s; // [i+1 ~ s] matchable
        s = i + 1, e = i + n;
        while(s != e){
            int m = (s+e)/2; 
            if(!isColinear(i, m) && ccw(pi(0, 0), vec(i-1, i), vec(m+1, m)) >= 0) e = m;
            else s = m+1;
        }
        is[i] = s; // [s ~ i+n-1] matchable
        if(is[i] <= ie[i]){
            evs.push_back(pi(is[i], i));
            eve.push_back(pi(ie[i], i));
            bit.add(i, 1);
            bit.add(i + n, 1);
        }
    }
    sort(evs.begin(), evs.end());
    sort(eve.begin(), eve.end());
    int ps = 0, pe = 0;
    for(int i=0; i<2*n; i++){
        ans += max(0, ie[i%n] - is[i%n] + 1);
        while(ps < evs.size() && evs[ps].first == i){
            bit.add(evs[ps].second, -1);
            bit.add(evs[ps].second + n, -1);
            ps++;
        }
        if(is[i%n] <= ie[i%n]){
            if(is[i%n] < n && ie[i%n] >= n) ans -= bit.query(is[i%n], n-1) + bit.query(0, ie[i%n] - n);
            else ans -= bit.query(is[i%n] % n, ie[i%n] % n);
        }
        while(pe < eve.size() && eve[pe].first == i){
            bit.add(eve[pe].second, 1);
            bit.add(eve[pe].second + n, 1);
            pe++;
        }
    }
    assert(ans % 2 == 0);
    printf("%lld\n", ans / 2);
}

int main(){
    int tc;
    scanf("%d",&tc);
    while(tc--) solve();
}

