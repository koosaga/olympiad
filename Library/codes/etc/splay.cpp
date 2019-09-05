struct node{
	node *l, *r, *p; 
	node(){ l = r = p = NULL; }
}*root;
void push(node *x){
	// if there's lazy stuff
}
void pull(node *x){
	x->sub = 1;
//	x->dat = node_data(x->val);
	if(x->l){
		x->sub += x->l->sub;
//		x->dat = x->l->dat + x->dat;
	}
	if(x->r){
		x->sub += x->r->sub;
//		x->dat = x->dat + x->r->dat;
	}
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
	if(!x->p) root = x;
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

void kth(int k){ 
	k--; // 1-based
	node *x = root;
	while(true){
		push(x);
		while(x->l && x->l->sub > k){
			x = x->l;
			push(x);
		}
		if(x->l) k -= x->l->sub;
		if(k == 0) break;
		k--;
		x = x->r;
	}
	splay(x);
}

node* split(int l, int r){ // if you modify sth : please climb up the tree to pull
	if(r == root->sub){
		if(l == 1) return root;
		kth(l - 1);
		return root->r;
	}
	kth(r + 1);
	push(root);
	node *tmp = root;
	root->l->p = NULL;
	root = root->l;
	if(l != 1) kth(l - 1);
	tmp->l = root;
	root->p = tmp;
	root = tmp;
	pull(root);
	if(l != 1) return root->l->r;
	return root->l;
}

void add(int x, int v){ // assume tree is nonempty!!
	if(!root){
		root = new node(v);
		return;
	}
	if(x == root->sub + 1){
		kth(x - 1);
		root->r = new node(v);
		root->r->p = root;
		pull(root);
	}
	else{
		kth(x);
		push(root);
		node *nxt = new node(v);
		nxt->l = root->l;
		if(root->l) root->l->p = nxt;
		pull(nxt);
		nxt->p = root;
		root->l = nxt;
		pull(root);
	}
}

void del(int x){ // not tested very well
	if(root->sub == 1){
		root = NULL;
		return;
	}
	kth(x);
	push(root);
	if(x == 1){
		root = root->r;
		root->p = NULL;
		return;
	}
	if(x == root->sub){
		root = root->l;
		root->p = NULL;
		return;
	}
	root->r->p = NULL;
	root->l->p = NULL;
	node *R = root->r;
	root = root->l; 
	node *p = root;
	push(p);
	while(p->r){
		p = p->r;
		push(p);
	}
	splay(p);
	push(root);
	root->r = R;
	R->p = root;
	pull(root);
}
