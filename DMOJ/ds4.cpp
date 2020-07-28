// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ds4
#include <cstdio>
#include <cstdlib>
typedef struct node* pnode;
struct node{
	pnode l,r;
	int key,size,prior;
	node(int key) : key(key),size(1),prior(rand()),l(NULL),r(NULL) {}
};
int sz(pnode t){
	if(t == NULL) return 0;
	return t->size;	
}
void upd_sz(pnode t){
	if(t) t->size = sz(t->l)+1+sz(t->r);
}
void split(pnode t,int key,pnode &l,pnode &r){
	if(t == NULL){
		l = r = NULL;
	}
	else if(key < t->key){
		split(t->l,key,l,t->l);
		r = t;
	}
	else{
		split(t->r,key,t->r,r);
		l = t;
	}
	upd_sz(t);
}
void merge(pnode &t,pnode l,pnode r){
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
}
int find(pnode t,int key){
	if(t == NULL) return 0;
	if(t->key == key) return 1;
	if(key < t->key) return find(t->l,key);
	return find(t->r,key);
}
void insert(pnode &t,int key){
	pnode L,R;
	pnode aux = new node(key);
	split(t,key-1,L,R);
	merge(t,L,aux);
	merge(t,t,R);
}
void erase(pnode &t,int key){
	if(!find(t,key)) return;
	pnode L,mid,R;
	split(t,key-1,L,R);
	split(R,key,mid,R);
	merge(mid,mid->l,mid->r);
	merge(t,L,mid);
	merge(t,t,R);
}
int kth(pnode t,int k){
	if(sz(t->l) + 1 == k) return t->key;
	if(k < sz(t->l) + 1) return kth(t->l,k);
	return kth(t->r,k - sz(t->l) - 1);
}
int cnt(pnode &t,int key){
	if(!find(t,key)) return -1;
	pnode L,R;
	split(t,key-1,L,R);
	int resp = sz(L)+1;
	merge(t,L,R);
	return resp;
}
void finaliza(pnode t){
	if(t == NULL) return;
	finaliza(t->l);
	printf("%d ",t->key);
	finaliza(t->r);
}
int main(){
	pnode raiz  = NULL;
	int n,m,last=0;
	scanf("%d %d",&n,&m);
	while(n--){
		int davez;
		scanf("%d",&davez);
		insert(raiz,davez);
	}
	while(m--){
		char op;
		int v;
		scanf(" %c %d",&op,&v);
		v ^= last;
		if(op == 'I'){
			insert(raiz,v);
		}
		else if(op == 'R'){
			erase(raiz,v);
		}
		else if(op == 'S'){
			last = kth(raiz,v);
			printf("%d\n",last);
		}
		else{
			last = cnt(raiz,v);
			printf("%d\n",last);
		}
	}
	finaliza(raiz);
	printf("\n");
	return 0;
};
		}
	}
	finaliza(raiz);
	printf("\n");
	return 0;
}