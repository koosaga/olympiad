#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
using namespace std;
typedef long long lint;
typedef pair<int,int> pi;

struct rmq{
    pi tree[270000];
    int lim;
    void init(int n, int *a){
        for(lim = 1; lim <= n; lim <<= 1);
        fill(tree,tree+270000,pi(1e9,0));
        for(int i=0; i<n; i++) tree[lim+i] = pi(a[i],i);
        for(int i=lim-1; i; i--) tree[i] = min(tree[2*i],tree[2*i+1]);
    }
    pi q(int s, int e){
        s += lim;
        e += lim;
        pi r(1e9,0);
        while(s<e){
            if(s%2 == 1) r = min(r,tree[s++]);
            if(e%2 == 0) r = min(r,tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) r = min(r,tree[s]);
        return r;
    }
}rmq;

int n;
int a[100005];
lint sum[100005];

pair<lint,pi> ret;

void sol(int s, int e){
    if(s > e) return;
    pi t = rmq.q(s,e);
    ret = max(ret,make_pair(1ll * t.first * (sum[e] - (s ? sum[s-1] : 0)),pi(s,e)));
    sol(s,t.second-1);
    sol(t.second+1,e);
}

int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d",&a[i]);
        sum[i] = a[i];
        if(i) sum[i] += sum[i-1];
    }
    rmq.init(n,a);
    sol(0,n-1);
    printf("%lld\n%d %d",ret.first,ret.second.first+1,ret.second.second+1);
}