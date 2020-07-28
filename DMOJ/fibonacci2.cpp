// Ivan Carvalho
// Solution to https://dmoj.ca/problem/fibonacci2
#include <bits/stdc++.h>
#define REP(A,B) for(int (A) = 0;(A)<(B);(A)++)
using namespace std;
typedef long long ll;
const int N = 2;
const ll MOD = ll(1e9 + 7);
const ll PISANO = 2000000016LL;
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
			}
			C.mat[i][j] %= MOD;
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
	ll a = 0,b = 1;
	string pown;
	cin >> pown;
	reverse(pown.begin(),pown.end());
	ll somatorio = 0, pot = 1;
	for(char c : pown){
		ll digito = c - '0';
		somatorio += digito*pot;
		somatorio %= PISANO;
		pot *= 10;
		pot %= PISANO;
	}
	if(somatorio == 1){
		cout << b % MOD << endl;
		return 0;
	}
	if(somatorio == 0){
		cout << a % MOD << endl;
		return 0;
	}
	somatorio--;
	if(somatorio < 0) somatorio += PISANO; 
	matrix base;
	base.mat[0][0] = 1;base.mat[0][1] = 1;
	base.mat[1][0] = 1;base.mat[1][1] = 0;
	matrix resp = exponentation(somatorio,base);
	ll exibe = resp.mat[0][0]*b + resp.mat[0][1]*a;
	exibe %= MOD;
	printf("%lld\n",exibe);
	return 0;
}
