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
const int oo = 2e9;
 
struct intv{
    int s, e, x, idx;
    bool operator<(const intv &a)const{
        return x == a.x ? s < a.s : x < a.x;
    }
}a[100005];
 
int n;
vector<intv> skyline;
 
struct rmq{
    pi tree[270000];
    int lim;
    void init(int n, intv *a){
        fill(tree, tree + 270000, pi(-oo, -oo));
        for(lim = 1; lim <= n; lim <<= 1);
        for(int i=0; i<=n; i++){
            tree[i+lim] = pi(a[i].e, i);
        }
        for(int i=lim-1; i; i--){
            tree[i] = max(tree[2*i], tree[2*i+1]);
        }
    }
    int query(int s, int e){
        s += lim;
        e += lim;
        pi ret(-oo, -oo);
        while(s < e){
            if(s%2 == 1) ret = max(ret, tree[s++]);
            if(e%2 == 0) ret = max(ret, tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) ret = max(ret, tree[s]);
        return ret.second;
    }
}rmq;
 
int getnxt(int ph, int pd){
    int s = lower_bound(a, a+n+1, (intv){-oo, -oo, pd, -oo}) - a;
    int e = lower_bound(a, a+n+1, (intv){ph+1, -oo, pd, -oo}) - a;
    return rmq.query(s, e-1);
}
 
bool ok[100005];
 
void solve(){
    int cur = 0;
    for(int i=0; i<skyline.size(); i++){
        ok[a[cur].idx] = 1;
        while(a[cur].e < skyline[i].e){
            cur = getnxt(a[cur].e, skyline[i].x);
            ok[a[cur].idx] = 1;
        }
        if(i+1 < skyline.size()){
            cur = getnxt(skyline[i+1].s, skyline[i+1].x);
            ok[a[cur].idx] = 1;
        }
    }
    printf("%d\n",count(ok + 1, ok + n + 1, true));
    for(int i=1; i<=n; i++){
        if(ok[i]) printf("%d ",i);
    }
}
 
vector<pi> sweep;
 
int main(){
    scanf("%d",&n);
    int mini = 2e9, maxi = -2e9;
    for(int i=1; i<=n; i++){
        scanf("%d %d %d",&a[i].s, &a[i].e, &a[i].x);
        a[i].e += a[i].s;
        a[i].idx = i;
        a[i].x++;
        maxi = max(maxi, a[i].e);
        mini = min(mini, a[i].s);
    }
    a[0] = {mini-1, maxi+1, 1, 0};
    for(int i=0; i<=n; i++){
        sweep.push_back(pi(a[i].s, -a[i].x));
        sweep.push_back(pi(a[i].e, a[i].x));
    }
    sort(sweep.begin(), sweep.end());
    int bef = -1, befh = -1;
    map<int, int> mp;
    mp[0]++;
    for(int i=0; i<sweep.size(); ){
        int e = i;
        while(e < sweep.size() && sweep[e].first == sweep[i].first){
            e++;
        }
        for(int j=i; j<e; j++){
            if(sweep[j].second < 0){
                mp[-sweep[j].second]++;
            }
            else{
                mp[sweep[j].second]--;
                if(mp[sweep[j].second] == 0){
                    mp.erase(sweep[j].second);
                }
            }
        }
        if(mp.rbegin()->first != befh){
            if(befh != -1){
                skyline.push_back({bef, sweep[i].first, befh});
            }
            befh = mp.rbegin()->first;
            bef = sweep[i].first;
        }
        i = e;
    }
    sort(a, a+n+1);
    rmq.init(n, a);
    solve();
}