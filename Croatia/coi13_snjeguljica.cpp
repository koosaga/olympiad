#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
 
struct rmq{
    int tree[530000], lim;
    void init(int n, int *a){
        memset(tree,0x3f,sizeof(tree));
        for(lim = 1; lim <= n; lim <<= 1);
        for(int i=1; i<=n; i++){
            tree[i + lim] = a[i];
        }
        for(int i=lim-1; i; i--){
            tree[i] = min(tree[2*i],tree[2*i+1]);
        }
    }
    void add(int pos, int val){
        tree[lim + pos] = val;
        int t = lim + pos;
        while(t > 1){
            t >>= 1;
            tree[t] = min(tree[2*t],tree[2*t+1]);
        }
    }
    int q(int s, int e){
        int res = 1e9;
        s += lim;
        e += lim;
        while(s < e){
            if(s%2 == 1) res = min(res,tree[s++]);
            if(e%2 == 0) res = min(res,tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) res = min(res,tree[s]);
        return res;
    }
}mint;
struct rmq2{
    int tree[530000], lim;
    void init(int n, int *a){
        for(lim = 1; lim <= n; lim <<= 1);
        for(int i=1; i<=n; i++){
            tree[i + lim] = a[i];
        }
        for(int i=lim-1; i; i--){
            tree[i] = max(tree[2*i],tree[2*i+1]);
        }
    }
    void add(int pos, int val){
        tree[lim + pos] = val;
        int t = lim + pos;
        while(t > 1){
            t >>= 1;
            tree[t] = max(tree[2*t],tree[2*t+1]);
        }
    }
    int q(int s, int e){
        int res = 0;
        s += lim;
        e += lim;
        while(s < e){
            if(s%2 == 1) res = max(res,tree[s++]);
            if(e%2 == 0) res = max(res,tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) res = max(res,tree[s]);
        return res;
    }
}maxt;
 
int main(){
    int n,q,t,u,v;
    scanf("%d %d",&n,&q);
    int a[200005],b[200005];
    for (int i=1; i<=n; i++) {
        scanf("%d",&b[i]);
        a[b[i]] = i;
    }
    mint.init(n,a);
    maxt.init(n,a);
    for (int i=0; i<q; i++) {
        scanf("%d %d %d",&t,&u,&v);
        if(t == 1){
            int locx = b[u];
            int locy = b[v];
            swap(a[locx],a[locy]);
            swap(b[u],b[v]);
            mint.add(locx,a[locx]);
            mint.add(locy,a[locy]);
            maxt.add(locx,a[locx]);
            maxt.add(locy,a[locy]);
        }
        else{
            puts(maxt.q(u,v) - mint.q(u,v) == v-u?"YES":"NO");
        }
    }
}