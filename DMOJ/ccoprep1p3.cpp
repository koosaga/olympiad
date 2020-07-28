// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccoprep1p3
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;
typedef struct node* pnode;
const int MAXN = 100001;
vector<int> linear;
struct node{
	pnode l,r;
	int key,prior,size;
	node(int key) : key(key),size(1),prior(rand()),l(NULL),r(NULL){}
};
int sz(pnode t){return (t == NULL) ? 0 : t->size;}
void upd_sz(pnode t){if(t) t->size = sz(t->l) + 1 + sz(t->r);}
void split(pnode t, int key ,pnode &l,pnode &r){
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
void insert(pnode &t,int val){
	pnode aux = new node(val);
	pnode L,R;
	split(t,val-1,L,R);
	merge(t,L,aux);
	merge(t,t,R);
}
int kth(pnode t,int k){
	int davez = sz(t->l) + 1;
	if(davez == k) return t->key;
	if(k < davez) return kth(t->l,k);
	return kth(t->r,k - davez); 
}
void junta(pnode t){
	if(t == NULL) return;
	linear.push_back(t->key);
	junta(t->l);
	junta(t->r);
}
int pai[MAXN],peso[MAXN],ida[MAXN],volta[MAXN],n,q,iniciais;
pnode raizes[MAXN];
int find(int x){
	if(x == pai[x]) return x;
	return pai[x] = find(pai[x]);
}
void join(int x,int y){
	linear.clear();
	if(peso[x]<peso[y]){
		pai[x] = y;
		junta(raizes[x]);
		for(int i=0;i<linear.size();i++){
			insert(raizes[y],linear[i]);
		}
	}
	else if(peso[x] > peso[y]){
		pai[y] = x;
		junta(raizes[y]);
		for(int i=0;i<linear.size();i++){
			insert(raizes[x],linear[i]);
		}
	}
	else{
		peso[y]++;
		pai[x] = y;
		junta(raizes[x]);
		for(int i=0;i<linear.size();i++){
			insert(raizes[y],linear[i]);
		}
	}
}
int kth(int x,int k){
	if(k > sz(raizes[x])) return -1;
	return volta[kth(raizes[x],k)];
}
int main(){
	scanf("%d %d",&n,&iniciais);
	for(int i=1;i<=n;i++){
		scanf("%d",&ida[i]);
		volta[ida[i]] = i;
		pai[i] = i; 
		raizes[i] = new node(ida[i]);
	}
	while(iniciais--){
		int u,v;
		scanf("%d %d",&u,&v);
		u = find(u);
		v = find(v);
		if(u != v) join(u,v);
	}
	scanf("%d",&q);
	for(int vez=0;vez<q;vez++){
		char op;
		scanf(" %c",&op);
		if(op == 'Q'){
			int x,k;
			scanf("%d %d",&x,&k);
			printf("%d\n",kth(find(x),k));
		}
		else{
			int x,y;
			scanf("%d %d",&x,&y);
			x = find(x);
			y = find(y);
			if(x==y) continue;
			join(x,y);
		}
	}
	return 0;
}(y);
			if(x==y) continue;
			join(x,y);
		}
	}
	return 0;
}