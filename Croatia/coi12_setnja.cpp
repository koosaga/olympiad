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
 
int n, x[200005], y[200005], p[200005];
 
struct trap{
    int sx, ex, sy, ey;
}a[200005];
 
int collide(trap &a, trap &b){
    int ret = 0;
    if(max(a.sx, b.sx) > min(a.ex, b.ex)){
        ret = max(ret, max(b.sx - a.ex, a.sx - b.ex));
    }
    if(max(a.sy, b.sy) > min(a.ey, b.ey)){
        ret = max(ret, max(b.sy - a.ey, a.sy - b.ey));
    }
    return ret;
}
 
int main(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        int x, y, p;
        scanf("%d %d %d",&x,&y,&p);
        a[i] = {x-p, x+p, y-p, y+p};
    }
    trap cur = a[0];
    lint ret = 0;
    for(int i=1; i<n; i++){
        int cd = collide(cur, a[i]);
        cur.sx -= cd;
        cur.ex += cd;
        cur.sy -= cd;
        cur.ey += cd;
        cur.sx = max(cur.sx, a[i].sx);
        cur.ex = min(cur.ex, a[i].ex);
        cur.sy = max(cur.sy, a[i].sy);
        cur.ey = min(cur.ey, a[i].ey);
        ret += cd;
    }
    cout << ret;
}