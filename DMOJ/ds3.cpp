// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ds3
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <vector>
#define MAXN 100100
#define NULO1 1000000000
#define NULO2 0
using namespace std;
typedef struct node* pnode;
struct node{
	int key,prior,size;
	pnode l,r;
	node(int key) : key(key), prior(rand()), size(1), l(NULL), r(NULL) {}
};
int sz(pnode t){
	if(t == NULL) return 0;
	return t->size;
}
void upd_sz(pnode t){
	if(t == NULL) return;
	t->size = sz(t->l) + 1 + sz(t->r);
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
	pnode aux = new node(key);
	pnode L,R;
	split(t,key,L,R);
	merge(t,L,aux);
	merge(t,t,R);
}
void erase(pnode &t,int key){
	pnode L,R,mid;
	split(t,key-1,L,R);
	split(R,key,mid,R);
	merge(t,L,R);
}
int query(pnode &t,int a,int b){
	pnode L,mid,R;
	split(t,a-1,L,R);
	split(R,b,mid,R);
	int resp = sz(mid);
	merge(t,L,mid);
	merge(t,t,R);
	return resp;
}
int seg[262243][2],vetor[MAXN],ponteiro,n,m;
vector<pnode> raizes;
map<int,int> conversao;
int gcd(int x,int y){
	if(x < y) swap(x,y);
	if(y == 0) return x;
	return gcd(y,x%y); 
}
void build(int pos,int left,int right){
	if(left == right){
		seg[pos][0] = seg[pos][1] = vetor[left];
		return;
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	seg[pos][0] = gcd(seg[2*pos][0],seg[2*pos+1][0]);
	seg[pos][1] = min(seg[2*pos][1],seg[2*pos+1][1]);
}
void update(int pos,int left,int right,int x,int val){
	if(left == right){
		seg[pos][0] = seg[pos][1] = val;
		return;
	}
	int mid = (left+right)/2;
	if(x<=mid){
		update(2*pos,left,mid,x,val);
	}
	else{
		update(2*pos+1,mid+1,right,x,val);
	}
	seg[pos][0] = gcd(seg[2*pos][0],seg[2*pos+1][0]);
	seg[pos][1] = min(seg[2*pos][1],seg[2*pos+1][1]);
}
int query_min(int pos,int left,int right,int i,int j){
	if(left>right||left>j||right<i) return NULO1;
	if(left>=i&&right<=j){
		return seg[pos][1];
	}
	int mid = (left+right)/2;
	if(j <= mid){
		return query_min(2*pos,left,mid,i,j);
	}
	if(i >= mid + 1){
		return query_min(2*pos+1,mid+1,right,i,j);
	}
	return min(query_min(2*pos,left,mid,i,j),query_min(2*pos+1,mid+1,right,i,j));
}
int query_gcd(int pos,int left,int right,int i,int j){
	if(left>right||left>j||right<i) return NULO2;
	if(left>=i&&right<=j){
		return seg[pos][0];
	}
	int mid = (left+right)/2;
	if(j <= mid){
		return query_gcd(2*pos,left,mid,i,j);
	}
	if(i >= mid + 1){
		return query_gcd(2*pos+1,mid+1,right,i,j);
	}
	return gcd(query_gcd(2*pos,left,mid,i,j),query_gcd(2*pos+1,mid+1,right,i,j));
}
int get_id(int val){
	if(conversao.count(val)){
		return conversao[val];
	}
	pnode novo = NULL;
	raizes.push_back(novo);
	conversao[val] = ponteiro;
	ponteiro++;
	return ponteiro-1;
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&vetor[i]);
		int id = get_id(vetor[i]);
		insert(raizes[id],i);
	}
	build(1,1,n);
	while(m--){
		char op;
		scanf(" %c",&op);
		if(op == 'C'){
			int x,v;
			scanf("%d %d",&x,&v);
			int velhoid = get_id(vetor[x]);
			int novoid = get_id(v);
			update(1,1,n,x,v);
			erase(raizes[velhoid],x);
			insert(raizes[novoid],x);
			vetor[x] = v;
		}
		else if(op == 'M'){
			int l,r;
			scanf("%d %d",&l,&r);
			printf("%d\n",query_min(1,1,n,l,r));
		}
		else if(op == 'G'){
			int l,r;
			scanf("%d %d",&l,&r);
			printf("%d\n",query_gcd(1,1,n,l,r));
		}
		else if(op == 'Q'){
			int l,r;
			scanf("%d %d",&l,&r);
			int mdc = query_gcd(1,1,n,l,r);
			if(!conversao.count(mdc)){
				printf("0\n");
			}
			else{
				int id = get_id(mdc);
				printf("%d\n",query(raizes[id],l,r));
			}
		}
	}
	return 0;
}			printf("0\n");
			}
			else{
				int id = get_id(mdc);
				printf("%d\n",query(raizes[id],l,r));
			}
		}
	}
	return 0;
}