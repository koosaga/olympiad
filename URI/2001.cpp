// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/2001
#include <cstdio>
#include <vector>
#include <algorithm>
#define REP(A,B) for(long long A=0;A<B;A++)
using namespace std;
typedef long long ll;
const ll MAXK =  101LL;
const ll MOD = 303700049LL;
typedef struct matrix{
	ll mat[MAXK][MAXK];
}matrix;
ll A[MAXK],B[MAXK],K;
matrix base,identidade;
matrix mult(matrix A,matrix B){
	matrix C;
	REP(i,K) REP(j,K) C.mat[i][j] = 0;
	REP(i,K) REP(j,K) REP(k,K) C.mat[i][j] = (C.mat[i][j] + A.mat[i][k]*B.mat[k][j]);
	REP(i,K) REP(j,K) C.mat[i][j] %= MOD;
	return C;
}
matrix fast(ll expo){
	matrix ans,minhabase;
	REP(i,K) REP(j,K) ans.mat[i][j] = (i==j);
	REP(i,K) REP(j,K) minhabase.mat[i][j] = base.mat[i][j];
	while(expo){
		if(expo & 1LL) ans = mult(ans,minhabase);
		minhabase = mult(minhabase,minhabase);
		expo /= 2LL; 
	}
	return ans;
}
int main(){
	ll n;
	while(scanf("%lld %lld",&K,&n) != EOF){
		REP(i,K) scanf("%lld",&A[i]);
		REP(i,K){
			ll j = i+1;
			B[i] = j;
		}
		K++;
		REP(i,K) REP(j,K){
			identidade.mat[i][j] = (i==j);
			base.mat[i][j] = (i+1==j);
		}
		base.mat[0][0] = 1;
		REP(i,K){
			ll tempk = K-1;
			base.mat[K-1][i] = (tempk-i+1);
		}
		base.mat[K-1][0] = 0;
		matrix novaresp = fast(n-1);
		ll novoexibir = 0;
		K--;
		REP(i,K){
			novoexibir = (novoexibir + novaresp.mat[0][i+1]*A[i]) % MOD;
		}
		ll exibir = 0;
		REP(i,K){
			exibir = (exibir + novaresp.mat[1][i+1]*A[i]) % MOD;
		}
		novoexibir += exibir;
		novoexibir %= MOD;
		printf("%lld %lld\n",exibir,novoexibir);
	}
	return 0;
} 
