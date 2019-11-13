#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
const int MAXN = 300005;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<int, int>;

struct node{
	node *l, *r, *p, *pp;
	int sz, ppson;
	node(){ l = r = p = pp = NULL; sz = 1; ppson = 0; }
}*root;
void push(node *x){
	// if there's lazy stuff
}
void pull(node *x){
	x->sz = x->ppson + 1;
	if(x->l) x->sz += x->l->sz;
	if(x->r) x->sz += x->r->sz;
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
		x->ppson += x->r->sz;
		x->r->p = NULL;
		x->r = NULL;
	}
	pull(x);
	while(x->pp){
		node *nxt = x->pp;
		splay(nxt);
		push(nxt);
		if(nxt->r){
			nxt->ppson += nxt->r->sz;
			nxt->r->pp = nxt;
			nxt->r->p = NULL;
			nxt->r = NULL;
		}
		nxt->ppson -= x->sz;
		nxt->r = x;
		x->p = nxt;
		x->pp = NULL;
		pull(nxt);
		splay(x);
	}
}

void link(node *par, node *son){
	access(par);
	access(son);
//	son->rev ^= 1;  // remove if needed
	push(son);
	son->l = par;
	par->p = son;
	pull(son);
}

node *nd[MAXN];

char buf[69];
string s;
int fail[MAXN], ans[MAXN];

int main(){
	nd[0] = new node();
	int q; scanf("%d",&q);
	int p = 0;
	int last = 0;
	int piv = 0;
	while(q--){
		scanf("%s", buf);
		if(*buf == 'a'){
			scanf("%s", buf);
			int ch = *buf - 'a' + last;
			ch %= 26;
			ch += 'a';
			s.push_back(ch);
			while(p && ch != s[p]){
				p = fail[p];
			}
			if(sz(s) > 1 && ch == s[p]) p++;
			fail[sz(s)] = p;
			nd[sz(s)] = new node();
			link(nd[p], nd[sz(s)]);
		}
		else{
			int x; scanf("%d",&x);
			x = ((x - 1 + last) % sz(s)) + 1;
			access(nd[x]);
			printf("%d\n", last = nd[x]->ppson + 1);
		}
	}
}
