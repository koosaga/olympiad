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

int r, c, n, m;
pi a[200005], b[200005];

struct seg{
    int s, e, x;
    bool operator<(const seg &a)const{
        return x < a.x;
    }
};

struct mir{
    int x, y, d;
    bool operator<(const mir &a)const{
        if(x != a.x) return x < a.x;
        return y < a.y;
    }
};

vector<seg> stx, sty, edx, edy;
set<mir> ordx, ordy;
bool collide;

void shoot(int x, int y, int d, vector<seg> &vx, vector<seg> &vy){
    if(d == 0){
        auto it = ordx.upper_bound({x, y, -1}); // y 증가. 
        if(it == ordx.end() || it->x != x){
            if(x == r){
                collide = 1;
            }
            else{
                vx.push_back({y+1, c, x});
            }
        }
        else{
            vx.push_back({y+1, it->y-1, x});
            shoot(it->x, it->y, d ^ it->d, vx, vy);
        }
        return;
    }
    if(d == 1){
        auto it = ordy.upper_bound({y, x, -1});
        if(it == ordy.end() || it->x != y){
            vy.push_back({x+1, r, y});
        }
        else{
            vy.push_back({x+1, it->y-1, y});
            shoot(it->y, it->x, d ^ it->d, vx, vy);
        }
        return;
    }
    if(d == 2){
        auto it = ordx.lower_bound({x, y, -1}); // y 감
        if(it == ordx.begin() || (--it)->x != x){ 
            if(x == 1){
                collide = 1;
            }
            else{
                vx.push_back({1, y-1, x});
            }
        }
        else{
            vx.push_back({it->y+1, y-1, x});
            shoot(it->x, it->y, d ^ it->d, vx, vy);
        }
        return;
    }
    if(d == 3){
        auto it = ordy.lower_bound({y, x, -1});
        if(it == ordy.begin() || (--it)->x != y){
            vy.push_back({1, x-1, y});
        }
        else{
            vy.push_back({it->y+1, x-1, y});
            shoot(it->y, it->x, d ^ it->d, vx, vy);
        }
        return;
    }
}

int sx = 1e9, sy = 1e9;

void init(){
    sx = sy = 1e9;
    collide = 0;
    ordx.clear();
    ordy.clear();
    stx.clear();
    sty.clear();
    edx.clear();
    edy.clear();
}

struct swp{
    int x, y, d;
    bool operator<(const swp &a)const{
        return x < a.x;
    }
};

struct bit{
    int tree[1000005], lim;
    void init(int n){
        lim = n+2;
        memset(tree, 0, sizeof(tree));
    }
    void add(int x, int v){
        x += 2;
        while(x <= lim){
            tree[x] += v;
            x += x & -x;
        }
    }
    int f(int x){
        x += 2;
        int ret = 0;
        while(x){
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
    int sum(int s, int e){
        return f(e) - f(s-1);
    }
}bit;


lint get_intersect(vector<seg> &vx, vector<seg> &vy){
    sort(vx.begin(), vx.end()); // x순 정렬. y축 최소가 누구일까여??
    vector<swp> sweep;
    multiset<int> s;
    for(auto &i : vy){
        if(i.s > i.e) continue;
        sweep.push_back({i.s, i.x, 1});
        sweep.push_back({i.e+1, i.x, -1});
    }
    sort(sweep.begin(), sweep.end());
    bit.init(max(r, c));
    int p = 0;
    lint ret = 0;
    for(auto &i : vx){
        while(p < sweep.size() && sweep[p].x <= i.x){
            bit.add(sweep[p].y, sweep[p].d);
            if(sweep[p].d == 1){
                s.insert(sweep[p].y);
            }
            else{
                s.erase(s.find(sweep[p].y));
            }
            p++;
        }
        ret += bit.sum(i.s, i.e);
        auto it = s.lower_bound(i.s);
        if(it != s.end() && *it <= i.e){
            tie(sx, sy) = min(pi(sx, sy), pi(i.x, *it));
        }
    }
    return ret;
}

int main(){
    int t = 0;
    while(~scanf("%d %d %d %d",&r,&c,&n,&m)){
        init();
        for(int i=0; i<n; i++){
            scanf("%d %d",&a[i].first, &a[i].second);
            ordx.insert({a[i].first, a[i].second, 3});
            ordy.insert({a[i].second, a[i].first, 3});
        }
        for(int i=0; i<m; i++){
            scanf("%d %d",&b[i].first, &b[i].second);
            ordx.insert({b[i].first, b[i].second, 1});
            ordy.insert({b[i].second, b[i].first, 1});
        }
        shoot(1, 0, 0, stx, sty);
        shoot(r, c+1, 2, edx, edy);
        printf("Case %d: ",++t);
        if(collide){
            puts("0");
        }
        else{
            lint ret = get_intersect(stx, edy) + get_intersect(edx, sty);
            if(ret == 0){
                puts("impossible");
            }
            else{
                printf("%lld %d %d\n",ret, sx, sy);
            }
        }
    }
}