// Ivan Carvalho
// Solution to https://www.spoj.com/problems/SPP/
#include <cstdio>
#include <algorithm>
#define REP(A,B) for(long long A=0;A<B;A++)
#define s1(A) scanf("%lld",&A);
using namespace std;
typedef long long ll;
const ll MAXK = 17;
ll K,N,M,P,A[MAXK],B[MAXK];
struct matrix{
	ll mat[MAXK][MAXK];
};
matrix base,identidade;
matrix mult(matrix A,matrix B){
	matrix C;
	REP(i,K) REP(j,K) C.mat[i][j]  = 0;
	REP(i,K) REP(j,K) REP(k,K) C.mat[i][j] = (C.mat[i][j] + A.mat[i][k]*B.mat[k][j]) % P; 
	return C;
}
matrix fast(ll expo){
	if(expo == 0) return identidade;
	if(expo == 1) return base;
	if(expo % 2 == 0){
		matrix temp = fast(expo/2);
		return mult(temp,temp);
	}
	return mult(base,fast(expo-1));
}
int main(){
	ll TC;
	s1(TC);
	while(TC--){
		s1(K);
		REP(i,K) s1(A[i]);
		REP(i,K) s1(B[i]);
		s1(M);
		s1(N);
		s1(P);
		K++;
		REP(i,K) REP(j,K){
			identidade.mat[i][j] = (i==j);
			base.mat[i][j] = (i+1==j);
		}
		base.mat[0][0] = 1;
		for(ll i=1;i<K;i++){
			ll tempk = K-1;
			base.mat[K-1][i] = B[tempk-i];
		}
		matrix resp1 = fast(M-1);
		matrix resp2 = fast(N);
		K--;
		ll exibir1 = 0;
		ll exibir2 = 0;
		REP(i,K){
			exibir1 = (exibir1 + resp1.mat[0][i+1]*A[i]) % P;
		}
		REP(i,K){
			exibir2 = (exibir2 + resp2.mat[0][i+1]*A[i]) % P;
		}
		ll exibir = exibir2 - exibir1;
		exibir %= P;
		exibir += P;
		exibir %= P;
		printf("%lld\n",exibir);
	}
	return 0;
}