#include <cstdio>
#include <algorithm>
int beyond[100005],n,m;
long long r;
int tree[550000],lim;
 
void add(int idx, int v){
    while (idx <= lim) {
        tree[idx]+=v;
        idx += idx & -idx;
    }
}
 
int sum(int idx){
    int res=0;
    while (idx) {
        res += tree[idx];
        idx -= idx & -idx;
    }
    return res;
}
 
int main(){
    int t;
    scanf("%d %d",&n,&m);
    for (lim = 1; lim<=3*n; lim<<=1);
    for (int i=1; i<=n; i++) {
        scanf("%d",&t);
        if(t>=m) beyond[i] = beyond[i-1]+1;
        else beyond[i] = beyond[i-1];
    }
    for (int i=0; i<=n; i++) {
        beyond[i]<<=1;
        beyond[i]+=n+1-i;
    }
    for (int i=0; i<=n; i++) {
        r += sum(beyond[i]);
        add(beyond[i],1);
    }
    printf("%lld",r);
}