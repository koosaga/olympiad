// Ivan Carvalho
// Solution to https://www.spoj.com/problems/AROPE/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100010;
char entrada[MAXN];
int n,m;
typedef struct node* pnode;
struct node{
	pnode l,r;
	char letter;
	int size,prior;
	node(char letter) : l(NULL),r(NULL),letter(letter),size(1),prior(rand()){}
};
inline int sz(pnode t){return t ? t->size : 0;}
inline void upd_sz(pnode t){if(t) t->size = sz(t->l) + 1 + sz(t->r);}
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
			split(t->r,key,add + sz(t->l) + 1,t->r,r);
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
void splice(pnode &t,int a,int b,int front){
	pnode L,mid,R;
	split(t,a-1,0,L,R);
	split(R,b,sz(L),mid,R);
	merge(t,L,R);
	if(front == 1) merge(t,mid,t);
	else merge(t,t,mid);
}
char kth(pnode t,int add,int count){
	int cur_key = sz(t->l) + add + 1;
	if(cur_key == count) return t->letter;
	if(count < cur_key){
		return kth(t->l,add,count);
	}
	return kth(t->r,add + sz(t->l) + 1,count);
}
int main(){
	scanf("%s",entrada);
	n = strlen(entrada);
	scanf("%d",&m);
	pnode raiz = NULL;
	for(int i = 0;i<n;i++){
		char c = entrada[i];
		pnode aux = new node(c);
		merge(raiz,raiz,aux);
	}
	while(m--){
		int op;
		scanf("%d",&op);
		if(op == 1){
			int x,y;
			scanf("%d %d",&x,&y);
			splice(raiz,x+1,y+1,1);
		}
		else if(op == 2){
			int x,y;
			scanf("%d %d",&x,&y);
			splice(raiz,x+1,y+1,0);
		}
		else{
			int x;
			scanf("%d",&x);
			x++;
			printf("%c\n",kth(raiz,0,x));
		}
	}
	return 0;
}