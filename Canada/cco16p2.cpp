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

int n;
struct pnt{
    int x, y, w;
}a[8005], b[8005];
int ps[8005];

lint ccw(pnt a, pnt b){
    return 1ll * a.x * b.y - 1ll * b.x * a.y;
}

lint hypot(pnt a){
    return 1ll * a.x * a.x + 1ll * a.y * a.y;
}

int solve(int x){
    int sum = 0, ret = -1e9, pt = 0;
    for(int i=0; i<n; i++){
        sum += a[i].w;
        if(i == x) continue;
        b[pt] = a[i];
        b[pt].x -= a[x].x;
        b[pt].y -= a[x].y;
        pt++;
    }
    sort(b, b+n-1, [&](const pnt &p, const pnt &q){
        if(p.x == q.x && p.y == q.y) return false;
        if(p.y == 0 && p.x > 0 && q.y == 0 && q.x > 0) return hypot(p) < hypot(q);
        if(p.y == 0 && p.x > 0) return true;
        if(q.y == 0 && q.x > 0) return false;
        if(p.y == 0 && q.y == 0) return hypot(p) < hypot(q);
        if(1ll * p.y * q.y <= 0) return p.y > q.y;
        lint tmp = ccw(p, q);
        if(tmp == 0) return hypot(p) < hypot(q);
        return tmp > 0;
    });
    for(int i=n-1; i<2*n-2; i++){
        b[i] = b[i-n+1];
    }
    ps[0] = b[0].w;
    for(int i=1; i<2*n-2; i++){
        ps[i] = ps[i-1] + b[i].w;
    }
    auto func = [&](int i, int j){
        if(ccw(b[i], b[j]) > 0 || (ccw(b[i], b[j]) == 0 && hypot(b[i]) < hypot(b[j]))) return 1;
        return 0;
    };
    int endp = 0;
    for(int i=0; i<n-1; i++){
        endp = max(endp, i+1);
        while(endp < i + n - 1 && func(i, endp)) endp++;
        int tmp = sum - (ps[endp-1] - ps[i]);
        ret = max(ret, tmp);
        ret = max(ret, sum - tmp);
        ret = max(ret, -b[i].w + tmp);
        ret = max(ret, sum + b[i].w - tmp);
        if(i == 0 || ccw(b[i-1], b[i]) != 0){
            ret = max(ret, -b[i].w - a[x].w + tmp);
            ret = max(ret, sum + b[i].w + a[x].w - tmp);
        }
    }
    return ret;
}

int main(){
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> a[i].x >> a[i].y >> a[i].w;
    }
    int ret = -1e9;
    for(int i=0; i<n; i++){
        ret = max(ret, solve(i));
    }
    cout << ret;
}