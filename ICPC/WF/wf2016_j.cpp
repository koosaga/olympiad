#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

lint ccw(pi a, pi b, pi c){
    int dx1 = b.first - a.first;
    int dy1 = b.second - a.second;
    int dx2 = c.first - a.first;
    int dy2 = c.second - a.second;
    return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

bool in(pi a, pi b, pi c){
    if(ccw(a, b, c) != 0) return false;
    if(a.first > b.first) swap(a.first, b.first);
    if(a.second > b.second) swap(a.second, b.second);
    return a.first <= c.first && c.first <= b.first &&
        a.second <= c.second && c.second <= b.second;
}

// by zigui
// C : counter_clockwise(C[0] == C[N]), N >= 2
// return highest point in C <- P(clockwise) or -1 if strictly in convex
// recommend : strongly convex, C[i] != P

int convex_tangent(vector<pi> &C, pi P, int up = 1){
    auto sign = [&](lint c){ return c > 0 ? up : c == 0 ? 0 : -up; };
    auto local = [&](pi P, pi a, pi b, pi c) { 
        return sign(ccw(P, a, b)) <= 0 && sign(ccw(P, b, c)) >= 0;
    };
    assert(C.size() >= 2);
    int N = C.size()-1, s = 0, e = N, m;
    if( local(P, C[1], C[0], C[N-1]) ) return 0;
    while(s+1 < e){
        m = (s+e) / 2;
        if( local(P, C[m-1], C[m], C[m+1]) ) return m;
        if( sign(ccw(P, C[s], C[s+1])) < 0){ // up
            if( sign(ccw(P, C[m], C[m+1])) > 0) e = m;
            else if( sign(ccw(P, C[m], C[s])) > 0) s = m;
            else e = m;
        }
        else{ // down
            if( sign(ccw(P, C[m], C[m+1])) < 0) s = m;
            else if( sign(ccw(P, C[m], C[s])) < 0) s = m;
            else e = m;
        }
    }
    if( s && local(P, C[s-1], C[s], C[s+1]) ) return s;
    if( e != N && local(P, C[e-1], C[e], C[e+1]) ) return e;
    return -1;
}

vector<pi> cvx1, cvx2;

pi query(pi v){
    int n = cvx1.size() - 1;
    int l = convex_tangent(cvx1, v);
    int r = n - convex_tangent(cvx2, pi(v.second, v.first));
    if(l == -1) return pi(-1, -1);
    l %= n;
    r %= n;
    return pi(l, r);
}

lint dist(pi a, pi b){
    int dx = b.first - a.first;
    int dy = b.second - a.second;
    return 1ll * dx * dx + 1ll * dy * dy;
}

vector<pi> get_cvx(vector<pi> &v){
    swap(v[0], *min_element(v.begin(), v.end()));
    sort(v.begin() + 1, v.end(), [&](const pi &a, const pi &b){
        lint k = ccw(v[0], a, b);
        if(k != 0) return k > 0;
        return dist(v[0], a) < dist(v[0], b);
    });
    vector<pi> ch;
    for(auto &i : v){
        while(ch.size() >= 2 && ccw(ch[ch.size()-2], ch.back(), i) <= 0) ch.pop_back();
        ch.push_back(i);
    }
    return ch;
}

const int MAXN = 1000005;

int n, dx[MAXN];
vector<pi> v[2];

int main(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        int x, y, z;
        scanf("%d %d %d",&x,&y,&z);
        v[z^1].push_back(pi(x, y));
    }
    int base = v[0].size();
    if(base == 1){
        puts("1");
        return 0;
    }
    sort(v[0].begin(), v[0].end());
    v[0].resize(unique(v[0].begin(), v[0].end()) - v[0].begin());
    cvx1 = get_cvx(v[0]);
    if(cvx1.size() == 1){
        for(auto &i : v[1]) if(cvx1[0] == i) base++;
        cout << base << endl;
        return 0;
    }
    if(cvx1.size() == 2){
        vector<pi> ni;
        for(auto &i : v[1]){
            if(in(cvx1[0], cvx1[1], i)){
                base++;
            }
            else ni.push_back(i);
        }
        v[1] = ni;
    }
    cvx1.push_back(cvx1[0]);
    cvx2 = cvx1;
    reverse(cvx2.begin(), cvx2.end());
    for(auto &i : cvx2) swap(i.first, i.second);
    sort(v[0].begin(), v[0].end());
    vector<pair<pi, pi>> intv;
    vector<pi> cnd;
    for(auto &i : v[1]){
        auto k = query(i);
        if(k == pi(-1, -1) || binary_search(v[0].begin(), v[0].end(), i) || in(cvx1[k.first], cvx1[k.second], i)) base++;
        else{
            pi l1 = pi(cvx1[k.first].first - i.first, cvx1[k.first].second - i.second);
            pi l2 = pi(cvx1[k.second].first - i.first, cvx1[k.second].second - i.second);
            if(l1 < pi(0, 0)) l1.first *= -1, l1.second *= -1;
            if(l2 < pi(0, 0)) l2.first *= -1, l2.second *= -1;
            cnd.push_back(l1);
            cnd.push_back(l2);
            intv.emplace_back(l1, l2);
        }
    }
    cnd.push_back(pi(0, 1));
    auto acmp = [&](const pi &a, const pi &b){
        return ccw(pi(0, 0), a, b) > 0;
    };
    sort(cnd.begin(), cnd.end(), acmp);
    cnd.resize(unique(cnd.begin(), cnd.end(), [&](const pi &a, const pi &b){
        return ccw(pi(0, 0), a, b) == 0;
    }) - cnd.begin());
    for(auto &i : intv){
        int l = lower_bound(cnd.begin(), cnd.end(), i.first, acmp) - cnd.begin() + 1;
        int r = lower_bound(cnd.begin(), cnd.end(), i.second, acmp) - cnd.begin() + 1;
        if(l <= r){
            dx[2*l]++;
            dx[2*r+1]--;
        }
        else{
            dx[0]++;
            dx[2*r+1]--;
            dx[2*l]++;
        }
    }
    int ans = 1e9;
    for(int i=0; i<=2*cnd.size(); i++){
        if(i) dx[i] += dx[i-1];
        ans = min(ans, dx[i]);
    }
    cout << ans + base << endl;
}

