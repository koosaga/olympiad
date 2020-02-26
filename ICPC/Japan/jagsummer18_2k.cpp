#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 20005;
const int mod = 1e9 + 7;

int n, a, b;
lint fact[MAXN], invf[MAXN];

lint bino(int x, int y){
	return fact[x] * (invf[y] * invf[x - y] % mod) % mod;
}

int f(int x, int y){
	if(x > y) return 0;
	return (bino(x + y, x) - bino(x + y, x - 1) + mod) %mod;
}

lint ipow(int x, int p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}
int main(){
	fact[0] = invf[0] = 1;
	for(int i=1; i<MAXN; i++){
		fact[i] = fact[i-1] * i % mod;
		invf[i] = ipow(fact[i], mod - 2);
	}
	cin >> n >> a >> b;
	b = n - 1 - b;
	if(a > b) swap(a, b);
	cout << 1ll * f(a, b) * f(n - b - 1, n - a - 1) % mod << endl;
}
