#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
const int MAXN = 1000005;
typedef long long lint;

struct lct{
	struct node{
		node *p, *l, *r, *pp;
		int lazy, idx;
		node(int _idx){
			p = l = r = pp = NULL;
			lazy = 0;
			idx = _idx;
		}
	}*n[MAXN];
	void init(int v){
		for(int i=1; i<=v; i++) n[i] = new node(i);
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
			push(x);
		}
	}
	node *root(node *x){
		access(x);
		while(x->l){
			push(x);
			x = x->l;
		}
		push(x);
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
	void cut(int x, int y){
		if(lca(n[x], n[y])->idx == y) swap(x, y);
		node *p = n[y];
		access(p);
		push(p);
		p->l->p = NULL;
		p->l = NULL;
		pull(p);
	}
}lct;

int n, q, mng[1000005];

int main(){
	scanf("%d %d",&n,&q);
	lct.init(n);
	while(q--){
		int t; scanf("%d",&t);
		if(t == 1){
			int s, e;
			scanf("%d %d",&s,&e);
			if(lct.link(e, s)) mng[s] = e;
		}
		if(t == 2){
			int s;
			scanf("%d",&s);
			lct.cut(s, mng[s]);
		}
		if(t == 3){
			int s, e;
			scanf("%d %d",&s,&e);
			if(lct.root(lct.n[s]) != lct.root(lct.n[e])) puts("-1");
			else printf("%d\n", lct.lca(lct.n[s], lct.n[e])->idx);
		}
	}
}
