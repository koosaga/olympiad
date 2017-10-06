#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
const int MAXN = 30005;
typedef long long lint;

struct lct{
    struct node{
        node *p, *l, *r, *pp;
        int cnt, sum, lazy;
        node(){
            p = l = r = pp = NULL;
            cnt = sum = lazy = 0;
        }
    }*n[MAXN];
    void init(int v){
        for(int i=1; i<=v; i++) n[i] = new node();
    }
    void push(node *p){
        if(p->lazy){
            swap(p->l, p->r);
            if(p->l) p->l->lazy ^= 1;
            if(p->r) p->r->lazy ^= 1;
            p->lazy = 0;
        }
    }
    void pull(node *p){
        p->sum = p->cnt + (p->l ? p->l->sum : 0) + (p->r ? p->r->sum : 0);
    }
    void rotate(node *x){
        if(!x->p) return;
        push(x->p);  // if there's lazy stuff
        push(x);
        node *p = x->p;
        bool is_left = (p->l == x);
        node *b = (is_left ? x->r : x->l);
        x->p = p->p;
        if(x->p && x->p->l == p) x->p->l = x;
        if(x->p && x->p->r == p) x->p->r = x;
        if(is_left){
            if(b) b->p = p;
            p->l = b;
            p->p = x;
            x->r = p;
        }
        else{
            if(b) b->p = p;
            p->r = b;
            p->p = x;
            x->l = p;
        }
        pull(p); // if there's something to pull up
        pull(x);
        if(p->pp){
            x->pp = p->pp;
            p->pp = NULL;
        }
    }
    void splay(node *x){
        while(x->p){
            node *p = x->p;
            node *g = p->p;
            if(g){
                if((p->l == x) ^ (g->l == p)) rotate(x);
                else rotate(p);
            }
            rotate(x);
        }
    }
    void access(node *x){
        splay(x);
        push(x);
        if(x->r){
            x->r->pp = x;
            x->r->p = NULL;
            x->r = NULL;
        }
        pull(x);
        while(x->pp){
            node *nxt = x->pp;
            splay(nxt);
            push(nxt);
            if(nxt->r){
                nxt->r->pp = nxt;
                nxt->r->p = NULL;
                nxt->r = NULL;
            }
            nxt->r = x;
            x->p = nxt;
            x->pp = NULL;
            pull(nxt);
            splay(x);
        }
    }
    node *root(node *x){
        access(x);
        while(x->l){
            push(x);
            x = x->l;
        }
        access(x);
        return x;
    }
    node *lca(node *s, node *t){
        access(s);
        access(t);
        splay(s);
        if(s->pp == NULL) return s;
        return s->pp;
    }
    bool link(int s, int e){
        node *par = n[s];
        node *son = n[e];
        if(root(par) == root(son)) return 0;
        access(par);
        access(son);
        son->lazy ^= 1;
        push(son);
        son->l = par;
        par->p = son;
        pull(son);
        return 1;
    }
    void update(int x, int v){
        access(n[x]);
        n[x]->cnt = v;
        pull(n[x]);
    }
    int query(int s, int e){
        if(root(n[s]) != root(n[e])) return -1;
        access(n[s]);
        int ans = n[s]->sum;
        access(n[e]);
        ans += n[e]->sum;
        node *p = lca(n[s], n[e]);
        access(p);
        ans -= 2 * p->sum;
        ans += p->cnt;
        return ans;
    }
}lct;

int n;

int main(){
    scanf("%d",&n);
    lct.init(n);
    for(int i=1; i<=n; i++){
        int x;
        scanf("%d",&x);
        lct.update(i, x);
    }
    int q; scanf("%d",&q);
    while(q--){
        char buf[20];
        scanf("%s", buf);
        if(*buf == 'b'){
            int x, y;
            scanf("%d %d",&x,&y);
            if(lct.link(x, y)) puts("yes");
            else puts("no");
        }
        if(*buf == 'p'){
            int x, v;
            scanf("%d %d",&x,&v);
            lct.update(x, v);
        }
        if(*buf == 'e'){
            int x, y;
            scanf("%d %d",&x,&y);
            int v = lct.query(x, y);
            if(v < 0) puts("impossible");
            else printf("%d\n", v);
        }
    }
}
