// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc15c6p6
#include <cstdio>
#include <bitset>
using namespace std;
const int MAXN = 1500;
const int MAXK = 5;
bitset<MAXN> B[MAXN][MAXK];
int main(){
	int N,M,K;
	scanf("%d %d %d",&N,&M,&K);
	for(int i=0;i<N;i++){
		B[i][0].set(i);
	}
	while(M--){
		int a,b;
		scanf("%d %d",&a,&b);
		a--;
		b--;
		B[a][0].set(b);
		B[b][0].set(a);
	}
	K--;
	for(int k = 1;k<=K;k++){
		for(int i=0;i<N;i++){
			B[i][k] = B[i][k-1];
			for(int j = 0;j < N;j++){
				if(B[i][k-1].test(j)) B[i][k] |= B[j][0];
			}
		}
	}
	for(int i=0;i<N;i++) printf("%lu\n",B[i][K].count());
	return 0;
}