#include <cstdio>
#include <vector>
using namespace std;
 
int n,m,k;
 
struct disj{
    int pa[400005], r[400005];
    void init(int n){
        for(int i=0; i<=n; i++) pa[i] = i;
    }
    int find(int x){
        if(pa[x] == x) return x;
        return pa[x] = find(pa[x]);
    }
    void uni(int p, int q){
        p = find(p);
        q = find(q);
        if(r[p] < r[q]) pa[q] = p;
        else pa[p] = q;
        if(r[p] == r[q]) r[p]++;
    }
}disj;
 
int vis[400005];
int main(){
    scanf("%d %d %d",&n,&m,&k);
    disj.init(2*(n+m));
    for (int i=0; i<k; i++) {
        int x,y,z;
        scanf("%d %d %d",&x,&y,&z);
        if(x&1 && y&1) z^=1;
        if(z == 0){
            disj.uni(x,y+n);
            disj.uni(x+n+m,y+n+n+m);
        }
        else{
            disj.uni(x+n+m,y+n);
            disj.uni(x,y+n+n+m);
        }
    }
    int res = 0;
    for (int i=1; i<=n+m; i++) {
        if(disj.find(i) == disj.find(n+m+i)){
            printf("0");
            return 0;
        }
    }
    for (int i=1; i<=2*(n+m); i++) {
        if(!vis[disj.find(i)]){
            vis[disj.find(i)] = 1;
            res++;
        }
    }
    res /= 2;
    res--;
    long long ret = 1, piv = 2, mod = 1e9;
    while (res) {
        if(res & 1) ret *= piv;
        piv *= piv;
        ret %= mod;
        piv %= mod;
        res >>= 1;
    }
    printf("%lld",ret);
}