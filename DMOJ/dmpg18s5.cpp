// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmpg18s5
#include <bits/stdc++.h>
using namespace std;
typedef struct node* pnode;
struct node{
	pnode l,r;
	int key,prior,size;
	node (int _key) :l(NULL),r(NULL), key(_key),prior(rand()),size(1){}
};
inline int sz(pnode t){return t ? t->size : 0;}
inline void upd_sz(pnode t){
	if(t) t->size = sz(t->l) + 1 + sz(t->r);
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
	if(l == NULL) t = r;
	else if(r == NULL) t = l;
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
void insert(pnode &t,pnode aux){
	if(t == NULL){
		t = aux;
		upd_sz(t);
		return;
	}
	if(aux->prior > t->prior){
		split(t,aux->key,aux->l,aux->r);
		t = aux;
		upd_sz(t);
		return;
	}
	else{
		if(aux->key < t->key) insert(t->l,aux);
		else insert(t->r,aux);
		upd_sz(t);
		return;
	}
}
void insert_aux(pnode &t,int key){
	pnode aux = new node(key);
	insert(t,aux);
}
void erase(pnode &t,int key){
	if(t->key == key){
		merge(t,t->l,t->r);
		return;
	}
	if(key < t->key) erase(t->l,key);
	else erase(t->r,key);
	upd_sz(t);
}
int conta(pnode &t,int a,int b){
	pnode L,mid,R;
	split(t,a-1,L,R);
	split(R,b,mid,R);
	int ans = sz(mid);
	merge(t,L,mid);
	merge(t,t,R);
	return ans;
}
const int MAXN = 2*1e5 + 10;
int N,Q,vetor[MAXN],existiu[MAXN],op[MAXN],A[MAXN],B[MAXN],C[MAXN];
vector<int> divisores[MAXN];
pnode raizes[MAXN];
int main(){
	scanf("%d %d",&N,&Q);
	for(int i = 1;i<=N;i++){
		scanf("%d",&vetor[i]);
	}
	for(int i = 1;i<=Q;i++){
		scanf("%d",&op[i]);
		if(op[i] == 1){
			scanf("%d %d %d",&A[i],&B[i],&C[i]);
			existiu[C[i]]++;
		}
		else{
			scanf("%d %d",&A[i],&B[i]);
		}
	}
	for(int i = 1;i<MAXN;i++){
		if(existiu[i] == 0) continue;
		for(int j = i;j<MAXN;j+=i){
			divisores[j].push_back(i);
		}
	}
	for(int i = 1;i<=N;i++){
		for(int d : divisores[vetor[i]]){
			insert_aux(raizes[d],i);
		}
	}
	for(int i = 1;i<=Q;i++){
		if(op[i] == 1){
			printf("%d\n",conta(raizes[C[i]],A[i],B[i]));
		}
		else{
			for(int d : divisores[vetor[A[i]]]){
				erase(raizes[d],A[i]);
			}
			vetor[A[i]] = B[i];
			for(int d : divisores[vetor[A[i]]]){
				insert_aux(raizes[d],A[i]);
			}
		}
	}
	return 0;
}
