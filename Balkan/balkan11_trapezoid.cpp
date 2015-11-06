#include <cstdio>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;
 
const int mod = 30013;
 
int n;
int a[100005], b[100005], c[100005], d[100005];
int dp[100005], cnt[100005];
 
struct seg{int a,b,p,i;}st[200005];
bool cmp(seg a, seg b){return a.a < b.a;}
struct seg2{int dp,a,b,p,i;}st2[200005];
bool cmp2(seg2 a, seg2 b){return a.a < b.a;}
 
struct rmq{
    int lim, tree[530000];
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
    }
    void ins(int s, int v){
        s += lim;
        tree[s] = v;
        while(s>1){
            s >>= 1;
            tree[s] = max(tree[2*s],tree[2*s+1]);
        }
    }
    int q(int s, int e){
        s += lim;
        e += lim;
        int r = 0;
        while(s<e){
            if(s%2 == 1) r = max(r,tree[s++]);
            if(e%2 == 0) r = max(r,tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) r = max(r,tree[s]);
        return r;
    }
}rmq;
 
struct bit{
    int lim, tree[132000];
    void init(int n){
        n += 2;
        for(lim = 1; lim <= n; lim <<= 1);
    }
    void add(int x, int v){
        x += 2;
        while(x <= lim){
            tree[x] += v;
            tree[x] %= mod;
            x += x & -x;
        }
    }
    int sum(int x){
        x += 2;
        int r = 0;
        while(x){
            r += tree[x];
            r %= mod;
            x -= x & -x;
        }
        return r;
    }
}idx;
 
void input(){
    vector<int> vu, vd;
    scanf("%d",&n);
    rmq.init(2*n);
    for (int i=0; i<n; i++) {
        scanf("%d %d %d %d",&a[i],&b[i],&c[i],&d[i]);
        vu.push_back(a[i]);
        vu.push_back(b[i]);
        vd.push_back(c[i]);
        vd.push_back(d[i]);
    }
    sort(vu.begin(),vu.end());
    sort(vd.begin(),vd.end());
    for (int i=0; i<n; i++) {
        a[i] = (int)(lower_bound(vu.begin(),vu.end(),a[i]) - vu.begin());
        b[i] = (int)(lower_bound(vu.begin(),vu.end(),b[i]) - vu.begin());
        c[i] = (int)(lower_bound(vd.begin(),vd.end(),c[i]) - vd.begin());
        d[i] = (int)(lower_bound(vd.begin(),vd.end(),d[i]) - vd.begin());
        st[2*i] = {a[i],c[i],0,i};
        st[2*i+1] = {b[i],d[i],1,i};
    }
    sort(st,st+2*n,cmp);
}
 
vector<pi> v;
 
int main(){
    input();
    for (int i=0; i<2*n; i++) {
        if(st[i].p == 0){
            dp[st[i].i] = rmq.q(0,st[i].b) + 1;
            st2[i] = {dp[st[i].i],st[i].a,st[i].b,0,st[i].i};
        }
        else{
            rmq.ins(st[i].b,dp[st[i].i]);
            st2[i] = {dp[st[i].i],st[i].a,st[i].b,1,st[i].i};
        }
    }
    int mcnt = *max_element(dp,dp+n);
    printf("%d ",mcnt);
    for (int i=0; i<2*n; i++) {
        if(st2[i].p == 1) v.push_back(pi(st2[i].dp,st2[i].b));
    }
    sort(v.begin(),v.end());
    sort(st2,st2+2*n,cmp2);
    idx.init(n);
    int acnt = 0;
    for (int i=0; i<2*n; i++) {
        if(st2[i].p == 0){
            if(st2[i].dp == 1){
                cnt[st2[i].i] = 1;
            }
            else{
                int start = (int)(lower_bound(v.begin(),v.end(),pi(st2[i].dp-1,0)) - v.begin());
                int end = (int)(lower_bound(v.begin(),v.end(),pi(st2[i].dp-1,st2[i].b)) - v.begin());
                cnt[st2[i].i] = idx.sum(end-1) - idx.sum(start-1);
                if(st2[i].dp == mcnt) acnt += cnt[st2[i].i];
            }
        }
        else{
            int pos = (int)(lower_bound(v.begin(),v.end(),pi(st2[i].dp,st2[i].b)) - v.begin());
            idx.add(pos,cnt[st2[i].i]);
        }
        acnt %= mod;
    }
    if(acnt < 0) acnt += mod;
    printf("%d",acnt);
}