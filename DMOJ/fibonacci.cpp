// Ivan Carvalho
// Solution to https://dmoj.ca/problem/fibonacci
#include <cstdio>
typedef unsigned long long ll;
#define REP(A,B) for(ll A = 0;A<B;A++)
#define MAXK 2
#define MOD 1000000007LLU
struct matrix{
	ll mat[MAXK][MAXK];
};
matrix base,identidade;
matrix mul(matrix A,matrix B){
	matrix C;
	REP(i,MAXK) REP(j,MAXK) C.mat[i][j] = 0;
	REP(i,MAXK) REP(j,MAXK) REP(k,MAXK) C.mat[i][j] = (C.mat[i][j] + A.mat[i][k]*B.mat[k][j]) % MOD;
	return C;
}
matrix fast_expo(ll expo){
	if(expo == 0) return identidade;
	if(expo == 1) return base;
	if(expo % 2 == 0){
		matrix temp = fast_expo(expo/2);
		return mul(temp,temp);
	}
	return mul(base,fast_expo(expo-1));
}
int main(){
	ll n;
	scanf("%llu",&n);
	REP(i,MAXK) REP(j,MAXK) identidade.mat[i][j] = (i==j);
	if(n == 0){
		printf("0\n");
		return 0;
	}
	base.mat[0][0] = 0;
	base.mat[0][1] = 1;
	base.mat[1][0] = 1;
	base.mat[1][1] = 1;
	matrix resp = fast_expo(n-1);
	//REP(i,MAXK){
	//	REP(j,MAXK){
	//		printf("%lld ",resp.mat[i][j]);
	//	}
	//	printf("\n");
	//}
	ll exibir = (resp.mat[0][0] + resp.mat[0][1]) % MOD;
	printf("%llu\n",exibir);
	return 0;
}