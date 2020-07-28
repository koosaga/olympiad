// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADAPLANT/
#include <cstdio>
#include <algorithm>
#define MAXN 100010
using namespace std;
const int INF = 1e9 + 1;
int arvore[4*MAXN],vetor[MAXN],n;
void build(int pos,int left,int right){
	if(left == right){
		arvore[pos] = vetor[left];
		return;
	}
	int mid = (left + right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	arvore[pos] = min(arvore[2*pos],arvore[2*pos+1]);
}
int query(int pos,int left,int right,int i,int j){
	if(left > right || left > j || right < i) return INF;
	if(left >= i && right <= j){
		return arvore[pos];
	}
	int mid = (left + right)/2;
	return min(query(2*pos,left,mid,i,j),query(2*pos+1,mid+1,right,i,j));
}
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		int k;
		scanf("%d %d",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%d",&vetor[i]);
		}
		int resp = 0;
		build(1,1,n);
		for(int i=1;i<=n;i++){
			int menor = min(query(1,1,n,max(1,i - k - 1),max(i-1,1)), query(1,1,n,min(i+1,n),min(i+k+1,n)));
			//printf("Menor %d Q1 %d Q2 %d\n",menor,query(1,1,n,max(1,i - k - 1),max(i-1,1)),query(1,1,n,min(i+1,n),min(i+k+1,n)));
			resp = max(vetor[i] - menor,resp);
		}
		printf("%d\n",resp);
	}
	return 0;
}