#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
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

struct pnt{
    int x, y, dx;
};

int n;
vector<pnt> v;

int x0[2005], x1[2005], y[2005];

lint ccw(pnt a, pnt b){
    return 1ll * a.x * b.y - 1ll * b.x * a.y;
}

int solve(int px, int py){
    v.clear();
    for(int i=0; i<n; i++){
        if(y[i] < py){
            v.push_back({x1[i] - px, py - y[i], x1[i] - x0[i]});
            v.push_back({x0[i] - px, py - y[i], x0[i] - x1[i]});
        }
        if(y[i] > py){
            v.push_back({px - x0[i], y[i] - py, x1[i] - x0[i]});
            v.push_back({px - x1[i], y[i] - py, x0[i] - x1[i]});
        }
    }
    sort(v.begin(), v.end(), [&](const pnt &a, const pnt &b){
        lint tmp = ccw(a, b);
        if(tmp == 0) return a.dx > b.dx;
        return tmp > 0;
    });
    int ret = 0, cur = 0;
    for(int i=0; i<v.size(); i++){
        cur += v[i].dx;
        ret = max(ret, cur);
    }
    return ret;
}

int main(){
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> x0[i] >> x1[i] >> y[i];
        if(x0[i] > x1[i]){
            swap(x0[i], x1[i]);
        }
    }
    int ret = 0;
    for(int i=0; i<n; i++){
        ret = max(ret, solve(x0[i], y[i]) + x1[i] - x0[i]);
        ret = max(ret, solve(x1[i], y[i]) + x1[i] - x0[i]);
    }
    cout << ret;
}