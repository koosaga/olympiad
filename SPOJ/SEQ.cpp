// Ivan Carvalho
// Solution to https://www.spoj.com/problems/SEQ/
#include <cstdio>
#include <algorithm>
#define REP(A,B) for(long long A=0;A<B;A++)
using namespace std;
typedef long long ll;
const ll MAXK =  10;
const ll MOD = 1e9;
typedef struct matrix{
	ll mat[MAXK][MAXK];
}matrix;
ll A[MAXK],B[MAXK],K;
matrix base,identidade;
matrix mult(matrix A,matrix B){
	matrix C;
	REP(i,K) REP(j,K) C.mat[i][j] = 0;
	REP(i,K) REP(j,K) REP(k,K) C.mat[i][j] = (C.mat[i][j] + A.mat[i][k]*B.mat[k][j]) % MOD;
	return C;
}
matrix fast(ll expo){
	if(expo == 0) return identidade;
	if(expo == 1) return base;
	if(expo%2==0){
		matrix temp = fast(expo/2);
		return mult(temp,temp);
	}
	return mult(base,fast(expo-1));
}
int main(){
	ll TC;
	scanf("%lld",&TC);
	while(TC--){
		scanf("%lld",&K);
		REP(i,K) scanf("%lld",&A[i]);
		REP(i,K) scanf("%lld",&B[i]);
		REP(i,K) REP(j,K){
			identidade.mat[i][j] = (i==j);
			base.mat[i][j] = (i+1==j);
		}
		REP(i,K){
			ll j = i+1;
			base.mat[K-1][i] = B[K-j];
		}
		ll n;
		scanf("%lld",&n);
		if(n<=K){
			printf("%lld\n",A[n-1]);
			continue;
		}
		matrix resp = fast(n-1);
		ll exibir = 0;
		REP(i,K){
			exibir = (exibir + resp.mat[0][i]*A[i]) % MOD; 
		}
		exibir = (exibir + MOD) % MOD;
		printf("%lld\n",exibir);
	}
	return 0;
}