#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 50005;
const double eps = 1e-8;
typedef pair<long double, long double> pi;

long double ccw(pi a, pi b, pi c){
    long double dx1 = b.first - a.first;
    long double dy1 = b.second - a.second;
    long double dx2 = c.first - a.first;
    long double dy2 = c.second - a.second;
    return dx1 * dy2 - dy1 * dx2;
}

namespace hpi{
    bool z(long double x){ return fabs(x) < eps; }
    struct line{
        long double a, b, c;
        bool operator<(const line &l)const{
            bool flag1 = pi(a, b) > pi(0, 0);
            bool flag2 = pi(l.a, l.b) > pi(0, 0);
            if(flag1 != flag2) return flag1 > flag2;
            long double t = ccw(pi(0, 0), pi(a, b), pi(l.a, l.b));
            return z(t) ? c * hypot(l.a, l.b) < l.c * hypot(a, b) : t > 0;
        }
        pi slope(){ return pi(a, b);}
    }; 
    pi cross(line a, line b){
        long double det = a.a * b.b - b.a * a.b;
        return pi((a.c * b.b - a.b * b.c) / det, (a.a * b.c - a.c * b.a) / det);
    }
    bool bad(line a, line b, line c){
        if(ccw(pi(0, 0), a.slope(), b.slope()) <= 0) return false;
        pi crs = cross(a, b);
        return crs.first * c.a + crs.second * c.b >= c.c;
    }
    bool solve(vector<line> v, vector<pi> &solution){ // ax + by <= c;
        sort(v.begin(), v.end());
        deque<line> dq;
        for(auto &i : v){
            if(!dq.empty() && z(ccw(pi(0, 0), dq.back().slope(), i.slope()))) continue;
            while(dq.size() >= 2 && bad(dq[dq.size()-2], dq.back(), i)) dq.pop_back();
            while(dq.size() >= 2 && bad(i, dq[0], dq[1])) dq.pop_front();
            dq.push_back(i);
        }
        while(dq.size() > 2 && bad(dq[dq.size()-2], dq.back(), dq[0])) dq.pop_back();
        while(dq.size() > 2 && bad(dq.back(), dq[0], dq[1])) dq.pop_front();
        vector<pi> tmp;
        for(int i=0; i<dq.size(); i++){
            line cur = dq[i], nxt = dq[(i+1)%dq.size()];
            if(ccw(pi(0, 0), cur.slope(), nxt.slope()) <= eps) return false;
            tmp.push_back(cross(cur, nxt));
        }
        solution = tmp;
        return true;
    }
};

int n;
pair<int, int> a[MAXN];

bool trial(int x){
    if(x >= (n+1)/2) return false;
    vector<hpi::line> v;
    vector<pi> w;
    for(int i=0; i<n; i++){
        hpi::line l;
        l.a = a[(i+x)%n].second - a[i].second;
        l.b = a[i].first - a[(i+x)%n].first;
        l.c = l.a * a[i].first + l.b * a[i].second;
        v.push_back(l);
    }
    return hpi::solve(v, w);
}

int main(){
    cin >> n;
    for(int i=0; i<n; i++){
        scanf("%d %d",&a[i].first, &a[i].second);
    }
    reverse(a, a+n);
    a[n] = a[0];
    int s = 1, e = n;
    while(s != e){
        int m = (s+e+1)/2;
        if(trial(m)) s = m;
        else e = m-1;
    }
    cout << s << endl;
}

