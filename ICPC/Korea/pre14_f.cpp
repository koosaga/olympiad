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

struct line{
    int sx, ex, sy, ey;
}a[4], t;

int ccw(pi a, pi b, pi c){
    int dx1 = b.first - a.first;
    int dy1 = b.second - a.second;
    int dx2 = c.first - a.first;
    int dy2 = c.second - a.second;
    if(dx1 * dy2 > dy1 * dx2) return 1;
    if(dx1 * dy2 == dy1 * dx2) return 0;
    return -1;
}

bool colinear(line a, line b){
    pi p1(a.sx, a.sy);
    pi p2(a.ex, a.ey);
    pi p3(b.sx, b.sy);
    pi p4(b.ex, b.ey);
    if(a.sx > a.ex) swap(a.sx, a.ex);
    if(a.sy > a.ey) swap(a.sy, a.ey);
    if(b.sx > b.ex) swap(b.sx, b.ex);
    if(b.sy > b.ey) swap(b.sy, b.ey);
    if(0 == ccw(p1, p2, p4) && ccw(p1, p2, p3) == 0){
        return max(a.sy, b.sy) <= min(a.ey, b.ey) && max(a.sx, b.sx) <= min(a.ex, b.ex);
    }
    return 0;
}

bool cross(line a, line b){
    pi p1(a.sx, a.sy);
    pi p2(a.ex, a.ey);
    pi p3(b.sx, b.sy);
    pi p4(b.ex, b.ey);
    if(ccw(p1, p2, p3) == ccw(p1, p2, p4)){
        if(ccw(p1, p2, p3) == 0){
            return colinear(a, b);
        }
        return 0;
    }
    if(ccw(p3, p4, p1) == ccw(p3, p4, p2)){
        if(ccw(p3, p4, p1) == 0){
            return colinear(a, b);
        }
        return 0;
    }
    return 1;
}

bool cross_infinity(line a, line b){
    pi p1(a.sx, a.sy);
    pi p2(a.ex, a.ey);
    pi p3(b.sx, b.sy);
    pi p4(b.ex, b.ey);
    if(a.sx > a.ex) swap(a.sx, a.ex);
    if(a.sy > a.ey) swap(a.sy, a.ey);
    if(b.sx > b.ex) swap(b.sx, b.ex);
    if(b.sy > b.ey) swap(b.sy, b.ey);
    if(0 == ccw(p1, p2, p4) && ccw(p1, p2, p3) == 0){
        return max(a.sy, b.sy) < min(a.ey, b.ey) || max(a.sx, b.sx) < min(a.ex, b.ex);
    }
    return 0;
}

bool inside_line(line a, pi b){
    int minx = min(a.sx, a.ex), miny = min(a.sy, a.ey);
    int maxx = max(a.sx, a.ex), maxy = max(a.sy, a.ey);
    return ccw(pi(a.sx, a.sy), b, pi(a.ex, a.ey)) == 0 && minx <= b.first && b.first <= maxx && miny <= b.second && b.second <= maxy;
}

bool cross_endpoint(line a, line b){
    return inside_line(b, pi(a.sx, a.sy)) || inside_line(b, pi(a.ex, a.ey));
}

int main(){
    int tc;
    scanf("%d",&tc);
    while(tc--){
        int n, m;
        int x1, y1, x2, y2;
        scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
        scanf("%d %d %d %d",&t.sx,&t.sy,&t.ex,&t.ey);
        a[0] = {x1, x2, y1, y1};
        a[1] = {x1, x2, y2, y2};
        a[2] = {x1, x1, y1, y2};
        a[3] = {x2, x2, y1, y2};
        int epc = 0, ccc = 0, inf = 0;
        for(int i=0; i<4; i++){
            if(cross_endpoint(a[i], t)) epc++;
            if(cross_infinity(a[i], t)) inf++;
            if(cross(a[i], t)) ccc++;
        }
        if(inf) puts("4");
        else if(epc) printf("%d\n",ccc - epc / 2);
        else printf("%d\n",ccc);
    }
}