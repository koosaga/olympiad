#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, q;
pi a[100005], b[100005];

lint ccw(pi a, pi b, pi c){
    int dx1 = b.first - a.first;
    int dy1 = b.second - a.second;
    int dx2 = c.first - a.first;
    int dy2 = c.second - a.second;
    return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

double dist(pi a, pi b){
    return hypot(b.first - a.first, b.second - a.second);
}

pi move(pi s, pi e, int x){
    if(s.first < e.first) return pi(e.first - x, e.second);
    if(s.second < e.second) return pi(e.first, e.second - x);
    if(s.second > e.second) return pi(e.first, e.second + x);
    return pi(e.first + x, e.second);
}

int main(){
    int t;
    cin >> t;
    while(t--){
        double ret = 0;
        scanf("%d",&n);
        for(int i=0; i<n; i++){
            scanf("%d %d",&a[i].first, &a[i].second);
        }
        reverse(a+1, a+n);
        scanf("%d",&q);
        for(int i=0; i<q; i++){
            scanf("%d %d",&b[i].first, &b[i].second);
            b[i].first = n - b[i].first;
            if(b[i].first == n){
                ret += b[i].second;
                q--;
                i--;
            }
        }
        sort(b, b+q);
        int p = 0;
        vector<pi> hull;
        vector<double> dsum;
        for(int i=0; i<n-1; i++){
            while(hull.size() >= 2 && ccw(hull[hull.size()-2], hull.back(), a[i]) <= 0){
                hull.pop_back();
                dsum.pop_back();
            }
            double dst = 0;
            if(!dsum.empty()){
                dst += dsum.back();
                dst += dist(hull.back(), a[i]);
            }
            hull.push_back(a[i]);
            dsum.push_back(dst);
            while(p < q && b[p].first == i+1){
                b[p] = move(a[i], a[i+1], b[p].second);
                int s = 0, e = hull.size()-1;
                while(s != e){
                    int m = (s+e)/2;
                    if(ccw(hull[m], hull[m+1], b[p]) >= 0) s = m+1;
                    else e = m;
                }
                ret += dsum[s];
                ret += dist(hull[s], b[p]);
                p++;
            }
        }
        printf("%.10f\n",ret);
    }
}