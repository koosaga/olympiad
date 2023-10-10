#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 9;
const int magic = 167;

struct matrix{
	lint a[magic][magic];
	matrix(int arg){
		memset(a, 0, sizeof(a));
		for(int i=0; i<magic; i++) a[i][i] = arg;
	}
};

matrix mul(matrix a, matrix b){
	matrix c(0);
	for(int i=0; i<magic; i++){
		for(int j=0; j<magic; j++){
			for(int k=0; k<magic; k++){
				c.a[i][j] += a.a[i][k] * b.a[k][j] % mod;
			}
			c.a[i][j] %= mod;
		}
	}
	return c;
}

int a[6];

int main(){
	int n, m;
	cin >> n >> m;
	for(int i=0; i<6; i++) cin >> a[i];
	matrix ret(1), piv(0);
	n %= magic;
	for(int i=0; i<6; i++) a[i] %= magic;
	for(int i=0; i<magic; i++){
		int nxt1 = a[0] * i * i + a[1] * i + a[2];
		int nxt2 = a[3] * i * i + a[4] * i + a[5];
		nxt1 %= magic;
		nxt2 %= magic;
		piv.a[i][nxt1]++;
		piv.a[i][nxt2]++;
	}
	while(m){
		if(m&1) ret = mul(ret, piv);
		piv = mul(piv, piv);
		m >>= 1;
	}
	lint ans = 0;
	lint pwr = 1;
	for(int i=0; i<magic; i++){
		ans += pwr * ret.a[n][i] % mod;
		pwr = (pwr * 112345) % mod;
	}
	cout << ans % mod;
}
