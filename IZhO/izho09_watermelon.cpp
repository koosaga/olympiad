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
 
map<int, pair<int, int> > mp;
 
int n;
 
struct cht{
    struct node{
        int a, b, idx;
    };
    deque<node> dq;
    bool cross(node a, node b, node c){
        return 1ll * (a.b - b.b) * (c.a - b.a) > 1ll * (b.b - c.b) * (b.a - a.a);
    }
    void insert(node t){
        while(dq.size() >= 2 && cross(dq[dq.size()-2], dq.back(), t)){
            dq.pop_back();
        }
        dq.push_back(t);
    }
    int getp1(int x){
        int s = 0, e = dq.size() - 1;
        while(s != e){
            int m = (s+e)/2;
            if(1ll * dq[m].a * x + dq[m].b < 1ll * dq[m+1].a * x + dq[m+1].b) s = m+1;
            else e = m;
        }
        return s;
    }
    int getp2(int x){
        int s = 0, e = dq.size() - 1;
        while(s != e){
            int m = (s+e)/2;
            if(1ll * dq[m].a * x + dq[m].b <= 1ll * dq[m+1].a * x + dq[m+1].b) s = m+1;
            else e = m;
        }
        return s;
    }
    int query(int x){
        int s = getp1(x), e = getp2(x);
        lint retv = -1e18;
        int retp = -1;
        for(int i=max(s, 0); i<=min(e, (int)dq.size()-1); i++){
            if(retv < 1ll * dq[i].a * x + dq[i].b){
                retv = 1ll * dq[i].a * x + dq[i].b;
                retp = dq[i].idx;
            }
            else if(retv == 1ll * dq[i].a * x + dq[i].b){
                retp = min(retp, dq[i].idx);
            }
        }
        return retp;
    }
}cht;
 
int main(){
    scanf("%d",&n);
    for(int i=1; i<=n; i++){
        int b, a;
        scanf("%d %d",&b, &a);
        if(mp.find(a) != mp.end()){
            mp[a] = max(mp[a], pi(b, -i));
        }
        else mp[a] = pi(b, -i);
    }
    for(auto &i : mp){
        cht.insert({i.first, i.second.first, -i.second.second});
    }
    int q;
    scanf("%d",&q);
    while(q--){
        int t;
        scanf("%d",&t);
        printf("%d\n",cht.query(t));
    }
}