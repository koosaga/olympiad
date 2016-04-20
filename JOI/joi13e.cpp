#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<int,int> pi;
 
struct bit{
    int tree[131073], lim;
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
    }
    void add(int x){
        while (x <= lim) {
            tree[x]++;
            x += x & -x;
        }
    }
    int sum(int p){
        int res = 0;
        while (p) {
            res += tree[p];
            p -= p & -p;
        }
        return res;
    }
}bit;
 
struct seg{
    long long tree[270000], lazy[270000];
    void lazydown(int p, int ps, int pe){
        tree[2*p] += lazy[p];
        tree[2*p+1] += lazy[p];
        lazy[2*p] += lazy[p];
        lazy[2*p+1] += lazy[p];
        lazy[p] = 0;
    }
    void add(int s, int e, int x, int ps, int pe, int p){
        if(e < ps || pe < s) return;
        if(s <= ps && pe <= e){
            tree[p] += x;
            lazy[p] += x;
            return;
        }
        lazydown(p,ps,pe);
        int pm = (ps+pe)/2;
        add(s,e,x,ps,pm,2*p);
        add(s,e,x,pm+1,pe,2*p+1);
        tree[p] = max(tree[2*p],tree[2*p+1]);
    }
}seg;
 
int a[100005],n;
 
vector<int> piva, pivb;
vector<int> hull;
vector<pi> del;
 
bool not_mid[100005];
 
void erase_pt(int x, int y){
    int s = (int)(lower_bound(piva.begin(),piva.end(),y) - piva.begin());
    int e = (int)(lower_bound(pivb.begin(),pivb.end(),x) - pivb.begin());
    if(s != piva.size() && piva[s] == y){
        seg.add(s,s,1,0,n-1,1);
    }
    seg.add(s,e-1,-2,0,n-1,1);
}
 
void add_pt(int x, int y){
    int s = (int)(lower_bound(piva.begin(),piva.end(),y) - piva.begin());
    int e = (int)(lower_bound(pivb.begin(),pivb.end(),x) - pivb.begin());
    if(s != piva.size() && piva[s] == y){
        seg.add(s,s,-1,0,n-1,1);
    }
    seg.add(s,e-1,2,0,n-1,1);
}
 
stack<int> sx, sy;
 
void add_session(int x, int y){
    int s = (int)(lower_bound(piva.begin(),piva.end(),y) - piva.begin());
    int e = (int)(lower_bound(pivb.begin(),pivb.end(),x) - pivb.begin());
    sx.push(s);
    sy.push(e-1);
    seg.add(s,e-1,-1,0,n-1,1);
}
 
void clear_session(){
    while (!sx.empty()) {
        int x = sx.top();
        int y = sy.top();
        seg.add(x,y,1,0,n-1,1);
        sx.pop();
        sy.pop();
    }
}
 
long long get_max(){
    return seg.tree[1];
}
 
long long get_area(){
    for (int i=1; i<=n; i++) {
        if(piva.empty() || piva.back() < a[i]){
            piva.push_back(a[i]);
            pivb.push_back(i);
            not_mid[i] = 1;
        }
        del.push_back(pi(a[i],i));
    }
    sort(del.begin(),del.end());
    reverse(del.begin(),del.end());
    for (int i=1; i<=n; i++) {
        while (!hull.empty() && a[hull.back()] >= a[i]) hull.pop_back();
        hull.push_back(i);
    }
    for (int i=0; i<hull.size(); i++) {
        not_mid[hull[i]] = 1;
    }
    int p = 0;
    long long r = 0;
    for (int i=1; i<=n; i++) {
        if(hull[p] == i){
            clear_session();
            while (!del.empty() && del.back().first < a[hull[p]]) {
                if(!not_mid[del.back().second]){
                    erase_pt(del.back().second,del.back().first);
                }
                del.pop_back();
            }
            for (int i=(int)del.size() - 1; i>=0; i--) {
                if(del[i].first == a[hull[p]] && !not_mid[del[i].second]){
                    add_session(del[i].second,del[i].first);
                }
                else break;
            }
            r = max(r,get_max());
            p++;
        }
        if(!not_mid[i]) add_pt(i,a[i]);
    }
    return r;
}
 
int same;
 
long long input(){
    vector<int> v;
    long long cnt = 0;
    scanf("%d",&n);
    bit.init(n);
    for (int i=1; i<=n; i++) {
        scanf("%d",&a[i]);
        v.push_back(a[i]);
    }
    v.push_back(-1);
    sort(v.begin(),v.end());
    v.resize(unique(v.begin(),v.end()) - v.begin());
    if(v.size() != n+1) same = 1;
    for (int i=1; i<=n; i++) {
        a[i] = (int)(lower_bound(v.begin(),v.end(),a[i]) - v.begin());
    }
    for (int i=1; i<=n; i++) {
        cnt += i - 1 - bit.sum(a[i]);
        bit.add(a[i]);
    }
    return cnt;
}
 
int main(){
    long long cnt = input();
    if(cnt == 0) printf("%d", 1 - same);
    else printf("%lld",cnt - 1 - get_area());
}