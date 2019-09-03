#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct node{
	node *l, *r, *p;
	int maxv, sub, val, lazy;
	node(){
		l = r = p = NULL;
		lazy = 0;
		sub = 1; maxv = val = -1e9;
	}
}*root;

inline void push(node *x){
	if(x->l){
		x->l->lazy += x->lazy;
		x->l->maxv += x->lazy;
		x->l->val += x->lazy;
	}
	if(x->r){
		x->r->lazy += x->lazy;
		x->r->maxv += x->lazy;
		x->r->val += x->lazy;
	}
	x->lazy = 0;
}

void pull(node *x){
	x->sub = 1;
	x->maxv = x->val;
	if(x->l){
		x->maxv = max(x->maxv, x->l->maxv);
		x->sub += x->l->sub;
	}
	if(x->r){
		x->maxv = max(x->maxv, x->r->maxv);
		x->sub += x->r->sub;
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
	if(!x->p) root = x; // IF YOU ARE SPLAY TREE
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
	node *p = root;
	while(p){
		while(p->l && k < p->l->sub) p = p->l;
		if(p->l) k -= p->l->sub;
		if(k == 0){
			splay(p);
			return;
		}
		k--;
		p = p->r;
	}
	assert(0);
}

void insert_and_add(int pos, int val){
	kth(pos);
	node *nxt = new node();
	nxt->val = val;
	nxt->l = root->l;
	nxt->l->p = nxt;
	pull(nxt);
	root->l = NULL;
	root->lazy -= 1;
	root->maxv -= 1;
	root->val -= 1;
	push(root);
	nxt->p = root;
	root->l = nxt;
	pull(root);
}

int getmax(int pos){
	kth(pos);
	return root->l->maxv;
}

int main(){
	int n;
	scanf("%d",&n);
	root = new node();
	root->val = root->maxv = 0;
	for(int i=1; i<=n; i++){
		node* nxt = new node();
		nxt->l = root;
		nxt->val = nxt->maxv = -i;
		root->p = nxt;
		pull(nxt);
		root = nxt;
	}
	vector<pi> a(n + 1);
	for(int i=1; i<=n; i++) scanf("%d %d",&a[i].first,&a[i].second);
	int ret = 0;
	for(int i=n; i; i--){
		int pos = a[i].first + n - i;
		int curMax = max(0, getmax(pos) + pos) + a[i].second;
		insert_and_add(pos, curMax - pos);
		ret = max(ret, curMax);
	}
	cout << ret << endl;
}
