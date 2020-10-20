// shirley smokes weed
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;

lint ccw(pi a, pi b, pi c){
    int dx1 = b.first - a.first;
    int dy1 = b.second - a.second;
    int dx2 = c.first - a.first;
    int dy2 = c.second - a.second;
    return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

pi p;

bool in_seg(pi l, pi r, pi x){
    return ccw(p, l, x) >= 0 && ccw(p, x, r) >= 0;
}

int solve(pi l, pi r, vector<pair<pi, pi>> segs){
    vector<pi> up, dn;
    for(auto &[x, y] : segs){
        bool good = 0;
        if(in_seg(l, r, x) || in_seg(l, r, y)) good = 1; // obvious witness
        if(in_seg(x, y, l) && in_seg(x, y, r)) good = 1;
        if(good){
            if(ccw(p, x, l) > 0) x = l;
            if(ccw(p, r, y) > 0) y = r;
            up.push_back(x);
            dn.push_back(y);
        }
    }
    sort(all(up), [&](const pi &x, const pi &y){
        return ccw(p, x, y) > 0;
    });
    sort(all(dn), [&](const pi &x, const pi &y){
        return ccw(p, x, y) > 0;
    });
    pi w = pi(r.first - l.first, r.second - l.second);
    if(w.first) w.first /= abs(w.first);
    if(w.second) w.second /= abs(w.second);
    int p1 = 0, p2 = 0, ret = 0;
    while(l != r){
        while(p1 < sz(up) && ccw(p, up[p1], l) >= 0) p1++;
        while(p2 < sz(dn) && ccw(p, dn[p2], l) > 0) p2++;
        if(p1 == p2) ret++;
        l.first += w.first;
        l.second += w.second;
    }
    return ret;
}

int main(){
    int n, r;
    scanf("%d %d",&n,&r);
    scanf("%d %d",&p.first,&p.second);
    vector<pair<pi, pi>> v;
    while(r--){
        int n; scanf("%d",&n);
        vector<pi> a(n);
        for(auto &[x, y] : a) scanf("%d %d",&x,&y);
        for(int j=0; j<n; j++){
            pi x = a[j];
            pi y = a[(j+1)%n];
            if(ccw(p, x, y) < 0) swap(x, y);
            v.push_back({x, y});
        }
    }
    int ans = 
    solve(pi(0, 0), pi(n, 0), v) +
    solve(pi(n, 0), pi(n, n), v) + 
    solve(pi(n, n), pi(0, n), v) +
    solve(pi(0, n), pi(0, 0), v);
    cout << ans << endl;
}
