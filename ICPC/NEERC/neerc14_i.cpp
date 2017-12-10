#include <cstdio>
#include <algorithm>
using namespace std;

int a[200005];
int lis[200005], lds[200005];

struct rmq{
    int tree[530000], lim;
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
    }
    void add(int pos, int v){
        pos += lim;
        tree[pos] = max(tree[pos],v);
        while(pos > 1){
            pos >>= 1;
            tree[pos] = max(tree[2*pos],tree[2*pos+1]);
        }
    }
    int q(int s, int e){
        s += lim;
        e += lim;
        int r = 0;
        while(s < e){
            if(s%2 == 1) r = max(r,tree[s++]);
            if(e%2 == 0) r = max(r,tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) r = max(r,tree[s]);
        return r;
    }
}rmq1,rmq2;

int n;

int main(){
    scanf("%d",&n);
    rmq1.init(n);
    rmq2.init(n);
    for (int i=1; i<=n; i++) {
        int t;
        scanf("%d",&t);
        a[t] = i;
    }
    for (int i=1; i<=n; i++) {
        lis[i] = 1 + rmq1.q(1,a[i]-1);
        rmq1.add(a[i],lis[i]);
        lis[i] = max(lis[i],lis[i-1]);
    }
    for (int i=n; i; i--) {
        lds[i] = 1 + rmq2.q(1,a[i]-1);
        rmq2.add(a[i],lds[i]);
        lds[i] = max(lds[i],lds[i+1]);
    }
    int ret = 0;
    for (int i=1; i<=n; i++) {
        ret = max(ret,lis[i] + lds[i+1]);
    }
    printf("%d",ret);
}