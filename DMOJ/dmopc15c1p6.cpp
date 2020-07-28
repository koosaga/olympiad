// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc15c1p6
#include <cstdio>
#define MAXN 200010
int arvore[4*MAXN],lazy[4*MAXN],vetor[MAXN],MOD;
inline int add(int x,int y){
	return (x+y)%MOD;
}
void build(int pos,int left,int right){
	if(left == right){
		arvore[pos] = vetor[left];
		return;
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	arvore[pos] = add(arvore[2*pos],arvore[2*pos+1]);
}
void propagate(int pos,int left,int right){
	lazy[pos] %= MOD;
	if(lazy[pos] == 0) return;
	arvore[pos] = add(arvore[pos], ((right - left + 1) % MOD) *lazy[pos]  );
	if(left != right){
		lazy[2*pos] += lazy[pos];
		lazy[2*pos+1] += lazy[pos];
	}
	lazy[pos] = 0;
}
void update(int pos,int left,int right,int i,int j,int val){
	propagate(pos,left,right);
	if(left>right||left>j||right<i) return;
	if(left >= i && right <= j){
		lazy[pos] = val;
		propagate(pos,left,right);
		return;
	}
	int mid = (left+right)/2;
	update(2*pos,left,mid,i,j,val);
	update(2*pos+1,mid+1,right,i,j,val);
	arvore[pos] = add(arvore[2*pos],arvore[2*pos+1]);
}
int query(int pos,int left,int right,int i,int j){
	propagate(pos,left,right);
	if(left>right||left>j||right<i) return 0;
	if(left >= i && right <= j){
		return arvore[pos];
	}
	int mid = (left+right)/2;
	return add(query(2*pos,left,mid,i,j),query(2*pos+1,mid+1,right,i,j));
}
int main(){
	int n,q;
	scanf("%d %d %d",&MOD,&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",&vetor[i]);
		vetor[i] %= MOD;
	}
	build(1,1,n);
	while(q--){
		int op;
		scanf("%d",&op);
		if(op == 1){
			int l,r,x;
			scanf("%d %d %d",&l,&r,&x);
			update(1,1,n,l,r,x);
		}
		else if(op == 2){
			int l,r;
			scanf("%d %d",&l,&r);
			printf("%d\n",query(1,1,n,l,r));
		}
	}
	return 0;
}
}