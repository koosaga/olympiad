// Ivan Carvalho
// Solution to https://www.spoj.com/problems/KL11B/
#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))
using namespace std;
const int SZ = 5*1e5 + 2;
typedef pair<int,int> ii;
typedef struct node* pnode;
struct node{
	pnode l,r;
	ii key;
	int prior,size,height;
	node(ii _key) : l(NULL),r(NULL),key(_key),prior(rand() ^ (rand() << 16)),size(1){}
};
inline int sz(pnode t){return t ? t->size : 0;}
inline void update(pnode t){if(t) t->size = sz(t->l) + 1 + sz(t->r);}
void split(pnode t,ii key,pnode &l,pnode &r){
	if(t == NULL){
		l = r = NULL;
	}
	else{
		if(key < t->key){
			split(t->l,key,l,t->l);
			r = t;
		}
		else{
			split(t->r,key,t->r,r);
			l = t;
		}
	}
	update(t);
}
void insert(pnode &t,pnode aux){
	if(t == NULL){
		t = aux;
	}
	else{
		if(aux->prior > t->prior){
			split(t,aux->key,aux->l,aux->r);
			t = aux;
		}
		else{
			if(aux->key < t->key) insert(t->l,aux);
			else insert(t->r,aux);
		}
	}
	update(t);
}
void insert(pnode &t,ii key){
	pnode aux = new node(key);
	insert(t,aux);
}
int count(pnode &t,int key){
	if(t == NULL) return 0;
	if(t->key.first <= key) return sz(t->l) + 1 + count(t->r,key);
	return count(t->l,key);
}
vector<int> comp;
int n,e1[SZ],e2[SZ],e3[SZ],tam;
pnode bit[SZ];
void update_bit(int idx,ii novo){
	while(idx <= tam){
		insert(bit[idx],novo);
		idx += LSOne(idx);
	}
}
int read_bit(int idx,int g){
	int ans = 0;
	while(idx > 0){
		ans += sz(bit[idx]) - count(bit[idx],g-1);
		idx -= LSOne(idx);
	}
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i = 1;i<=n;i++){
		char op;
		int a,b;
		scanf(" %c %d %d",&op,&a,&b);
		e1[i] = (op == '+');
		e2[i] = a;
		e3[i] = b;
		comp.push_back(e2[i]);
	}
	sort(comp.begin(),comp.end());
	comp.erase(unique(comp.begin(),comp.end()),comp.end());
	tam = comp.size();
	for(int i = 1;i<=tam;i++){
		bit[i] = NULL;
	}
	for(int i = 1;i<=n;i++){
		e2[i] = lower_bound(comp.begin(),comp.end(),e2[i]) - comp.begin() + 1;
		//printf("%d %d %d\n",e1[i],e2[i],e3[i]);
		if(e1[i] == 1) update_bit(e2[i],ii(e3[i],i));
		else printf("%d\n",read_bit(e2[i],e3[i]));
	}
	return 0;
}