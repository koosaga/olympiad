// Ivan Carvalho
// Solution to https://www.spoj.com/problems/CNTPRIME/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1e4 + 1;
const int MAXP = 1e6 + 1;
const int MAXS = 1e3 + 1;
int arvore[4*MAXN],lazy[4*MAXN],vetor[MAXN],n,m,TC;
int crivo[MAXP];
void build(int pos,int left,int right){
	lazy[pos] = -1;
	if(left == right){
		arvore[pos] = !crivo[vetor[left]];
		return;
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	arvore[pos] = arvore[2*pos] + arvore[2*pos+1];
}
void update(int pos,int left,int right,int i,int j,int val){
	if(lazy[pos] != -1){
		arvore[pos] = (right - left + 1)*lazy[pos];
		if(left != right){
			lazy[2*pos] = lazy[pos];
			lazy[2*pos+1] = lazy[pos];
		}
		lazy[pos] = -1;
	}
	if(left > right || left > j || right < i) return;
	if(left >= i && right <= j){
		arvore[pos] = (right - left + 1)*val;
		if(left != right){
			lazy[2*pos] = val;
			lazy[2*pos+1] = val;
		}
		return;
	}
	int mid = (left+right)/2;
	update(2*pos,left,mid,i,j,val);
	update(2*pos+1,mid+1,right,i,j,val);
	arvore[pos] = arvore[2*pos] + arvore[2*pos+1];
}
int query(int pos,int left,int right,int i,int j){
	if(lazy[pos] != -1){
		arvore[pos] = (right - left + 1)*lazy[pos];
		if(left != right){
			lazy[2*pos] = lazy[pos];
			lazy[2*pos+1] = lazy[pos];
		}
		lazy[pos] = -1;
	}
	if(left > right || left > j || right < i) return 0;
	if(left >= i && right <= j){
		return arvore[pos];
	}
	int mid = (left+right)/2;
	return query(2*pos,left,mid,i,j) + query(2*pos+1,mid+1,right,i,j);
}
int main(){
	crivo[0] = crivo[1] = 1;
	for(int i=2;i<MAXP;i++){
		if(!crivo[i]){
			if(i > MAXS) continue;
			for(int j = i*i;j<MAXP;j += i){
				crivo[j] = 1;
			}
		}
	}
	scanf("%d",&TC);
	for(int tc=1;tc<=TC;tc++){
		printf("Case %d:\n",tc);
		scanf("%d %d",&n,&m);
		for(int i=1;i<=n;i++){
			scanf("%d",&vetor[i]);
		}
		build(1,1,n);
		while(m--){
			int op;
			scanf("%d",&op);
			if(op == 0){
				int x,y,v;
				scanf("%d %d %d",&x,&y,&v);
				update(1,1,n,x,y,!crivo[v]);
			}
			else{
				int x,y;
				scanf("%d %d",&x,&y);
				printf("%d\n",query(1,1,n,x,y));
			}
		}
	}
	return 0;
}