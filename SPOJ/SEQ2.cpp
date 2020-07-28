// Ivan Carvalho
// Solution to https://www.spoj.com/problems/SEQ2/
#include <bits/stdc++.h>
using namespace std;
typedef struct node* pnode;
const int NEG = -1000;
struct soma_parcial{
	int prefix,sufix,total,best;
};
soma_parcial join(soma_parcial A,soma_parcial B){
	soma_parcial C;
	C.total = A.total + B.total;
	C.prefix = max(A.prefix,A.total + B.prefix);
	C.sufix = max(A.sufix + B.total,B.sufix);
	C.best = max(max(A.best,B.best), A.sufix + B.prefix );
	return C;
}
soma_parcial inverte(soma_parcial A){
	swap(A.prefix,A.sufix);
	return A;
}
struct node{
	pnode l,r;
	int prior,size,lazy_r,lazy_s,lazy_v;
	soma_parcial puro,conjunto;
	node(int _val){
		l = r = NULL;
		prior = (rand() ^ (rand() << 16));
		size = 1;
		lazy_r = lazy_v = lazy_s = 0;
		puro.best = puro.prefix = puro.sufix = puro.total = _val;
		conjunto.best = conjunto.prefix = conjunto.sufix = conjunto.total = _val;
	}
};
inline int sz(pnode t){return t ? t->size : 0;}
inline soma_parcial get_ps(pnode t){
	if(t->lazy_s){
		soma_parcial davez;
		davez.total = t->size * t->lazy_v;
		davez.prefix = davez.sufix = davez.best = max(t->lazy_v,t->size*t->lazy_v);
		return davez;
	}
	if(!t->lazy_r) return t->conjunto;
	return inverte(t->conjunto); 
}
void update(pnode t){
	if(!t) return;
	t->size = sz(t->l) + 1 + sz(t->r);
	t->conjunto = t->puro;
	if(t->l){
		t->conjunto = join(get_ps(t->l),t->puro);
	}
	if(t->r){
		t->conjunto = join(t->conjunto, get_ps(t->r) );
	}
}
void propagate(pnode t){
	if(!t) return;
	if(t->lazy_r){
		t->lazy_r = 0;
		swap(t->l,t->r);
		t->conjunto = inverte(t->conjunto);
		if(t->l) t->l->lazy_r ^= 1;
		if(t->r) t->r->lazy_r ^= 1;
	}
	if(t->lazy_s){
		t->lazy_s = 0;
		t->puro.prefix = t->puro.sufix = t->puro.total = t->puro.best = t->lazy_v;
		t->conjunto.total = t->lazy_v*t->size;
		t->conjunto.prefix = t->conjunto.sufix = t->conjunto.best = max(t->lazy_v,t->size*t->lazy_v);
		if(t->l){
			t->l->lazy_s = 1;
			t->l->lazy_v = t->lazy_v;
		}
		if(t->r){
			t->r->lazy_s = 1;
			t->r->lazy_v = t->lazy_v;
		}
	}
}
void split(pnode t,int key,int add,pnode &l,pnode &r){
	propagate(t);
	if(t == NULL){
		l = r = NULL;
	}
	else{
		int cur_key = sz(t->l) + add + 1;
		if(key < cur_key){
			split(t->l,key,add,l,t->l);
			r = t;
		}
		else{
			split(t->r,key,cur_key,t->r,r);
			l = t;
		}
	}
	update(t);
}
void merge(pnode &t,pnode l,pnode r){
	propagate(l);
	propagate(r);
	if(l == NULL){
		t = r ;
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
	update(t);
}
void insert(pnode &t,int a,pnode &aux){
	pnode L,R;
	split(t,a,0,L,R);
	merge(t,L,aux);
	merge(t,t,R);
}
void erase(pnode &t,int a,int b){
	if(a > b) return;
	pnode L,mid,R;
	split(t,a-1,0,L,R);
	split(R,b,sz(L),mid,R);
	merge(t,L,R);
}
void reverse(pnode &t,int a,int b){
	if(a > b) return;
	pnode L,mid,R;
	split(t,a-1,0,L,R);
	split(R,b,sz(L),mid,R);
	mid->lazy_r = 1;
	propagate(mid);
	merge(t,L,mid);
	merge(t,t,R);
}
void modify(pnode &t,int a,int b,int val){
	if(a > b) return;
	pnode L,mid,R;
	split(t,a-1,0,L,R);
	split(R,b,sz(L),mid,R);
	mid->lazy_s = 1;
	mid->lazy_v = val;
	propagate(mid);
	merge(t,L,mid);
	merge(t,t,R);
}
int get_sum(pnode &t,int a,int b){
	if(a > b) return 0;
	pnode L,mid,R;
	split(t,a-1,0,L,R);
	split(R,b,sz(L),mid,R);
	int ret = mid->conjunto.total;
	merge(t,L,mid);
	merge(t,t,R);
	return ret;
}
char entrada[100];
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){int n,q;
	pnode raiz = NULL;
	scanf("%d %d",&n,&q);
	for(int i = 1;i<=n;i++){
		int x;
		scanf("%d",&x);
		pnode aux = new node(x);
		merge(raiz,raiz,aux);
		//printf("%d\n",raiz->conjunto.best);
	}
	while(q--){
		scanf("%s",entrada);
		if(entrada[0] == 'I'){
			int posi,tot;
			scanf("%d %d",&posi,&tot);
			pnode lista = NULL;
			while(tot--){
				int x;
				scanf("%d",&x);
				pnode aux = new node(x);
				merge(lista,lista,aux);
			}
			insert(raiz,posi,lista);
		}
		else if(entrada[0] == 'D'){
			int posi,tot;
			scanf("%d %d",&posi,&tot);
			erase(raiz,posi,posi + tot - 1);
		}
		else if(entrada[0] == 'M' && entrada[2] == 'K'){
			int posi,tot,c;
			scanf("%d %d %d",&posi,&tot,&c);
			modify(raiz,posi,posi+tot-1,c);
		}
		else if(entrada[0] == 'R'){
			int posi,tot;
			scanf("%d %d",&posi,&tot);
			reverse(raiz,posi,posi + tot - 1);
		}
		else if(entrada[0] == 'G'){
			int posi,tot;
			scanf("%d %d",&posi,&tot);
			printf("%d\n",get_sum(raiz,posi,posi + tot - 1));
		}
		else{
			printf("%d\n",raiz->conjunto.best);
		}
	}
	}
	return 0;
}