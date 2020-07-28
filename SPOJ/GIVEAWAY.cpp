// Ivan Carvalho
// Solution to https://www.spoj.com/problems/GIVEAWAY/
#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))
using namespace std;
typedef struct node* pnode;
const int MAXN = 6*1e5+10;
const int INF = 1e9 + 1;
struct node{
	pnode l,r;
	int val;
	node() : l(NULL),r(NULL),val(0){}
	void update(int left,int right,int x,int delta){
		val += delta;
		if(left == right) return;
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
		if(left >= i && right <= j) return val;
		int mid = (left+right)/2;
		if(j <= mid) return l ? l->query(left,mid,i,j) : 0;
		else if(i >= mid + 1) return r ? r->query(mid+1,right,i,j) : 0;
		return ( l ? l->query(left,mid,i,j) : 0 ) + ( r ? r->query(mid+1,right,i,j) : 0 );
	}
};
int vetor[MAXN],n,q;
pnode bit[MAXN];
void update(int posx,int posy,int delta){
	while(posx <= n){
		bit[posx]->update(1,INF,posy,delta);
		posx += LSOne(posx);
	}
}
int read(int posx,int posy){
	int ans = 0;
	while(posx > 0){
		ans += bit[posx]->query(1,INF,posy,INF);
		posx -= LSOne(posx);
	}
	return ans;
}
int query(int x1,int x2,int y){
	return read(x2,y) - read(x1-1,y);
}
int main(){
	scanf("%d",&n);
	bit[0] = new node;
	for(int i = 1;i<=n;i++){
		scanf("%d",&vetor[i]);
		bit[i] = new node;
	}
	for(int i = 1;i<=n;i++){
		update(i,vetor[i],1);
	}
	scanf("%d",&q);
	while(q--){
		int op,a,b,c;
		scanf("%d",&op);
		if(op == 0){
			scanf("%d %d %d",&a,&b,&c);
			if(a > b) swap(a,b);
			printf("%d\n",query(a,b,c+1));
		}
		else{
			scanf("%d %d",&a,&b);
			update(a,vetor[a],-1);
			vetor[a] = b;
			update(a,vetor[a],1);
		}
	}
	return 0;
} 