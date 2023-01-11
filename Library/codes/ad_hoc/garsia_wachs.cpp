#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;

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
	node* find_RM_pair(){
		node *p = this;
		while(true){
			assert(p);
			assert(p->sub_bad);
			if(p->l && p->l->sub_bad){
				p = p->l;
				continue;
			}
			if(p->l && (p->l->ri <= p->x)){
				p = p->prev();
				break;
			}
			if(p->r && (p->x <= p->r->le)){
				break;
			}
			p = p->r;
		}
		p->splay();
		return p;
	}
	node* search_geq(int val){
		node *p = this;
		while(true){
			if(p->r && p->r->le >= val){
				p = p->r;
				continue;
			}
			if(p->x >= val) break;
			p = p->l;
		}
		p->splay();
		return p;
	}
};

int main(){
	int tc; scanf("%d",&tc);
	while(tc--){
		int n;
		scanf("%d",&n);
		vector<int> a(n + 5);
		for(int i=2; i<=n+1; i++) scanf("%d",&a[i]);
		a[0] = a[1] = a[n+2] = a[n+3] = a[n+4] = 2.1e9;
		vector<node*> nd = {NULL, NULL};
		for(int i=0; i<sz(a); i++){
			node* foo = new node(a[i]);
			if(i >= 2) foo->setLeft(nd[i % 2]);
			nd[i % 2] = foo;
		}
		lint ret = 0;
		for(int i=0; i<n-1; i++){
			// find and erase
			auto swapRight = [&](){
				swap(nd[0]->r, nd[1]->r);
				nd[0]->r->p = nd[0];
				nd[1]->r->p = nd[1];
				nd[0]->pull();
				nd[1]->pull();
			};
			int val = -1;
			{
				node *fst = nd[0] = nd[0]->find_RM_pair();
				node *snd = nd[1] = nd[1]->find_RM_pair();
				int lsz = (fst->l ? fst->l->sub : 0);
				int rsz = (snd->l ? snd->l->sub : 0);
				int pivot = -1;
				//cout << lsz << " " << rsz << endl;
				if(lsz <= rsz){
					nd[1] = nd[1]->kth(lsz + 1);
					pivot = 0;
				}
				else{
					nd[0] = nd[0]->kth(rsz + 2);
					pivot = 1;
				}
				nd[pivot]->x += nd[pivot ^ 1]->x;
				val = nd[pivot]->x;
				ret += val;
				for(int i=0; i<2; i++){
					node *sep = nd[i]->r;
					assert(sep);
					sep->p = NULL;
					nd[i]->setRight(NULL);
					while(sep->l) sep = sep->l;
					sep->splay();
					sep->setLeft(nd[i]->l);
					nd[i] = sep;
				//	nd[i]->l->inorder(); cout << endl;
				}
			}
		//	cout << val << endl;
			{
				assert(nd[0]->l);
				assert(nd[1]->l);
				node *fst = nd[0] = nd[0]->l->search_geq(val);
				node *snd = nd[1] = nd[1]->l->search_geq(val);
				int lsz = (fst->l ? fst->l->sub : 0);
				int rsz = (snd->l ? snd->l->sub : 0);
				node *ins = new node(val);
				if(lsz > rsz){
					nd[0] = nd[0]->kth(lsz + 1);
					nd[1] = nd[1]->kth(lsz + 1);
					ins->setLeft(nd[1]->l);
					nd[1]->setLeft(ins);
					ins->splay();
					nd[1] = ins;
				}
				else{
					nd[0] = nd[0]->kth(rsz + 2);
					nd[1] = nd[1]->kth(rsz + 1);
					ins->setLeft(nd[0]->l);
					nd[0]->setLeft(ins);
					ins->splay();
					nd[0] = ins;
				}
				swapRight();
			//	nd[0]->inorder(); cout << endl;
			//	nd[1]->inorder(); cout << endl;
			}
		}
		printf("%lld\n", ret);
	}
}
