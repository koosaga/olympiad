// Ivan Carvalho
// Solution to https://www.spoj.com/problems/FIBTWIST/
#include <bits/stdc++.h>
#define REP(A,B) for(int (A) = 0;(A) < (B);(A)++)
using namespace std;
typedef long long ll;
const int T = 4;
ll MOD;
int N;
struct matrix{ll mat[T][T];};
matrix multiplication(matrix A,matrix B){
	matrix C;
	REP(i,T) REP(j,T) C.mat[i][j] = 0;
	REP(i,T) REP(j,T) REP(k,T) C.mat[i][j] = (C.mat[i][j] + A.mat[i][k]*B.mat[k][j]) % MOD;
	return C;
}
matrix exponentation(ll pown,matrix base){
	matrix exponenciada = base;
	matrix resp;
	REP(i,T) REP(j,T) resp.mat[i][j] = (i == j);
	for(ll i = 0;(1LL << i) <= pown;i++){
		if((1LL << i) & pown) resp = multiplication(resp,exponenciada);
		exponenciada = multiplication(exponenciada,exponenciada);
	}
	return resp;
}
int main(){
	cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0);
	int TC;
	cin >> TC;
	while(TC--){
		cin >> N >> MOD;
		if(N == 1){
			cout << 1 << endl;
			continue;
		}
		if(N == 0){
			cout << 0 << endl;
			continue;
		}
		N--;
		matrix base;
		base.mat[0][0] = 1;base.mat[0][1] = 1;base.mat[0][2] = 1;base.mat[0][3] = 0;
		base.mat[1][0] = 1;base.mat[1][1] = base.mat[1][2] = base.mat[1][3] = 0;
		base.mat[2][0] = base.mat[2][1] = 0;base.mat[2][2] = 1;base.mat[2][3] = 1;
		base.mat[3][0] = base.mat[3][1] = base.mat[3][2] = 0;base.mat[3][3] = 1;
		matrix resp = exponentation(N,base);
		ll exibe = (resp.mat[0][0] + resp.mat[0][2] + resp.mat[0][3]) % MOD;
		cout << exibe << endl;
	}
	return 0;
}