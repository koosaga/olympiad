// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1474
#include <cstdio>
#include <algorithm>
#define REP(A,B) for(long long A=0;A<B;A++)
using namespace std;
#define MAXK 2
#define MOD 1000000LL
typedef long long ll;
struct matrix{
	ll mat[MAXK][MAXK];
};
matrix base,identidade;
matrix multiplication(matrix A,matrix B){
	matrix C;
	REP(i,MAXK) REP(j,MAXK) C.mat[i][j] = 0;
	REP(i,MAXK) REP(j,MAXK) REP(k,MAXK) C.mat[i][j] = (C.mat[i][j] + A.mat[i][k]*B.mat[k][j]) % MOD;
	return C;
}
matrix exponentiation(ll expo){
	if(expo == 0) return identidade;
	if(expo == 1) return base;
	if(expo % 2 == 0){
		matrix temp = exponentiation(expo/2);
		return multiplication(temp,temp);
	}
	return multiplication(base,exponentiation(expo-1));
}
int main(){
	ll n,k,l;
	while(scanf("%lld %lld %lld",&n,&k,&l) != EOF){
		n /= 5;
		k %= MOD;
		l %= MOD;
		REP(i,MAXK) REP(j,MAXK){
			identidade.mat[i][j] = (i==j);
			base.mat[i][j] = (i+1==j);
		}
		base.mat[1][0] = l;
		base.mat[1][1] = k;
		ll caso1 = k % MOD;
		ll caso2 = ((k*k % MOD) + l % MOD) % MOD;
		matrix resp = exponentiation(n-1);
		ll exibir = (caso1*resp.mat[0][0] + caso2*resp.mat[0][1]) % MOD;
		ll temp = exibir;
		ll digitos = 0;
		while(temp != 0){
			temp /= 10;
			digitos++;
		}
		if(exibir == 0) digitos = 1;
		digitos = 6 - digitos;
		while(digitos--) printf("0");
		printf("%lld\n",exibir);
	}
	return 0;
}
