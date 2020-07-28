// Ivan Carvalho
// Solution to https://dmoj.ca/problem/acc1p1
#include <bits/stdc++.h>
using namespace std;

typedef struct node* pnode;

struct node{

	pnode l,r;
	int best,pref,suf,total,comp;
	int prior,size,val;
	bool flag;

	node(int _val = 0){
		l = r = NULL;
		best = pref = suf = total = comp = val = _val;
		prior = rand();
		size = 1;
		flag = false;
	}

};

void propagate(pnode t){
	
	if(t == NULL || !t->flag) return;

	t->flag = false;
	swap(t->suf,t->pref);
	swap(t->l,t->r);

	if(t->l) t->l->flag ^= true;
	if(t->r) t->r->flag ^= true;

}

inline int sz(pnode t){return t ? t->size : 0;}

inline void upd_sz(pnode t){if(t) t->size = sz(t->l) + 1 + sz(t->r);}

void upd_cont(pnode t){

	if(t == NULL) return;

	propagate(t->l);
	propagate(t->r);

	if(t->val == 0){
		t->best = max(t->l ? (t->l->best) : 0, t->r ? t->r->best 
: 0);
		t->pref = t->l ? t->l->pref : 0;
		t->suf = t->r ? t->r->suf : 0;
		t->comp = 0;
		t->total = (t->l ? t->l-> total : 0) + (t->r ? 
t->r->total : 0);
		return;
	}

	if(t->l && t->r){
		t->comp = t->l->comp && t->r->comp;
		t->total = (t->l->total) + 1 + (t->r->total);
		t->pref = max(t->l->pref,(t->l->comp)*(t->l->total + 1 + 
t->r->pref));
		t->suf = max(t->r->suf, (t->r->comp)*(t->r->total + 
t->val + t->l->suf));
		t->best = max(max(t->l->best,t->r->best), t->l->suf + 1 
+ t->r->pref );
	}
	else if(t->l){
		t->comp = t->l->comp;
		t->total = t->l->total + 1;
		t->pref = max(t->l->pref, t->l->comp*(t->l->total + 1) 
);
		t->suf = 1 + t->l->suf;
		t->best = max(t->l->best, 1 + t->l->suf );
	}
	else if(t->r){
		t->comp = t->r->comp;
		t->total = 1 + t->r->total;
		t->pref = 1 + t->r->pref;
		t->suf = max(t->r->suf,  t->r->comp*(t->r->total + 1));
		t->best = max(t->r->best, 1 + t->r->pref );
	}
	else{
		t->best = t->pref = t->suf = t->total = t->comp = 1;
	}

}

void split(pnode t,pnode &l, pnode &r, int key,int add){

	propagate(t);

	if(t == NULL){
		l = r = NULL;
		return;
	}

	int cur_key = sz(t->l) + add + 1;

	if(key < cur_key){
		split(t->l,l,t->l,key,add);
		r = t;
	}
	else{
		split(t->r,t->r,r,key,cur_key);
		l = t;
	}

	upd_sz(t);
	upd_cont(t);

}

void merge(pnode &t, pnode l, pnode r){
	
	propagate(l);
	propagate(r);

	if(l == NULL){
		t = r;
	}
	else if(r == NULL){
		t = l;
	}
	else if(l->prior > r->prior){
		merge(l->r,l->r,r);
		t = l;
	}
	else{
		merge(r->l,l,r->l);
		t = r;
	}

	upd_sz(t);
	upd_cont(t);

}

void reverse(pnode &t, int a,int b){

	pnode L,mid,R;

	split(t,L,R,a-1,0);
	split(R,mid,R,b,sz(L));

	mid->flag = true;

	merge(t,L,mid);
	merge(t,t,R);

}

int query(pnode &t,int a,int b){

	pnode L,mid,R;

	split(t,L,R,a-1,0);
	split(R,mid,R,b,sz(L));

	int ans = mid->best;

	merge(t,L,mid);
	merge(t,t,R);
	return ans;

}

int main(){

	int N,Q;
	scanf("%d %d",&N,&Q);

	pnode raiz = NULL;

	for(int i = 1;i<=N;i++){
		char c;
		scanf(" %c",&c);
		pnode novo = new node(c == '1');
		merge(raiz,raiz,novo);
	}

	while(Q--){
		int op,a,b;
		scanf("%d %d %d",&op,&a,&b);
		a++;
		if(op == 1){
			reverse(raiz,a,a+b-1);
		}
		else{
			printf("%d\n",query(raiz,a,a+b-1));
		}
	}

	return 0;

}
