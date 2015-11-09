#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<double, double> pi;
 
int n;
pi a[100005];
vector<pi> hull;
vector<pi> low, high;
 
int ccw(pi a, pi b, pi c){
    double dx1 = b.first - a.first;
    double dy1 = b.second - a.second;
    double dx2 = c.first - a.first;
    double dy2 = c.second - a.second;
    double cmp = dx1 * dy2 - dy1 * dx2;
    if(cmp == 0) return 0;
    return cmp > 0 ? 1 : -1;
}
 
int main(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%lf %lf",&a[i].first, &a[i].second);
    }
    if(n == 0){
        pi st, ed;
        while(~scanf("%lf %lf %lf %lf",&st.first, &st.second, &ed.first, &ed.second)){
            puts("GOOD");
        }
        return 0;
    }
    swap(a[0], *min_element(a, a+n));
    sort(a+1, a+n, [&](const pi &p, const pi &q){
        int t = ccw(a[0], p, q);
        if(t != 0) return t > 0;
        return p.first < q.first;
    });
    for(int i=0; i<n; i++){
        while(hull.size() >= 2 && ccw(hull[hull.size() - 2], hull.back(), a[i]) <= 0){
            hull.pop_back();
        }
        hull.push_back(a[i]);
    }
    double xmax = max_element(a, a+n)->first;
    bool flag = 0;
    for(auto &i : hull){
        if(!flag) low.push_back(i);
        if(i.first == xmax) flag = 1;
        if(flag) high.push_back(i);
    }
    high.push_back(hull[0]);
    pi st, ed;
    while(~scanf("%lf %lf %lf %lf",&st.first, &st.second, &ed.first, &ed.second)){
        if(st > ed) swap(st, ed);
        auto func = [&](pi x){
            double a = st.second - ed.second;
            double b = ed.first - st.first;
            return a * x.first + b * x.second;
        };
        double base = func(st);
        int s = 0, e = low.size() - 1;
        while(s != e){
            int m = (s+e)/2;
            if(func(low[m]) <= func(low[m+1])) e = m;
            else s = m+1;
        }
        if(base < func(low[s])){
            puts("GOOD");
            continue;
        }
        s = 0, e = high.size() - 1;
        while(s != e){
            int m = (s+e)/2;
            if(func(high[m]) <= func(high[m+1])) s = m+1;
            else e = m;
        }
        if(base > func(high[s])){
            puts("GOOD");
            continue;
        }
        puts("BAD");
    }
}