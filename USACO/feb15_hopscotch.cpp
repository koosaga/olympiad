#include <cstdio>
 
const int mod = 1e9 + 7;
 
struct node{
    node(){
        v = 0;
        ls = rs = NULL;
    }
    int v;
    node *ls, *rs;
}*root[751*751];
 
void add(int s, int e, int x, int v, node* p){
    if(s == e){
        p->v += v;
        p->v %= mod;
        return;
    }
    int m = (s+e)/2;
    if(x <= m){
        if(!p->ls) p->ls = new node();
        add(s,m,x,v,p->ls);
        p->v += v;
        p->v %= mod;
    }
    else{
        if(!p->rs) p->rs = new node();
        add(m+1,e,x,v,p->rs);
        p->v += v;
        p->v %= mod;
    }
}
 
int sum(int s, int e, int x, node *p){
    if(x == e) return p->v;
    int m = (s+e)/2;
    if(x > m){
        int ret = 0;
        if(p->ls) ret += p->ls->v;
        if(p->rs) ret += sum(m+1,e,x,p->rs);
        return ret % mod;
    }
    if(!p->ls) return 0;
    return sum(s,m,x,p->ls);
}
 
int n,m,a[751][751], gap[751][751];
long long s[751][751];
 
int main(){
    int k;
    scanf("%d %d %d",&n,&m,&k);
    for(int i=1; i<=k; i++) root[i] = new node();
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            scanf("%d",&a[i][j]);
        }
    }
    gap[1][1] = 1;
    for (int i=1; i<=m; i++) {
        s[1][i] = 1;
    }
    add(1,m,1,1,root[a[1][1]]);
    for (int i=2; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            gap[i][j] = (int)s[i-1][j-1];
            if(j >= 2) gap[i][j] += mod - sum(1,m,j-1,root[a[i][j]]);
            gap[i][j] %= mod;
            s[i][j] = 1ll * gap[i][j] + s[i][j-1] + s[i-1][j] - s[i-1][j-1] + mod;
            s[i][j] %= mod;
        }
        for (int j=1; j<=m; j++) {
            add(1,m,j,gap[i][j],root[a[i][j]]);
        }
    }
    printf("%d",gap[n][m]);
}