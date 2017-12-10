#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int gcd(int x, int y){
    return y ? gcd(y, x%y) : x;
}

lint ccw(pi a, pi b, pi c){
    int dx1 = b.first - a.first;
    int dy1 = b.second - a.second;
    int dx2 = c.first - a.first;
    int dy2 = c.second - a.second;
    return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

bool fcmp(pi a, pi b){
    return 1ll * a.first * b.second < 1ll * b.first * a.second;
}

int n;
pi a[100005];
int s[100005], e[100005];

int main(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d %d",&a[i].first, &a[i].second);
    }
    sort(a, a+n);
    for(int i=0; i<n; i++){
        s[i] = a[i].first;
        e[i+1] = a[i].second;
    }
    pi ret(2000000, 1);
    vector<pi> hull;
    for(int i=1; i<=n; i++){
        while(hull.size() >= 2 && ccw(hull[hull.size()-2], hull.back(), pi(i-1, s[i-1])) >= 0){
            hull.pop_back();
        }
        hull.push_back(pi(i-1, s[i-1]));
        int s = 0, e = hull.size() - 1;
        while(s != e){
            int m = (s+e)/2;
            if(ccw(hull[m], hull[m+1], pi(i, ::e[i])) >= 0) e = m;
            else s = m+1;
        }
        auto w = pi(::e[i] - hull[s].second, i - hull[s].first);
        if(fcmp(w, ret)) ret = w;
    }
    int g = gcd(ret.first, ret.second);
    ret.first /= g;
    ret.second /= g;
    printf("%d/%d\n", ret.first, ret.second);
}

