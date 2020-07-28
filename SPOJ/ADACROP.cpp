// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADACROP/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 4*1e5 + 1;
typedef struct node* pnode;
struct node{
	int val;
	pnode l,r;
	node() : val(0),l(NULL),r(NULL){}
	void update(int left,int right,int x,int delta){
		if(left == right){
			val += delta;
			return;
		}
		val += delta;
		int mid = (left+right)/2;
		if(x <= mid){
			if(l == NULL) l = new node;
			l->update(left,mid,x,delta);
		}
		else{
			if(r == NULL) r = new node;
			r->update(mid+1,right,x,delta);
		}
	}
	int query(int left,int right,int i,int j){
		if(left >= i && right <= j){
			return val;
		}
		int mid = (left+right)/2;
		if(j <= mid){
			return (l == NULL) ? 0 : l->query(left,mid,i,j);
		}
		else if(i >= mid + 1){
			return (r == NULL) ? 0 : r->query(mid+1,right,i,j);
		}
		else{
			return ((l == NULL) ? 0 : l->query(left,mid,i,j)) + ((r == NULL) ? 0 : r->query(mid+1,right,i,j));
		}
	}
};
map<int,int> conversao;
int vetor[MAXN],n,q,ptr;
pnode raizes[MAXN];
int get_id(int x){
	if(conversao.count(x)) return conversao[x];
	conversao[x] = ++ptr;
	raizes[ptr] = new node;
	return conversao[x];
}
int main(){
	scanf("%d %d",&n,&q);
	for(int i = 1;i<=n;i++){
		int x;
		scanf("%d",&x);
		x = get_id(x);
		vetor[i] = x;
		raizes[x]->update(1,n,i,1);
	}
	for(int vez = 1;vez<=q;vez++){
		int idx,novo;
		scanf("%d %d",&idx,&novo);
		idx++;
		novo = get_id(novo);
		int velho = vetor[idx];
		raizes[velho]->update(1,n,idx,-1);
		printf("%d\n",raizes[novo]->query(1,n,1,idx));
		raizes[novo]->update(1,n,idx,1);
		vetor[idx] = novo;
	}
	return 0;
}