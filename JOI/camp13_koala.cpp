#include <cstdio>
#include <algorithm>
using namespace std;

int d,c,n;
int a[100005], b[100005];
long long dp[100005];

struct node{
    node() : ls(NULL), rs(NULL), max(-1e18) {}
    node *ls,*rs;
    long long max;
};

void add(int pos, long long x, int ps, int pe, node* p){
    if(ps == pe){
        p->max = max(p->max,x);
        return;
    }
    int pm = (ps+pe)/2;
    if(pos <= pm){
        if(!p->ls) p->ls = new node();
        add(pos,x,ps,pm,p->ls);
        p->max = max(p->max,p->ls->max);
    }
    else{
        if(!p->rs) p->rs = new node();
        add(pos,x,pm+1,pe,p->rs);
        p->max = max(p->max,p->rs->max);
    }
}

long long q(int s, int e, int ps, int pe, node* p){
    if(e < ps || pe < s) return -1e18;
    if(s <= ps && pe <= e) return p->max;
    long long ret = -1e18;
    int pm = (ps+pe)/2;
    if(p -> ls) ret = max(ret,q(s,e,ps,pm,p->ls));
    if(p -> rs) ret = max(ret,q(s,e,pm+1,pe,p->rs));
    return ret;
}

int main(){
    int s,e;
    node *root = new node();
    scanf("%d %d %d %d %d",&s,&e,&d,&c,&n);
    for (int i=1; i<=n; i++) {
        scanf("%d %d",&a[i],&b[i]);
        a[i] -= s;
    }
    a[n+1] = e-s;
    add(a[n+1]%d,-1ll * a[n+1] / d * c,0,d-1,root);
    for (int i=n; i>=0; i--) {
        dp[i] = max(q(0,a[i]%d,0,d-1,root),q(a[i]%d+1,d-1,0,d-1,root)-c);
        dp[i] += b[i];
        add(a[i]%d,dp[i],0,d-1,root);
    }
    printf("%lld",dp[0]);
}