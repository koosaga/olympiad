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
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int offset = 200002;
 
int n, m;
pi a[600005];
 
lint ccw(pi a, pi b, pi c){
    int dx1 = b.first - a.first;
    int dy1 = b.second - a.second;
    int dx2 = c.first - a.first;
    int dy2 = c.second - a.second;
    return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}
 
lint dist(pi a, pi b){
    return 1ll * (b.first - a.first) * (b.first - a.first) + 1ll * (b.second - a.second) * (b.second - a.second);
}
 
vector<pi> h1, h2;
 
void get_hull(){
    pi b[300005];
    scanf("%d",&m);
    for(int i=0; i<m; i++){
        scanf("%d %d",&b[i].first, &b[i].second);
    }
    sort(b, b+m);
    for(int i=0; i<m; i++){
        while(h1.size() >= 2 && ccw(h1[h1.size()-2], h1.back(), b[i]) >= 0){
            h1.pop_back();
        }
        while(h2.size() >= 2 && ccw(h2[h2.size()-2], h2.back(), b[i]) <= 0){
            h2.pop_back();
        }
        h1.push_back(b[i]);
        h2.push_back(b[i]);
    }
}
 
bool has_ccwr(pi s, pi e){ 
    if(s == e) return 0; 
    if(s.first == e.first){
        if(ccw(s, e, h1.front()) <= 0) return 1;
        if(ccw(s, e, h1.back()) <= 0) return 1;
        return 0;
    }
    if(s.first < e.first){
        int st = 0, ed = h2.size() - 1;
        while(st != ed){
            int m = (st + ed) / 2;
            lint t1 = ccw(s, e, h2[m]);
            lint t2 = ccw(s, e, h2[m+1]);
            if(t1 <= t2){
                ed = m;
            }
            else st = m+1;
        }
        return ccw(s, e, h2[st]) <= 0;
    }
    else{
        int st = 0, ed = h1.size() - 1;
        while(st != ed){
            int m = (st + ed) / 2;
            lint t1 = ccw(s, e, h1[m]);
            lint t2 = ccw(s, e, h1[m+1]);
            if(t1 <= t2){
                ed = m;
            }
            else st = m+1;
        }
        return ccw(s, e, h1[st]) <= 0;
    }
}
 
int rmax[300005];
 
int main(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d %d",&a[i].first, &a[i].second);
        a[n+i] = a[i];
    }
    get_hull();
    int p = 0;
    for(int i=0; i<n; i++){
        while(!has_ccwr(a[i], a[p])) p++;
        rmax[i] = p - 1;
    }
    int ccap = 0;
    lint ret = 0, cur = 0;
    for(int i=0; i<n; i++){
        while(ccap < rmax[i]){
            cur += ccw(a[i], a[ccap], a[ccap+1]);
            ccap++;
        }
        ret = max(ret, cur);
        cur -= ccw(a[i], a[i+1], a[ccap]);
    }
    printf("%lld",ret);
    // make convex hull
}