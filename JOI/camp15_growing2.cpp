#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef pair<int,int> pi;
 
vector<int> v;
 
int n, a[100005], p[100005], c[100005];
lint pc[100005];
lint dp1[100005], dp2[100005];
 
struct bit{
    lint tree[100005];
    int lim;
    void init(int n){
        memset(tree,0,sizeof(tree));
        lim = n+2;
    }
    void add(int x, lint v){
        x += 2;
        while(x <= lim){
            tree[x] += v;
            x += x & -x;
        }
    }
    lint sum(int x){
        x += 2;
        lint ret = 0;
        while(x){
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
}bit;
 
struct seg{
    lint tree[270000], lazy[270000];
    void init(){
        memset(tree,0,sizeof(tree));
        memset(lazy,0,sizeof(lazy));
    }
    void lazydown(int p){
        tree[2*p] += lazy[p];
        tree[2*p+1] += lazy[p];
        lazy[2*p] += lazy[p];
        lazy[2*p+1] += lazy[p];
        lazy[p] = 0;
    }
    void add(int s, int e, int ps, int pe, int p, lint v){
        if(e < ps || pe < s) return;
        if(s <= ps && pe <= e){
            tree[p] += v;
            lazy[p] += v;
            return;
        }
        lazydown(p);
        int pm = (ps + pe) / 2;
        add(s,e,ps,pm,2*p,v);
        add(s,e,pm+1,pe,2*p+1,v);
        tree[p] = max(tree[2*p],tree[2*p+1]);
    }
    lint q(int s, int e, int ps, int pe, int p){
        if(e < ps || pe < s) return -1e18;
        if(s <= ps && pe <= e) return tree[p];
        lazydown(p);
        int pm = (ps + pe) / 2;
        return max(q(s,e,ps,pm,2*p),q(s,e,pm+1,pe,2*p+1));
    }
}seg;
 
vector<pi> stk;
void solve(lint *dp){
    bit.init(n);
    seg.init();
    stk.clear();
    for (int i=1; i<=n; i++) {
        pc[i] = pc[i-1] + c[i];
        stk.push_back(pi(a[i],i));
    }
    sort(stk.begin(),stk.end());
    seg.add(0,0,0,n,1,0);
    for (int i=0; i<n; i++) {
        int pos = stk[i].second;
        bit.add(pos,c[pos]);
        seg.add(pos,n,0,n,1,-c[pos]);
        dp[pos] = max(0ll,seg.q(0,pos-1,0,n,1)) - pc[pos] + bit.sum(pos) + p[pos];
        seg.add(pos,pos,0,n,1,dp[pos] + pc[pos]);
    }
}
 
int main(){
    scanf("%d",&n);
    v.push_back(-1);
    for (int i=1; i<=n; i++) {
        scanf("%d %d %d",&a[i],&p[i],&c[i]);
        v.push_back(a[i]);
    }
    sort(v.begin(),v.end());
    v.resize(unique(v.begin(),v.end()) - v.begin());
    for (int i=1; i<=n; i++) {
        a[i] = (int)(lower_bound(v.begin(),v.end(),a[i]) - v.begin());
    }
    solve(dp1);
    reverse(a+1,a+n+1);
    reverse(p+1,p+n+1);
    reverse(c+1,c+n+1);
    solve(dp2);
    lint ret = 0;
    for (int i=1; i<=n; i++) {
        ret = max(ret,dp1[n+1-i] + dp2[i] - p[i]);
    }
    printf("%lld\n",ret);
}