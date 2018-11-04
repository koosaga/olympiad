#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, d;
const int mod = 31991;

struct mat{
	int adj[55][55];
	mat operator*(const mat &m)const{
		mat ret;
		for(int i=0; i<d; i++){
			for(int j=0; j<d; j++){
				ret.adj[i][j] = 0;
				for(int k=0; k<d; k++){
					ret.adj[i][j] += adj[i][k] * m.adj[k][j];
					ret.adj[i][j] %= mod;
				}
			}
		}
		return ret;
	}
}ret, piv;

int main(){
	cin >> d >> n;
	for(int i=0; i<d; i++){
		ret.adj[i][i] = 1;
		piv.adj[0][i] = 1;
	}
	for(int i=1; i<d; i++){
		piv.adj[i][i-1] = 1;
	}
	while(n){
		if(n&1) ret = ret * piv;
		piv = piv * piv;
		n >>= 1;
	}
	cout << ret.adj[0][0];
}
