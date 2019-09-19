#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 300005;
const int mod = 998244353;
 
int n, pwr[MAXN];
char str[MAXN];
lint fact[MAXN], invf[MAXN];
 
lint ipow(int x, int p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}
 
lint bino(int x, int y){
	if(min(x, y) < 0) return 0;
	return fact[x + y] * (invf[x] * invf[y] % mod) % mod;
}
 
int main(){
	scanf("%s", str);
	n = strlen(str);
	pwr[0] = 1;
	fact[0] = invf[0] = 1;
	for(int i=1; i<=n; i++) pwr[i] = pwr[i-1] * 2 % mod;
	for(int i=1; i<=n; i++){
		fact[i] = fact[i-1] * i % mod;
		invf[i] = ipow(fact[i], mod - 2);
	}
	if(count(str, str + n, str[0]) == n){
		cout << n << endl;
		return 0;
	}
	lint ret = pwr[n] - 1;
	for(int i=0; i<n; ){
		int e = i;
		while(e < n && str[i] == str[e]) e++;
		for(int j=i; j<e; j++){
			int l = j - i + 1;
			lint sub = (pwr[l] + mod - l - 1) * bino(i - 1, n - (j + 1)) % mod;
			ret += mod - sub;
			l = e - j;
			sub = (pwr[l] + mod - l - 1) * bino(j, n - e - 1) % mod;
			ret += mod - sub;
		}
		i = e;
	}
	cout << ret % mod << endl;
}
