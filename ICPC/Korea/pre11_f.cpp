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

int m, n, sx, sy, ex, ey;
vector<pi> v;

inline void print(){
    puts("1");
    for(auto &i : v) printf("%d %d\n",i.first + 1, i.second + 1);
}

bool case1(){
    if(sy == ey){
        if(sy != 0 && sy != m-1) return 0;
        if(sy == 0){
            for(int i=0; i<m; i++) v.push_back(pi(sx, i));
            for(int i=m-1; i>=0; i--) v.push_back(pi(sx^1, i));
        }
        if(sy == m-1){
            for(int i=m-1; i>=0; i--) v.push_back(pi(sx, i));
            for(int i=0; i<m; i++) v.push_back(pi(sx^1, i));
        }
        return 1;
    }
    int swp = 0;
    if(sy > ey){
        swap(sx, ex);
        swap(sy, ey);
        swp = 1;
    }
    for(int i=sy; i>=0; i--) v.push_back(pi(sx, i));
    for(int i=0; i<=sy; i++) v.push_back(pi(sx^1, i));
    int p = sx^1;
    for(int i=sy+1; i<ey; i++){
        v.push_back(pi(p, i));
        v.push_back(pi(p^1, i));
        p ^= 1;
    }
    for(int i=ey; i<m; i++) v.push_back(pi(p, i));
    for(int i=m-1; i>=ey; i--) v.push_back(pi(p^1, i));
    if(swp) reverse(v.begin(), v.end());
    return 1;
}

void route(int n, int m, int px, int py, vector<pi> &ret){
    if(n == 2){
        int p = 0;
        for(int i=0; i<py; i++){
            ret.push_back(pi(p, i));
            ret.push_back(pi(p^1, i));
            p ^= 1;
        }
        for(int i=py; i<m; i++){
            ret.push_back(pi(p, i));
        }
        for(int i=m-1; i>=py; i--){
            ret.push_back(pi(p^1, i));
        }
        return;
    }
    if(m == 2){
        int p = 0;
        for(int i=0; i<px; i++){
            ret.push_back(pi(i, p));
            ret.push_back(pi(i, p^1));
            p ^= 1;
        }
        for(int i=px; i<n; i++){
            ret.push_back(pi(i, p));
        }
        for(int i=n-1; i>=px; i--){
            ret.push_back(pi(i, p^1));
        }
        return;
    }
    if(px%2 == 1){
        route(m, n, py, px, ret);
        for(auto &i : ret) swap(i.first, i.second);
        return;
    }
    for(int i=0; i<px; i++){
        if(i%2) for(int j=m-1; j>=0; j--) ret.push_back(pi(i, j));
        else for(int j=0; j<m; j++) ret.push_back(pi(i, j));
    }
    for(int i=0; i<py; i++){
        if(i%2) for(int j=n-1; j>=px; j--) ret.push_back(pi(j, i));
        else for(int j=px; j<n; j++) ret.push_back(pi(j, i));
    }
    for(int i=n-1; i>=px; i--){
        if(i%2) for(int j=py; j<m; j++) ret.push_back(pi(i, j));
        else for(int j=m-1; j>=py; j--) ret.push_back(pi(i, j));
    }
}

void solve(){
    v.clear();
    cin >> n >> m >> sx >> sy >> ex >> ey;
    sx--, sy--, ex--, ey--;
    if((sx + sy + ex + ey) % 2 == 0){
        cout << -1 << endl;
        return;
    }
    if(n == 2 || m == 2){
        int bs = 0;
        if(m == 2){
            bs = 1;
            swap(n, m);
            swap(sx, sy);
            swap(ex, ey);
        }
        if(!case1()){
            cout << -1 << endl;
            return;
        }
        if(bs){
            for(auto &i : v) swap(i.first, i.second);
        }
        print();
        return;
    }
    int osx = sx, osy = sy, oex = ex, oey = ey;
    if(abs(ex - sx) + abs(ey - sy) == 1){
        int swp = 0, rev = 0, bs = 0;
        if(sx == ex){
            swap(sx, sy);
            swap(ex, ey);
            swap(n, m);
            swp = 1;
        }
        if(sx > ex){
            swap(sx, ex);
            swap(sy, ey);
        }
        if(ex == n-1){
            sx = 0;
            ex = 1;
            bs = 1;
        }
        for(int i=0; i<m; i++){
            if(i%2) for(int j=0; j<n-1; j++) v.push_back(pi(j, i));
            else for(int j=n-2; j>=0; j--) v.push_back(pi(j, i));
        }
        for(int i=0; i<m; i++){
            v.push_back(pi(n-1, m-1-i));
        }
        if(bs) for(auto &i : v) i.first = n - 1 - i.first;
        if(swp) for(auto &i : v) swap(i.first, i.second);
        rotate(v.begin(), find(v.begin(), v.end(), pi(osx, osy)), v.end());
        if(v.back() != pi(oex, oey)){
            reverse(v.begin(), v.end());
            rotate(v.begin(), find(v.begin(), v.end(), pi(osx, osy)), v.end());
        }
        print();
        return;
    }
    int swp = 0;
    if(sx/2 != ex/2){
        swap(sx, sy);
        swap(ex, ey);
        swap(n, m);
        swp = 1;
    }
    if(sy > ey){
        swap(sx, ex);
        swap(sy, ey);
    }
    int yp = sy/2 * 2 + 2;
    vector<pi> v1, v2;
    if((sx + yp - 1 - sy) % 2 == 1){
        route(n, yp, sx, yp-1-sy, v1);
        reverse(v1.begin(), v1.end());
        for(auto &i : v1) v.push_back(pi(i.first, yp-1-i.second));
    }
    else{
        route(n, yp, n-1-sx, yp-1-sy, v1);
        reverse(v1.begin(), v1.end());
        for(auto &i : v1) v.push_back(pi(n-1-i.first, yp-1-i.second));
    }
    if((ex + ey - yp) % 2 == 1){
        route(n, m-yp, ex, ey-yp, v2);
        for(auto &i : v2) v.push_back(pi(i.first, yp+i.second));
    }
    else{
        route(n, m-yp, n-1-ex, ey-yp, v2);
        for(auto &i : v2) v.push_back(pi(n-1-i.first, yp+i.second));
    }
    if(swp) for(auto &i : v) swap(i.first, i.second);
    rotate(v.begin(), find(v.begin(), v.end(), pi(osx, osy)), v.end());
    if(v.back() != pi(oex, oey)){
        reverse(v.begin(), v.end());
        rotate(v.begin(), find(v.begin(), v.end(), pi(osx, osy)), v.end());
    }
    print();
}

int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}