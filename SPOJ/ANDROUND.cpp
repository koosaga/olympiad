// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ANDROUND/
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 100010;
const int NULO = 2147483647;
int arvore[4*MAXN],vetor[MAXN],n,k;
void build(int pos,int left,int right){
	if(left == right){
		arvore[pos] = vetor[left];
		return; 
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	arvore[pos] = (arvore[2*pos] & arvore[2*pos+1]);
}
int query(int pos,int left,int right,int i,int j){
	if(left > right || left > j || right < i) return NULO;
	if(left >= i && right <= j){
		return arvore[pos];
	}
	int mid = (left+right)/2;
	return (query(2*pos,left,mid,i,j) & query(2*pos+1,mid+1,right,i,j));
}
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		scanf("%d %d",&n,&k);
		for(int i=1;i<=n;i++) scanf("%d",&vetor[i]);
		for(int i=1;i<=n;i++){
			vetor[n+i] = vetor[i];
			vetor[2*n+i] = vetor[i]; 
		}
		build(1,1,3*n);
		int lo = 1;
		int hi = 3*n;
		for(int i=1;i<=n;i++) printf("%d ",query(1,1,3*n,max(lo,n + i - k),min(hi,n + i+k)));
		printf("\n");
	}
	return 0;
}