// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dpr
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 50;
const int MOD = 1e9 + 7;

struct matrix{

	ll mat[MAXN][MAXN];

	matrix(int idd = 0){
		for(int i = 0;i<MAXN;i++){
			for(int j = 0;j<MAXN;j++){
				mat[i][j] = (idd) ? (i == j) : (0);
			}
		}
	}

	matrix operator*(const matrix& other)const{
		matrix ans;
		for(int i = 0;i<MAXN;i++){
			for(int j = 0;j<MAXN;j++){
				for(int k = 0;k<MAXN;k++){
					ans.mat[i][j] += mat[i][k]*other.mat[k][j];
					if(ans.mat[i][j] > MOD) ans.mat[i][j] %= MOD;
				}
			}
		}
		return ans;
	}

};

matrix exponentiation(matrix base, ll K){

	matrix ans(1);

	for(int i = 0;(1LL << i) <= K;i++){
		if((1LL << i) & K) ans = ans*base;
		base = base*base;
	}

	return ans;

}

int main(){

	matrix base;
	int N;
	ll K;
	cin >> N >> K;
	for(int i = 0;i<N;i++){
		for(int j = 0;j<N;j++) cin >> base.mat[i][j];
	}

	matrix ans = exponentiation(base,K);
	ll paths = 0;
	for(int i = 0;i<N;i++){
		for(int j = 0;j<N;j++){
			paths = (paths + ans.mat[i][j]) % MOD;
		}
	}

	cout << paths << endl;

	return 0;

}