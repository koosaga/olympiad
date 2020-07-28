// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ARRAYSUB/
#include <cstdio>
#include <algorithm>
#define MAXN 100010
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
int n,k,vetor[MAXN],arvore[4*MAXN];
void build(int pos, int left, int right){
	if (left == right){
		arvore[pos] = vetor[left];
		return;
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	arvore[pos] = max(arvore[2*pos],arvore[2*pos+1]);
}
int query(int pos, int left, int right, int i, int j){
	if (left > right || left > j || right < i) return 0;
	if (left >= i && right <= j){
		return arvore[pos];
	}
	int mid = (left + right)/2;
	return max(query(2*pos,left,mid,i,j),query(2*pos+1,mid+1,right,i,j));
}
int main(){
	getint(n);
	for(int i=1;i<=n;i++) getint(vetor[i]);
	build(1,1,n);
	getint(k);
	for(int i=1; i + k - 1 <=n;i++){
		printf("%d ",query(1,1,n,i,i+k-1));
	}
	printf("\n");
	return 0;
} 