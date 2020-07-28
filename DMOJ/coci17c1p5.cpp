// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci17c1p5
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 1;
typedef struct node* pnode;

struct node{
	pnode l,r;
	int key,puro,junta,prior;
	node(int _key,int _puro) : l(NULL),r(NULL),key(_key),puro(_puro),junta(_puro),prior(rand() ^ (rand() << 16)){}
};

inline int jnt(pnode t){return t ? t->junta : INF;}

inline void update(pnode t){if(t) t->junta = min(min(jnt(t->l),t->puro),jnt(t->r));}

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
	
	update(t);

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
	
	update(t);

}

void insert(pnode &t,int key,int puro){
	pnode L,R;
	pnode aux = new node(key,puro);
	split(t,key,L,R);
	merge(t,L,aux);
	merge(t,t,R);
}

int find(pnode t,int y){
	if(jnt(t->l) <= y) return find(t->l,y);
	if(t->puro <= y) return t->key;
	return find(t->r,y);
}

int query(pnode &t,int y,int b){
	pnode L,R;
	split(t,b-1,L,R);
	int ret = -1;
	if(jnt(R) <= y) ret = find(R,y);
	merge(t,L,R);
	return ret; 
}

int main(){
	
	int N,M;
	pnode raiz = NULL;
	scanf("%d %d",&N,&M);
	
	while(M--){
	
		char op;
		scanf(" %c",&op);
		if(op == 'M'){
			int a,b;
			scanf("%d %d",&a,&b);
			insert(raiz,b,a);
		}
		else{
			int y,b;
			scanf("%d %d",&y,&b);
			printf("%d\n",query(raiz,y,b));
		}
	
	}
	
	return 0;

}