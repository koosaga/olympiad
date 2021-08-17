struct node{
	node *l, *r, *p;
	int x, le, ri, sub, sub_bad;
	node(){ 
	}
	node(int val){
		l = r = p = NULL;
		x = le = ri = val;
		sub = 1;
		sub_bad = 0;
	}
	void push(){

	}
	void pull(){
		le = ri = x;
		sub = 1;
		sub_bad = 0;
		if(l){
			le = l->le;
			sub += l->sub;
			sub_bad += l->sub_bad;
			if(l->ri <= x) sub_bad += 1;
		}
		if(r){
			ri = r->ri;
			sub += r->sub;
			sub_bad += r->sub_bad;
			if(x <= r->le) sub_bad += 1;
		}
	}
	void setLeft(node *p){
		l = p;
		if(p) p->p = this;
		pull();
	}
	void setRight(node *p){
		r = p;
		if(p) p->p = this;
		pull();
	}
	void rotate(){
		node *x = this;
		if(!x->p) return;
		x->p->push();
		x->push();
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
		p->pull();
		x->pull();
	}
	void splay(){
		node *x = this;
		while(x->p){
			node *p = x->p;
			node *g = p->p;
			if(g){
				if((p->l == x) ^ (g->l == p)) x->rotate();
				else p->rotate();
			}
			x->rotate();
		}
	}
	node* prev(){
		splay();
		if(!l) return NULL;
		auto prv = l;
		while(prv->r) prv = prv->r;
		prv->splay();
		return prv;
	}
	node* next(){
		splay();
		if(!r) return NULL;
		auto nxt = r;
		while(nxt->l) nxt = nxt->l;
		nxt->splay();
		return nxt;
	}
	void inorder(){
		if(l) l->inorder();
		if(l) assert(l->p == this);
		printf("%d ", x);
		if(r) r->inorder();
		if(r) assert(r->p == this);
	}
	node* kth(int k){ // returns new root: please assign to original root
		k--; // 1-based
		splay();
		assert(this->sub > k);
		node *p = this;
		while(true){
			p->push();
			while(p->l && p->l->sub > k){
				p = p->l;
				p->push();
			}
			if(p->l) k -= p->l->sub;
			if(k == 0) break;
			k--;
			p = p->r;
		}
		p->splay();
		return p;
	}
};

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
