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

lint dx[1000005];
lint ddx[1000005];

void strip(int s, int e){
    if(s < 0) swap(s, e);
    dx[abs(s)]++;
    dx[abs(e)+1]--;
}

void solve(int sx, int ex, int sy, int ey){
    if(sx <= 0 && 0 <= ex){
        solve(sx, -1, sy, ey);
        solve(1, ex, sy, ey);
        strip(sy, ey);
        return;
    }
    if(sy <= 0 && 0 <= ey){
        solve(sx, ex, sy, -1);
        solve(sx, ex, 1, ey);
        strip(sx, ex);
        return;
    }
    if(sx < 0 && ex < 0){
        sx = -sx;
        ex = -ex;
        swap(sx, ex);
    }
    if(sy < 0 && ey < 0){
        sy = -sy;
        ey = -ey;
        swap(sy, ey);
    }
    int tbuf = (max(sx, sy) - sx + 1) * (max(sx, sy) - sy + 1);
    if(max(sx, sy) <= min(ex, ey)){
        dx[max(sx, sy)] += tbuf;
        dx[min(ex, ey) + 1] -= tbuf;
        ddx[max(sx, sy) + 1] += 2;
        ddx[min(ex, ey) + 1] -= 2;
        dx[min(ex, ey) + 1] -= 2 * (min(ex, ey) - max(sx, sy));
    }
    int stp = max(max(sx, sy), min(ex, ey) + 1);
    if(stp <= max(ex, ey)){
        if(ex < ey){
            dx[stp] += ex - sx + 1;
            dx[max(ex, ey) + 1] -= ex - sx + 1;
        }
        else{
            dx[stp] += ey - sy + 1;
            dx[max(ex, ey) + 1] -= ey - sy + 1;
        }
    }
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        int sx, sy, ex, ey;
        scanf("%d %d %d %d",&sx,&sy,&ex,&ey);
        solve(sx, ex, sy, ey);
    }
    for(int i=1; i<=1000000; i++){
        ddx[i] += ddx[i-1];
        dx[i] += ddx[i];
    }
    for(int i=1; i<=1000000; i++){
        dx[i] += dx[i-1];
    }
    for(int i=1; i<=1000000; i++){
        dx[i] += dx[i-1];
    }
    int q;
    scanf("%d",&q);
    while(q--){
        int x;
        scanf("%d",&x);
        printf("%lld\n",dx[x]);
    }
}
