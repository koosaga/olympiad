// Ivan Carvalho
// Solution to https://dmoj.ca/problem/thicc17p2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
ll n,a,b,m,soma,resp;
int main(){
	cin >> n >> a >> b >> m;
	soma = a;
	for(ll i = 1;i<n;i++){
		a *= b;
		a %= m;
		//printf("%lld %lld\n",a,soma);
		resp += (a*soma) % MOD;
		resp %= MOD;
		soma += a;
		soma %= MOD;
	}
	resp *= 2;
	resp %= MOD;
	cout << resp << endl;
	return 0;
}