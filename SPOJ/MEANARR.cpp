// Ivan Carvalho
// Solution to https://www.spoj.com/problems/MEANARR/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef struct node* pnode;
struct node{
	pnode l,r;
	ll key,prior,size;
	node(ll key) : l(NULL),r(NULL),key(key),prior(rand()),size(1){}
};
inline ll sz(pnode t){return t == NULL ? 0 : t->size;}
inline void upd_sz(pnode t){if(t) t->size = sz(t->l) + 1 + sz(t->r);}
void split(pnode t,pnode &l,pnode &r,ll key){
	if(t == NULL){
		l = r = NULL;
	}
	else{
		if(key < t->key){
			split(t->l,l,t->l,key);
			r = t;
		}
		else{
			split(t->r,t->r,r,key);
			l = t;
		}
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
void insert(pnode &t,ll key){
	pnode L,R;
	pnode aux = new node(key);
	split(t,L,R,key-1);
	merge(t,L,aux);
	merge(t,t,R);
}
ll count(pnode &t,ll key){
	pnode L,R;
	split(t,L,R,key);
	ll resp = sz(L);
	merge(t,L,R);
	return resp;
}
int main(){
	ll N,K;
	scanf("%lld %lld",&N,&K);
	ll resp = 0,somatorio = 0;
	pnode raiz = new node(0LL);
	for(ll i = 0;i<N;i++){
		ll davez;
		scanf("%lld",&davez);
		davez -= K;
		somatorio += davez;
		resp += count(raiz,somatorio);
		insert(raiz,somatorio);
	}
	printf("%lld\n",resp);
	return 0;
}