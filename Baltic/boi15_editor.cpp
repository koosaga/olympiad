#include <cstdio>
#include <algorithm>
using namespace std;
 
struct node{
    node *ls, *rs;
    int val;
    node(){
        ls = rs = NULL;
        val = 0;
    }
}*root[300005];
 
int n, r[300005];
 
void add(int pos, int ps, int pe, node* p, node *prev, int v){
    if(ps == pe) {
        p->val = max(p->val,v);
        return;
    }
    int pm = (ps + pe) / 2;
    if(pos <= pm){
        p->ls = new node();
        p->rs = prev->rs;
        add(pos, ps, pm, p->ls, prev->ls, v);
    }
    else{
        p->ls = prev->ls;
        p->rs = new node();
        add(pos, pm+1, pe, p->rs, prev->rs, v);
    }
    p->val = max(p->ls->val, p->rs->val);
}
 
void init(int ps, int pe, node *p){
    if(ps == pe) return;
    p->ls = new node();
    p->rs = new node();
    int pm = (ps + pe) / 2;
    init(ps, pm, p->ls);
    init(pm+1, pe, p->rs);
}
 
int query(int s, int e, int ps, int pe, node* p){
    if(e < ps || pe < s) return 0;
    if(s <= ps && pe <= e) return p->val;
    int pm = (ps + pe) / 2;
    return max(query(s,e,ps,pm,p->ls), query(s,e,pm+1,pe,p->rs));
}
 
int main(){
    scanf("%d",&n);
    for(int i=0; i<=n; i++){
        root[i] = new node();
    }
    init(0,n,root[0]);
    for(int i=1; i<=n; i++){
        int t;
        scanf("%d",&t);
        if(t > 0){
            add(0,0,n,root[i],root[i-1],i);
            r[i] = t;
        }
        else{
            int obj = query(0,-t-1,0,n,root[i-1]) - 1;
            add(-t,0,n,root[i],root[obj],i);
            r[i] = r[obj];
        }
        printf("%d\n",r[i]);
    }
}