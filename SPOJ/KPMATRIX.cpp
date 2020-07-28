// Ivan Carvalho
// Solution to https://www.spoj.com/problems/KPMATRIX/
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
typedef struct node* pnode;
const int MAXN = 251;
int soma[MAXN][MAXN],matriz[MAXN][MAXN],N,M,A,B;
struct node{
	int prior,size;
	ii key;
	pnode l,r;
	node(ii key) : key(key),l(NULL),r(NULL),prior(rand()),size(1){} 
};
inline int sz(pnode t){return (t == NULL) ? 0 : t->size;}
inline void upd_sz(pnode t){if(t) t->size = sz(t->l) + 1 + sz(t->r);}
void split(pnode t,ii key,pnode &l,pnode &r){
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
//void merge(pnode &t,pnode l,pnode r){
//	if(l == NULL){
//		t = r;
//	}
//	else if(r == NULL){
//		t = l;
//	}
//	else if(l->prior > r->prior){
//		merge(l->r,l->r,r);
//		t = l;
//	}
//	else{
//		merge(r->l,l,r->l);
//		t = r;
//	}
//	upd_sz(t);
//}
//void insert(pnode &t,ii key){
//	pnode L,R;
//	pnode aux = new node(key);
//	split(t,MP(key.first-1,MAXN),L,R);
//	merge(t,L,aux);
//	merge(t,t,R);
//}
void insert(pnode &t,pnode it){
	if(t == NULL){
		t = it;
	}
	else if(it->prior > t->prior){
		split(t,it->key,it->l,it->r);
		t = it;
	}
	else{
		if(it->key < t->key) insert(t->l,it);
		else insert(t->r,it);
	}
	upd_sz(t);
}
void insert_util(pnode &raiz,ii key){
	pnode it = new node(key);
	insert(raiz,it);
}
int cnt(pnode t,ii key){
	if(t == NULL) return 0;
	if(t->key == key){return sz(t->l) + 1;}
	if(key < t->key){return cnt(t->l,key);}
	return sz(t->l) + 1 + cnt(t->r,key);
}
int main(){
	scanf("%d %d",&N,&M);
	for(int linha = 1;linha <= N;linha++){
		for(int coluna =1;coluna<=M;coluna++){
			scanf("%d",&matriz[linha][coluna]);
			soma[linha][coluna] = soma[linha][coluna-1] + matriz[linha][coluna];
		}
	}
	scanf("%d %d",&A,&B);
	int resp = 0;
	for(int coluna_ini = 1;coluna_ini<=M;coluna_ini++){
		for(int coluna_fim = coluna_ini;coluna_fim <= M;coluna_fim++){
			int davez = 0;
			pnode raiz = NULL;
			insert_util(raiz,MP(0,0));
			for(int linha = 1;linha <= N;linha++){
				davez += soma[linha][coluna_fim] - soma[linha][coluna_ini-1];
				resp += cnt(raiz,MP(davez - A,linha-1)) - cnt(raiz,MP(davez - B - 1,linha-1));
				insert_util(raiz,MP(davez,linha));
			}
		}
	}
	printf("%d\n",resp);
	return 0;
}