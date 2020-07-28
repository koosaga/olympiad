// Ivan Carvalho
// Solution to https://www.spoj.com/problems/QMAX3VN/
#include <cstdio>
#include <algorithm>
#include <cstdlib>
using namespace std;
const int NEG = -(1e9 + 1);
typedef struct node* pnode;
struct node{
	int size,prior,puro,maximo;
	pnode l,r;
	node(int puro) : puro(puro) , maximo(puro), l(NULL), r(NULL) , prior(rand()), size(1) {}
};
int sz(pnode t){
	if(t == NULL) return 0;
	return t->size;
}
void upd_sz(pnode t){
	if(t == NULL) return;
	t->size = sz(t->l) + 1 + sz(t->r);
}
int mx(pnode t){
	if(t == NULL) return NEG;
	return t->maximo;
}
void operation(pnode t){
	if(t == NULL) return;
	t->maximo = max(max(mx(t->l),mx(t->r)),t->puro);
}
void split(pnode t,int key,int add,pnode &l,pnode &r){
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
			split(t->r,key,add+sz(t->l) + 1,t->r,r);
			l = t;
		}
	}
	upd_sz(t);
	operation(t);
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
	operation(t);
}
void insert(pnode &t,int key,int val){
	pnode L,R;
	pnode aux = new node(val);
	split(t,key-1,0,L,R);
	merge(t,L,aux);
	merge(t,t,R);
}
void erase(pnode &t,int key){
	pnode L,mid,R;
	split(t,key-1,0,L,R);
	split(t,key,sz(L),mid,R);
	merge(t,L,R);
}
int query(pnode &t,int a,int b){
	pnode L,R;
	split(t,a-1,0,L,R);
	split(R,b,sz(L),t,R);
	int ans = t->maximo;
	merge(t,L,t);
	merge(t,t,R);
	return ans;
}
int main(){
	int n;
	scanf("%d",&n);
	pnode raiz = NULL;
	while(n--){
		char op;
		scanf(" %c",&op);
		if(op == 'A'){
			int davez,pos;
			scanf("%d %d",&davez,&pos);
			insert(raiz,pos,davez);
		}
		else{
			int a,b;
			scanf("%d %d",&a,&b);
			printf("%d\n",query(raiz,a,b));
		}
	}
	return 0;
}