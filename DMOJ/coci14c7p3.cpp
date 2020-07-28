// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c7p3
#include <cstdio>
#include <algorithm>
#define MAXN 150010
using namespace std;
int A[MAXN],B[MAXN],C[MAXN],ida[MAXN],volta[MAXN],maximo[MAXN],resp,N;
void solve(){
	for(int i=1;i<=N;i++) ida[i] = ida[i-1] + A[i];
	for(int i = N;i >= 1;i--) volta[i] = volta[i+1] + B[i];
	int soma = B[N] - C[N];
	maximo[N] = soma;
	for(int i = N-1;i>=1;i--){
		soma += B[i] - C[i];
		maximo[i] = max(soma,maximo[i+1]);
	}
	for(int i=1;i<=N-2;i++){
		//printf("%d %d %d\n",ida[i],volta[i+1],maximo[i+2]);
		resp = min(resp,ida[i] + volta[i+1] - maximo[i+2]);
	}
}
int main(){
	resp = 5 * MAXN;
	scanf("%d",&N);
	for(int i=1;i<=N;i++) scanf("%d",&A[i]);
	for(int i=1;i<=N;i++) scanf("%d",&B[i]);
	for(int i=1;i<=N;i++) scanf("%d",&C[i]);
	solve();
	swap(B,C);
	solve();
	swap(A,B);
	solve();
	swap(B,C);
	solve();
	swap(A,B);
	solve();
	swap(B,C);
	solve();
	printf("%d\n",resp);
	return 0;
}