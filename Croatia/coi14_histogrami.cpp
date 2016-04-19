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
typedef pair<lint, lint> pi;
 
int n, m, g;
int h[1000005];
 
struct pnt{
    int x, y;
    lint cost;
}a[100005];
 
struct sweep{
    int y, x, idx;
};
 
vector<sweep> v;
 
struct bit{
    lint tree[1000005];
    void add(int x, int v){
        while(x <= 1000000){
            tree[x] += v;
            x += x & -x;
        }
    }
    lint query(int x){
        lint ret = 0;
        while(x){
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
    lint sum(int s, int e){
        return query(e) - query(s-1);
    }
}bit1, bit2;
 
void getcost1(){
    int cp = 0;
    for(auto &i : v){
        while(cp < i.x){
            bit1.add(h[cp++], 1);
        }
        lint ret = bit1.sum(1, i.y - 1) + bit1.sum(i.y + 1, 1000000);
        if(i.idx < 0) a[-i.idx].cost -= ret;
        else a[i.idx].cost += ret;
    }
}
 
void getcost2(){
    int cp = 0;
    for(auto &i : v){
        while(cp < i.x){
            bit1.add(h[cp], 1);
            bit2.add(h[cp], h[cp]);
            cp++;
        }
        lint ret = bit2.sum(i.y + 1, 1000000) - bit1.sum(i.y + 1, 1000000) * i.y;
        ret += bit1.sum(1, i.y - 1) * i.y - bit2.sum(1, i.y - 1);
        if(i.idx < 0) a[-i.idx].cost -= ret;
        else a[i.idx].cost += ret;
    }
}
 
int par[100005];
 
int main(){
    scanf("%d %d %d",&n,&m,&g);
    for(int i=0; i<n; i+=2){
        int sx, sy, ex;
        scanf("%d %d %d %*d",&sx,&sy,&ex);
        for(int j=sx; j<ex; j++){
            h[j] = sy;
        }
    }
    for(int i=0; i<m; i++){
        scanf("%d %d",&a[i].x, &a[i].y);
        a[i].cost = 1e18;
    }
    sort(a, a+m, [&](const pnt &a, const pnt &b){
        return a.y == b.y ? a.x < b.x : a.y < b.y;
    });
    for(int i=1; i<m; i++){
        if(a[i-1].y == a[i].y){
            a[i].cost = 0;
            v.push_back({a[i].y, a[i].x, i});
            v.push_back({a[i].y, a[i-1].x, -i});
        }
    }
    sort(v.begin(), v.end(), [&](const sweep &a, const sweep &b){
        return a.x < b.x;
    });
    if(g == 1) getcost1();
    else getcost2();
    sort(a, a+m, [&](const pnt &a, const pnt &b){
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    });
    map<int, pi> mp;
    lint tret = 1e18, tretp = -1;
    for(int i=0; i<m; ){
        int e = i;
        while(e < m && a[e].x == a[i].x) e++;
        if(a[i].x == 0){
            for(int j=i; j<e; j++){
                par[j] = -1;
                mp[a[j].y] = pi(0, j);
            }
            i = e;
            continue;
        }
        lint ret = 1e18, retp = -1; 
        for(int j=i; j<e; j++){
            if(mp.find(a[j].y) == mp.end()) continue;
            if(ret > mp[a[j].y].first + a[j].cost){
                ret = mp[a[j].y].first + a[j].cost;
                retp = j;
            }
        }
        if(retp != -1){
            for(int j=i; j<e; j++){
                mp[a[j].y].first = ret;
                if(retp != j) mp[a[j].y].second = j, par[j] = retp;
                else par[j] = mp[a[j].y].second;
            }
        }
        if(e == m){
            tretp = retp;
            tret = mp[a[tretp].y].first;
        }
        i = e;
    }
    vector<pnt> ans;
    printf("%lld\n",tret);
    while(tretp != -1){
        ans.push_back(a[tretp]);
        tretp = par[tretp];
    }
    reverse(ans.begin(), ans.end());
    printf("%d\n",ans.size());
    for(auto &i : ans){
        printf("%d %d\n",i.x, i.y);
    }
}