// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1202
#include <iostream>
#include <string>
#define MAXN 2
#define MODULO 1000
using namespace std;
struct Matrix{
	int mat[MAXN][MAXN];
};
Matrix base;
inline Matrix multiplication(Matrix A,Matrix B){
	Matrix C;
	for(int i=0;i<MAXN;i++){
		for(int j=0;j<MAXN;j++){
			C.mat[i][j] = 0;
			for(int k=0;k<MAXN;k++){
				C.mat[i][j] += (A.mat[i][k] * B.mat[k][j]) % MODULO;
				C.mat[i][j] %= MODULO;
			}
		}
	}
	return C;
}
Matrix exponentiation(string expo){
	Matrix resp;
	for(int i=0;i<MAXN;i++){
		for(int j=0;j<MAXN;j++){
			resp.mat[i][j] = int(i==j);
		}
	}
	while(true){
		if(expo.empty()) break;
		if(expo.back() == '1') resp = multiplication(resp,base);
		base = multiplication(base,base);
		expo.pop_back();
	}
	return resp;
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int TC;
	cin >> TC;
	while(TC--){
		for(int i=0;i<MAXN;i++){
			for(int j=0;j<MAXN;j++){
				base.mat[i][j] = 1;
			}
		}
		base.mat[1][1] = 0;
		string num;
		cin >> num;
		Matrix resposta = exponentiation(num);
		int exibir = resposta.mat[0][1];
		if(exibir < 10) cout << "00";
		else if(exibir < 100) cout << "0";
		cout << exibir << endl;
	}
	return 0;
}
