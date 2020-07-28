// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccoprep2p1
#include <cstdio>
#define MAXK 3
#define REP(A,B) for(int (A)=0;(A)<(B);(A)++)
typedef unsigned long long ll;
ll pot[20],n,m;
struct matrix{
	ll mat[3][3];
};
matrix base,identidade;
matrix multiplication(matrix A,matrix B){
	matrix C;
	REP(i,MAXK) REP(j,MAXK) C.mat[i][j] = 0LLU;
	REP(i,MAXK){
		REP(j,MAXK){
			REP(k,MAXK){
				C.mat[i][j] = (C.mat[i][j] + A.mat[i][k] * B.mat[k][j]) % m;
			}
		}
	}
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
	scanf("%llu %llu",&n,&m);
	ll f0 = 0LLU, g0 = 0LLU,g0mod = 0LLU,tot = 0LLU;
	REP(i,MAXK) REP(j,MAXK){
		identidade.mat[i][j] = (i==j);
		base.mat[i][j] = (j >= i);	
	}
	bool flag = true;
	for(ll vez = 1;vez<=19 && flag;vez++){
		tot *= 10LLU;
		tot += 9LLU;
		base.mat[0][0] *= 10LLU;
		base.mat[0][0] %= m;
		if(n <= tot){
			flag = false;
			tot = n;
		}
		matrix resp = exponentiation(tot - g0);
		f0 = ((f0 * resp.mat[0][0]) % m) + ((g0mod*resp.mat[0][1]) % m) + resp.mat[0][2];
		f0 %= m;
		g0 = tot;
		g0mod = g0 % m;
	}
	printf("%llu\n",f0);
	return 0;
}