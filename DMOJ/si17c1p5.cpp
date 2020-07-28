// Ivan Carvalho
// Solution to https://dmoj.ca/problem/si17c1p5
#include <bits/stdc++.h>
#define REP(A,B) for(int (A) = 0;(A)<(B);(A)++)
using namespace std;
typedef long long ll;
const int N = 2;
const ll MOD = ll(1e9);
struct matrix{
	ll mat[N][N];
};
matrix multiplication(matrix A,matrix B){
	matrix C;
	REP(i,N){
		REP(j,N){
			C.mat[i][j] = 0;
		}
	}
	REP(i,N){
		REP(j,N){
			REP(k,N){
				C.mat[i][j] += A.mat[i][k]*B.mat[k][j];
				C.mat[i][j] %= MOD;
			}
		}
	}
	return C;
}
matrix exponentation(ll pot,matrix base){
	matrix resp;
	matrix exponenciada = base;
	REP(i,N){
		REP(j,N){
			resp.mat[i][j] = (i == j);
		}
	}
	for(ll i = 0;(1LL << i) <= pot;i++){
		if((1LL << i) & pot) resp = multiplication(resp,exponenciada);
		exponenciada = multiplication(exponenciada,exponenciada);
	}
	return resp;
}
int main(){
	ll a,b,pown;
	cin >> a >> b >> pown;
	if(pown == 1){
		cout << b % MOD << endl;
		return 0;
	}
	if(pown == 0){
		cout << a % MOD << endl;
		return 0;
	}
	pown--;
	matrix base;
	base.mat[0][0] = 1;base.mat[0][1] = 1;
	base.mat[1][0] = 1;base.mat[1][1] = 0;
	matrix resp = exponentation(pown,base);
	ll exibe = resp.mat[0][0]*b + resp.mat[0][1]*a;
	exibe %= MOD;
	printf("%lld\n",exibe);
	return 0;
}