#include <cstdio>
#include <algorithm>
using namespace std;
 
struct pt{int x,y,z;}a[500005];
bool cmp(pt a, pt b){return a.x > b.x;}
 
int n;
 
struct rmq{
    int tree[1050000], lim;
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
    }
    void add(int x, int v){
        x += lim;
        tree[x] = max(tree[x],v);
        while(x > 1){
            x >>= 1;
            tree[x] = max(tree[2*x],tree[2*x+1]);
        }
    }
    int q(int s, int e){
        s += lim;
        e += lim;
        int ret = 0;
        while(s < e){
            if(s%2 == 1) ret = max(ret,tree[s++]);
            if(e%2 == 0) ret = max(ret,tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) ret = max(ret,tree[s]);
        return ret;
    }
}rmq;
 
int main(){
    scanf("%d",&n);
    rmq.init(n);
    for (int i=0; i<n; i++) {
        int t;
        scanf("%d",&t);
        a[t-1].x = n - i;
    }
    for (int i=0; i<n; i++) {
        int t;
        scanf("%d",&t);
        a[t-1].y = n - i;
    }
    for (int i=0; i<n; i++) {
        int t;
        scanf("%d",&t);
        a[t-1].z = n - i;
    }
    sort(a,a+n,cmp);
    int ret = 0;
    for (int i=0; i<n; i++) {
        int maxv = rmq.q(a[i].y+1,n);
        if(maxv <= a[i].z) ret++;
        rmq.add(a[i].y,a[i].z);
    }
    printf("%d",ret);
}