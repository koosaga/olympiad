// Ivan Carvalho
// Solution to https://www.spoj.com/problems/TWIST/
#include <bits/stdc++.h>
using namespace std;
random_device rd;
mt19937 gen(rd());
typedef struct node* pnode;
struct node{
	pnode l,r;
	int val,size,prior,rev;
	node(int val) : l(NULL),r(NULL),val(val),size(1),prior(gen()),rev(0){}
};
inline int sz(pnode t){return (t) ? t->size : 0;}
inline void upd_sz(pnode t){if(t) t->size = sz(t->l) + 1 + sz(t->r);}
inline void push(pnode &t){
	if(t && t->rev){
		swap(t->l,t->r);
		if(t->l) t->l->rev ^= 1;
		if(t->r) t->r->rev ^= 1;
		t->rev = 0;
	}
}
void split(pnode t,int key,int add,pnode &l,pnode &r){
	push(t);
	if(t == NULL){l = r = NULL;}
	else{
		int cur_key = add + sz(t->l) + 1;
		if(key < cur_key){
			split(t->l,key,add,l,t->l);
			r = t;
		}
		else{
			split(t->r,key,add + sz(t->l) + 1,t->r,r);
			l = t;
		}
	}
	upd_sz(t);
}
void merge(pnode &t,pnode l,pnode r){
	push(l);
	push(r);
	if(l == NULL){t = r;}
	else if(r == NULL){t = l;}
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
void reverse(pnode &t,int a,int b){
	pnode L,mid,R;
	split(t,a-1,0,L,R);
	split(R,b,sz(L),mid,R);
	mid->rev = 1;
	merge(t,L,mid);
	merge(t,t,R);	
}
int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	pnode raiz = NULL;
	for(int i=1;i<=n;i++){
		pnode aux = new node(i);
		merge(raiz,raiz,aux);
	}	
	for(int i=1;i<=m;i++){
		int a,b;
		scanf("%d %d",&a,&b);
		reverse(raiz,a,b);
	}
	for(int i=1;i<=n;i++){
		pnode aux;
		split(raiz,i,i-1,aux,raiz);
		printf("%d ",aux->val);
	}
	printf("\n");
	return 0;
}