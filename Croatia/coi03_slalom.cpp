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
typedef pair<int, int> pi;
 
int n;
struct seg{int s, e, x;}seg[5005];
 
double dpl[5005], dpr[5005];
 
int ccw(pi a, pi b, pi c){
    int dx1 = b.first - a.first;
    int dy1 = b.second - a.second;
    int dx2 = c.first - a.first;
    int dy2 = c.second - a.second;
    return dx1 * dy2 >= dy1 * dx2;
}
 
double dist(pi a, pi b){
    return hypot(a.first - b.first, a.second - b.second);
}
 
int main(){
    cin >> n;
    cin >> seg[0].s >> seg[0].x;
    seg[0].e = seg[0].s;
    for(int i=1; i<=n; i++){
        cin >> seg[i].s >> seg[i].e >> seg[i].x;
    }
    cin >> seg[n+1].s >> seg[n+1].x;
    seg[n+1].e = seg[n+1].s;
    for(int i=1; i<=n+1; i++){
        pi angs(seg[i].s+1, seg[i].x), ange(seg[i].s-1, seg[i].x);
        pi st(seg[i].s, seg[i].x);
        dpl[i] = dpr[i] = 1e9;
        for(int j=i-1; j>=0; j--){
            pi ts(seg[j].e, seg[j].x);
            pi te(seg[j].s, seg[j].x);
            if(ccw(st, angs, ts) && ccw(st, ts, ange)){
                dpl[i] = min(dpl[i], dpr[j] + dist(ts, st));
            }
            if(ccw(st, angs, te) && ccw(st, te, ange)){
                dpl[i] = min(dpl[i], dpl[j] + dist(te, st));
            }
            if(ccw(st, angs, ts)){
                angs = ts;
            }
            if(!ccw(st, ange, te)){
                ange = te;
            }
        }
        angs = pi(seg[i].e+1, seg[i].x);
        ange = pi(seg[i].e-1, seg[i].x);
        pi ed(seg[i].e, seg[i].x);
        for(int j=i-1; j>=0; j--){
            pi ts(seg[j].e, seg[j].x);
            pi te(seg[j].s, seg[j].x);
            if(ccw(ed, angs, ts) && ccw(ed, ts, ange)){
                dpr[i] = min(dpr[i], dpr[j] + dist(ts, ed));
            }
            if(ccw(ed, angs, te) && ccw(ed, te, ange)){
                dpr[i] = min(dpr[i], dpl[j] + dist(te, ed));
            }
            if(ccw(ed, angs, ts)){
                angs = ts;
            }
            if(!ccw(ed, ange, te)){
                ange = te;
            }
        }
    }
    printf("%.4f",dpl[n+1]);
}