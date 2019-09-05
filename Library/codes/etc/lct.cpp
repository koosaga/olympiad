struct node{
	node *l, *r, *p, *pp;
	node(){ l = r = p = pp = NULL; }
}*root;
void push(node *x){
	// if there's lazy stuff
}
void pull(node *x){

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
	if(p->pp){ // IF YOU ARE LINK CUT TREE
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
node *par(node *x){
	access(x);
	if(!x->l) return NULL;
	push(x);
	x = x->l;
	while(x->r){
		push(x);
		x = x->r;
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
void link(node *par, node *son){
	access(par);
	access(son);
	son->rev ^= 1;  // remove if needed
	push(son);
	son->l = par;
	par->p = son;
	pull(son);
}
void cut(node *p){
	access(p);
	push(p);
	if(p->l){
		p->l->p = NULL;
		p->l = NULL;
	}
	pull(p);
}
