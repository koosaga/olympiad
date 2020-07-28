// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ORDERSET/
#include <cstdio>
#include <cstdlib>
typedef struct node* pnode;
struct node{
	int key,prior,size;
	pnode l,r;
	node(int key) : key(key), prior(rand()), size(1), l(NULL), r(NULL) {}
};
int sz(pnode t){
	if(t == NULL) return 0;
	return t->size;
}
void upd_sz(pnode t){
	if(t == NULL) return;
	t->size = sz(t->l) + 1 + sz(t->r);
}
int find(pnode t,int key){
	if(t == NULL) return 0;
	if(t->key == key) return 1;
	if(key < t->key) return find(t->l,key);
	return find(t->r,key);
}
void split(pnode t, int key ,pnode &l,pnode &r){
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
//void insert(pnode &t,pnode it){
//	if(t == NULL) t = it;
//	else if(it->prior > t->prior){
//		split(t,it->key,it->l,it->r);
//		t = it;
//	}
//	else insert(it->key < t->key ? t->l : t->r,it);
//	upd_sz(t);
//}
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
//void erase(pnode &t,int key){
//	if(t->key == key) merge(t,t->l,t->r);
//	else erase(key < t->key ? t->l : t->r,key);
//	upd_sz(t);
//}
void erase_util(pnode &t,int key){
	pnode L,mid,R,aux1,aux2;
	split(t,key-1,L,R);
	split(R,key,aux1,aux2);
	merge(t,L,aux2);
}
void insert_util(pnode &t,int val){
	if(find(t,val)) return;
	pnode aux = new node(val);
	pnode L,R,temp;
	split(t,val-1,L,R);
	merge(temp,L,aux);
	merge(t,temp,R);
}
int kth(pnode t,int k){
	int davez = sz(t->l) + 1;
	if(davez == k) return t->key;
	if(k < davez) return kth(t->l,k);
	return kth(t->r,k - davez);
}
int cnt(pnode t,int key){
	if(t == NULL) return 0;
	if(t->key == key) return sz(t->l);
	if(t->key < key) return sz(t->l) + 1 + cnt(t->r,key);
	return cnt(t->l,key);
}
int main(){
	int Q;
	scanf("%d",&Q);
	pnode raiz = NULL;
	while(Q--){
		char op;
		int val;
		scanf(" %c %d",&op,&val);
		if(op == 'I') insert_util(raiz,val);
		if(op == 'D') erase_util(raiz,val);
		if(op == 'K'){
			if(val > sz(raiz)) printf("invalid\n");
			else printf("%d\n",kth(raiz,val));
		}
		if(op == 'C') printf("%d\n",cnt(raiz,val));
	}
	return 0;
}