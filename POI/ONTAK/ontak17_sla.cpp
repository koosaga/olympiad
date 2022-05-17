#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
#define all(v) (v).begin(), (v).end()
#define sz(v) ((int)(v).size())
const int MAXN = 1000005;

lint ccw(pi a, pi b, pi c){
    int dx1 = b.first - a.first;
    int dy1 = b.second - a.second;
    int dx2 = c.first - a.first;
    int dy2 = c.second - a.second;
    return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

int n;
pi a[MAXN][2];

int main(){
    scanf("%d",&n);
    scanf("%d %d %d %d",&a[0][0].first,&a[0][0].second,&a[n+1][0].first,&a[n+1][0].second);
    a[0][1] = a[0][0];
    a[n+1][1] = a[n+1][0];
    for(int i = 1; i <= n; i++){
        int s, e, x;
        scanf("%d %d %d",&s,&e,&x);
        a[i][0] = pi(s, x);
        a[i][1] = pi(e, x);
    }
    n += 2;
    vector<pi> path = {a[0][0]};
    deque<pi> lh = {a[0][0]};
    deque<pi> rh = {a[0][0]};
    for(int i = 1; i < n; i++){
        while(sz(rh) >= 2 && ccw(path.back(), rh[1], a[i][0]) > 0){
            rh.pop_front();
            path.push_back(rh[0]);
            while(sz(lh) && lh[0].second >= path.back().second) lh.pop_front();
            while(sz(lh) >= 2 && ccw(path.back(), lh[0], lh[1]) >= 0) lh.pop_front();
            lh.push_front(path.back());
        }
        while(sz(lh) >= 2 && ccw(path.back(), a[i][1], lh[1]) > 0){
            lh.pop_front();
            path.push_back(lh[0]);
            while(sz(rh) && rh[0].second >= path.back().second) rh.pop_front();
            while(sz(rh) >= 2 && ccw(path.back(), rh[0], rh[1]) <= 0) rh.pop_front();
            rh.push_front(path.back());
        }
        while(sz(lh) >= 2 && ccw(lh[sz(lh) - 2], lh.back(), a[i][0]) >= 0) lh.pop_back();
        while(sz(rh) >= 2 && ccw(rh[sz(rh) - 2], rh.back(), a[i][1]) <= 0) rh.pop_back();
        lh.push_back(a[i][0]);
        rh.push_back(a[i][1]);
    }
    assert(sz(lh) <= 2 || sz(rh) <= 2);
    if(sz(lh) >= sz(rh)){
        lh.pop_front();
        for(auto &x : lh) path.push_back(x);
    }
    else{
        rh.pop_front();
        for(auto &x : rh) path.push_back(x);
    }
    printf("%d\n", sz(path));
    for(auto &[x, y] : path) printf("%d %d\n", x, y);
}

