// Ivan Carvalho
// Solution to https://www.spoj.com/problems/CERC07S/
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#define MP make_pair
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
typedef struct node* pnode;
typedef pair<int,int> ii;
const int LIMIT = 1e9 + 10;
const ii INF = MP(LIMIT,LIMIT);
struct node{
	int prior,size,rev;
	ii val,minimo;
	pnode l,r;
	node(ii val) : val(val),minimo(val),size(1),prior(rand()),rev(0),l(NULL),r(NULL) {}
};
inline int sz(pnode t){return (t == NULL) ? 0 : t->size;}
inline void upd_sz(pnode t){if(t) t->size = sz(t->l) + 1 + sz(t->r);}
inline ii mn(pnode t){return (t == NULL) ? INF : t->minimo;}
inline void operation(pnode t){if(t) t->minimo = min(min(mn(t->l),mn(t->r)),t->val);}
inline void push(pnode &t){
	if(t && t->rev){
		t->rev = 0;
		swap(t->l,t->r);
		if(t->l) t->l->rev ^= 1;
		if(t->r) t->r->rev ^= 1;
	}
}
void split(pnode t,int key,int add,pnode &l,pnode &r){
	if(t == NULL){
		l = r = NULL;
	}
	else{
		push(t);
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
	push(l);
	push(r);
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
void insert(pnode &t,int key,ii val){
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
void reverse(pnode &t,int a,int b){
	pnode L,mid,R;
	split(t,a-1,0,L,R);
	split(R,b,sz(L),mid,R);
	mid->rev = 1;
	merge(t,L,mid);
	merge(t,t,R);
}
int search(pnode t,int add,ii val){
	push(t);
	if(mn(t->l) == val){
		return search(t->l,add,val);
	}
	int cur_key = sz(t->l) + add + 1;
	if(t->val == val) return cur_key;
	return search(t->r,add+sz(t->l)+1,val);
}
int query(pnode t,int a,int b,ii val){
	pnode L,mid,R;
	split(t,a-1,0,L,R);
	split(R,b,sz(L),mid,R);
	int ans = search(mid,sz(L),val);
	merge(t,L,mid);
	merge(t,t,R);
	return ans;
}
int main(){
	int n;
	while(scanf("%d",&n) && n){
		vector<ii> entrada;
		pnode raiz = NULL;
		for(int i=1;i<=n;i++){
			int davez;
			getint(davez);
			entrada.push_back(MP(davez,i));
			insert(raiz,i,MP(davez,i));
		}
		sort(entrada.begin(),entrada.end());
		for(int i=1;i<=n;i++){
			int inverte = query(raiz,i,n,entrada[i-1]);
			printf("%d ",inverte);
			reverse(raiz,i,inverte);
		}
		printf("\n");
	}
	return 0;
} 