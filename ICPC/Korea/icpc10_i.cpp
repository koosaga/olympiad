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
typedef pair<lint, lint> pi;

int m, n;

int dmin[120005];
int x[50005], y[50005];

int getdist(int a, int b){
    return abs(x[a] - x[b]) + abs(y[a] - y[b]);
}

int proc(int sx, int ex, int sy, int ey, int dist){
    sx = max(sx, x[1] + y[1] - dist);
    ex = min(ex, x[1] + y[1] + dist);
    sy = max(sy, x[1] - y[1] - dist);
    ey = min(ey, x[1] - y[1] + dist);
    if(sx > ex || sy > ey) return 0;
    if(sx == ex){
        ey = min(ey, 2 * m - 2 - ex);
        sy = max(sy, -sx);
        ey = min(ey, sx);
        sy = max(sy, ex - 2 * m + 2);
        if(sy > ey) return 0;
        if(abs(sx)%2 != 0){
            ey++;
            sy++;
        }
        ey += 1000000;
        sy += 1000000;
        return ey / 2 - (sy - 1) / 2;
    }
    if(sy == ey){
        sx = max(sx, -sy);
        ex = min(ex, 2 * m - 2 - ey);
        sx = max(sx, sy);
        ex = min(ex, 2 * m - 2 + ey);
        if(sx > ex) return 0;
        if(abs(sy)%2 != 0){
            sx++;
            ex++;
        }
        sx += 1000000;
        ex += 1000000;
        return ex / 2 - (sx - 1) / 2;
    }
    while(1);
    return 0;
}

void solve(){
    scanf("%d %d",&m,&n);
    for(int i=0; i<n; i++){
        scanf("%d %d",&x[i],&y[i]);
    }
    memset(dmin, 0x3f, sizeof(dmin));
    for(int i=0; i<n; i++){
        dmin[getdist(0, i)] = min(dmin[getdist(0, i)], getdist(1, i));
    }
    for(int i=1; i<2*m; i++){
        dmin[i] = min(dmin[i], dmin[i-1]);
    }
    lint ret = 0;
    for(int i=1; i<2*m; i++){
        //printf("%d %d\n",i, dmin[i]);
        if(dmin[i] == 0) break;
        ret += proc(x[0] + y[0] - i, x[0] + y[0] + i, x[0] - y[0] - i, x[0] - y[0] - i, dmin[i] - 1);
        ret += proc(x[0] + y[0] - i, x[0] + y[0] + i, x[0] - y[0] + i, x[0] - y[0] + i, dmin[i] - 1);
        ret += proc(x[0] + y[0] - i, x[0] + y[0] - i, x[0] - y[0] - i + 1, x[0] - y[0] + i - 1, dmin[i] - 1);
        ret += proc(x[0] + y[0] + i, x[0] + y[0] + i, x[0] - y[0] - i + 1, x[0] - y[0] + i - 1, dmin[i] - 1);
    }
    printf("%lld\n",ret);
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        solve();
    }
}