// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci07c3p6
#include <cstdio>
#include <vector>
#define MAXN 250020
using namespace std;
int arvore[3*MAXN][10];
int lazy[3*MAXN],vetor[MAXN],n,m;
void build(int pos,int left,int right){
	if(left == right){
		arvore[pos][vetor[left]]++;
		return;
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	for(int idx=0;idx<10;idx++) arvore[pos][idx] = (arvore[2*pos][idx] + arvore[2*pos+1][idx]);
}
void propagate(int pos,int left,int right){
	int copia[10];
	for(int i=0;i<10;i++){
		copia[i] = 0;
	}
	for(int i=0;i<10;i++){
		copia[(i + lazy[pos])%10] = arvore[pos][i];
	}
	for(int i=0;i<10;i++){
		arvore[pos][i] = copia[i];
	}
	if(left != right){
		lazy[2*pos] += lazy[pos];
		lazy[2*pos+1] += lazy[pos];
	}
	lazy[pos] = 0;
}
void update(int pos,int left,int right,int i,int j){
	propagate(pos,left,right);
	if(left>right||left>j||right<i) return;
	if(left >= i && right <= j){
		lazy[pos]++;
		propagate(pos,left,right);
		return;
	}
	int mid = (left+right)/2;
	update(2*pos,left,mid,i,j);
	update(2*pos+1,mid+1,right,i,j);
	for(int idx=0;idx<10;idx++) arvore[pos][idx] = (arvore[2*pos][idx] + arvore[2*pos+1][idx]);
}
int query(int pos,int left,int right,int i,int j){
	propagate(pos,left,right);
	if(left>right||left>j||right<i) return 0;
	if(left >= i && right <= j){
		int ans = 0;
		for(int idx=0;idx<10;idx++){
			ans += idx*arvore[pos][idx];
		}
		return ans;
	}
	int mid = (left+right)/2;
	return query(2*pos,left,mid,i,j) + query(2*pos+1,mid+1,right,i,j);
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		char c;
		scanf(" %c",&c);
		vetor[i] = c - '0';
	}
	build(1,1,n);
	while(m--){
		int a,b;
		scanf("%d %d",&a,&b);
		printf("%d\n",query(1,1,n,a,b));
		update(1,1,n,a,b);
	}
	return 0;
}n 0;
}