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

int n, k;
int x[100005], y[100005];
int minx, maxx, miny, maxy;

struct rect{
    int sx, ex, sy, ey;
};

bool cp[100005], cq[100005];

bool cover(rect p, rect q){
    for(int i=0; i<n; i++){
        if(p.sx <= x[i] && x[i] <= p.ex && p.sy <= y[i] && y[i] <= p.ey){
            cp[i] = 1;
        }
        else{
            cp[i] = 0;
        }
        if(q.sx <= x[i] && x[i] <= q.ex && q.sy <= y[i] && y[i] <= q.ey){
            cq[i] = 1;
        }
        else{
            cq[i] = 0;
        }
    }
    int cnt1 = 0, cnt2 = 0;
    for(int i=0; i<n; i++){
        if(!cp[i] && !cq[i]) return 0;
        if(cp[i] && !cq[i]) cnt1++;
        if(!cp[i] && cq[i]) cnt2++;
    }
    return cnt1 <= k && cnt2 <= k;
}

bool trial(int t){
    rect a1 = {minx, minx + t, miny, miny + t};
    rect a2 = {maxx - t, maxx, maxy - t, maxy};
    rect a3 = {maxx - t, maxx, miny, miny + t};
    rect a4 = {minx, minx + t, maxy - t, maxy};
    return cover(a1, a2) || cover(a3, a4);
}

void solve(){
    scanf("%d %d",&n,&k);
    for(int i=0; i<n; i++){
        int a, b;
        scanf("%d %d",&a,&b);
        x[i] = a + b;
        y[i] = a - b;
    }
    minx = *min_element(x, x+n);
    maxx = *max_element(x, x+n);
    miny = *min_element(y, y+n);
    maxy = *max_element(y, y+n);
    int s = 0, e = 1e7;
    while(s != e){
        int m = (s+e)/2;
        if(trial(m)) e = m;
        else s = m+1;
    }
    printf("%d\n",(s+1)/2);
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--) solve();
}