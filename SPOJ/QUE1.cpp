// Ivan Carvalho
// Solution to https://www.spoj.com/problems/QUE1/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10010;
typedef pair<int,int> ii;
typedef struct node* pnode;
struct node{
	pnode l,r;
	int key,size,prior;
	node(int key) : l(NULL),r(NULL),key(key),size(1),prior(rand()) {}
};
inline int sz(pnode t){return t == NULL ? 0 : t->size;}
void upd_sz(pnode t){if(t) t->size = sz(t->l) + 1 + sz(t->r);}
void split(pnode t,pnode &l,pnode &r,int key){
	if(t == NULL){
		l = r = NULL;
	}
	else if(key < t->key){
		split(t->l,l,t->l,key);
		r = t;
	}
	else{
		split(t->r,t->r,r,key);
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
void insert(pnode &t,int key){
	pnode L,R,aux;
	aux = new node(key);
	split(t,L,R,key-1);
	merge(t,L,aux);
	merge(t,t,R);
}
void erase(pnode &t,int key){
	pnode L,mid,R;
	split(t,L,R,key-1);
	split(R,mid,R,key);
	merge(t,L,R);
}
int kth(pnode t,int count){
	int idx = sz(t->l) + 1;
	if(idx == count){
		return t->key;
	}
	else if(count < idx){
		return kth(t->l,count);
	}
	return kth(t->r,count - idx);
}
int TC,n,resposta[MAXN],v1[MAXN],v2[MAXN];
int main(){
	scanf("%d",&TC);
	while(TC--){
		scanf("%d",&n);
		for(int i = 1;i<=n;i++) scanf("%d",&v1[i]);
		for(int i = 1;i<=n;i++) scanf("%d",&v2[i]);
		vector<ii> pares;
		pnode raiz = NULL;
		for(int i = 1;i<=n;i++){
			pares.push_back(ii(v1[i],v2[i]));
			insert(raiz,i);
		}
		sort(pares.begin(),pares.end());
		for(int i = 0;i<n;i++){
			int a = pares[i].first,b = pares[i].second;
			b++;
			int resultado = kth(raiz,b);
			resposta[resultado] = a;
			erase(raiz,resultado);
		}
		for(int i = 1;i<=n;i++) printf("%d ",resposta[i]);
		printf("\n");
	}
	return 0;
}