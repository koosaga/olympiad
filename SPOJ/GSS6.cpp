// Ivan Carvalho
// Solution to https://www.spoj.com/problems/GSS6/
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef struct node* pnode;
struct kadane{
	int total,maximo_ini,maximo_fim,maximo;
};
struct node{
	pnode l,r;
	kadane puro,junto;
	int prior,size;
	node(int _puro){
		l = r = NULL;
		puro.total = puro.maximo_ini = puro.maximo_fim = puro.maximo = _puro;
		junto = puro;
		prior = rand();
		size = 1;
	}
};
kadane join(kadane a, kadane b){
	kadane resultado;
	resultado.total = a.total + b.total;
	resultado.maximo_ini = max(a.maximo_ini,a.total+b.maximo_ini);
	resultado.maximo_fim = max(b.maximo_fim,b.total+a.maximo_fim);
	resultado.maximo = max(max(a.maximo,b.maximo),a.maximo_fim+b.maximo_ini);
	return resultado;
}
int sz(pnode t){
	if(t == NULL) return 0;
	return t->size;
}
void upd_sz(pnode t){
	if(t == NULL) return;
	t->size = sz(t->l) + 1 + sz(t->r);
}
void operation(pnode t){
	if(t == NULL) return;
	if(t->l == NULL && t->r == NULL){
		t->junto = t->puro;
	}
	else if(t->l == NULL){
		t->junto = join(t->puro,t->r->junto);
	}
	else if(t->r == NULL){
		t->junto = join(t->l->junto,t->puro);
	}
	else{
		t->junto = join(t->l->junto,t->puro);
		t->junto = join(t->junto,t->r->junto);
	}
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
			split(t->r,key,add+sz(t->l)+1,t->r,r);
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
	split(R,key,sz(L),mid,R);
	merge(t,L,R);
}
int query(pnode &t,int a,int b){
	pnode L,R;
	split(t,a-1,0,L,R);
	split(R,b,sz(L),t,R);
	int resp = t->junto.maximo;
	merge(t,L,t);
	merge(t,t,R);
	return resp;
}
int main(){
	int N;
	scanf("%d",&N);
	pnode raiz = NULL;
	for(int i = 1;i<=N;i++){
		int davez;
		scanf("%d",&davez);
		insert(raiz,i,davez);
	}
	int Q;
	scanf("%d",&Q);
	while(Q--){
		char op;
		scanf(" %c",&op);
		if(op == 'I'){
			int x,y;
			scanf("%d %d",&x,&y);
			insert(raiz,x,y);
		}
		else if(op == 'D'){
			int x;
			scanf("%d",&x);
			erase(raiz,x);
		}
		else if(op == 'R'){
			int x,y;
			scanf("%d %d",&x,&y);
			erase(raiz,x);
			insert(raiz,x,y);
		}
		else if(op == 'Q'){
			int x,y;
			scanf("%d %d",&x,&y);
			printf("%d\n",query(raiz,x,y));
		}
	}
	return 0;
}