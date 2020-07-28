// Ivan Carvalho
// Solution to https://dmoj.ca/problem/vmss7wc15c2p2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD1 = 1e9 + 9;
const ll prime1 = 999983;
const ll MOD2 = 1e9 + 7;
const ll prime2 = 999979;
const ll invprime1 = 943912055;
const ll invprime2 = 672490127;
const int MAXN = 25011;
int n;
string s1;
ll hash1[MAXN],hash2[MAXN],inv1[MAXN],inv2[MAXN],pot1[MAXN],pot2[MAXN],sufhash1[MAXN],sufhash2[MAXN];
int checa(int a,int b){
	ll val1 = ((hash1[b] - hash1[a-1])*(inv1[a-1]))%MOD1;
	if(val1 < 0) val1 += MOD1;
	ll val2 = ((hash2[b] - hash2[a-1])*(inv2[a-1]))%MOD2;
	if(val2 < 0) val2 += MOD2;
	int rev = n - b;
	ll sufval1 = ((sufhash1[a] - sufhash1[b+1])*(inv1[rev]))%MOD1;
	if(sufval1 < 0) sufval1 += MOD1;
	ll sufval2 = ((sufhash2[a] - sufhash2[b+1])*(inv2[rev]))%MOD2;
	if(sufval2 < 0) sufval2 += MOD2;
	//cout << val1 << " " << sufval1 << " " << val2 << " " << sufval2 << endl;
	if(sufval1 != val1 || sufval2 != val2) return 0;
	return 1;
}
int func(int tam){
	for(int i=1,j = tam;j <= n;i++,j++) if(checa(i,j)) return 1;
	return 0;
}
int main(){
	cin >> n >> s1;
	if(n == 1){
		cout << n << endl;
		cout << s1 << endl;
		return 0;
	}
	pot1[0] = pot2[0] = inv1[0] = inv2[0] = 1;
	for(int i=1;i<=n;i++){
		pot1[i] = (pot1[i-1]*prime1)%MOD1;
		inv1[i] = (inv1[i-1]*invprime1)%MOD1;
		pot2[i] = (pot2[i-1]*prime2)%MOD2;
		inv2[i] = (inv2[i-1]*invprime2)%MOD2;
		hash1[i] = (hash1[i-1] + s1[i-1]*pot1[i])%MOD1;
		hash2[i] = (hash2[i-1] + s1[i-1]*pot2[i])%MOD2;
	}
	for(int i = n,potquevai = 1;i>=1;i--,potquevai++){
		sufhash1[i] = (sufhash1[i+1] + s1[i-1]*pot1[potquevai])%MOD1;
		sufhash2[i] = (sufhash2[i+1] + s1[i-1]*pot2[potquevai])%MOD2;
	}
	int ini = 1, fim = (n+1)/2,resp = -1,meio;
	while(ini <= fim){
		meio = (ini+fim)/2;
		if(func(2*meio)){
			resp = 2*meio;
			ini = meio + 1;
			continue;
		}
		else if(func(2*meio - 1)){
			resp = 2*meio - 1;
			ini = meio + 1;
			continue;
		}
		else{
			fim = meio - 1;
		}
	}
	for(int i=1,j = resp;j <= n;i++,j++){
		if(checa(i,j)){
			for(int k=i-1;k<=j-1;k++) cout << s1[k];
			cout << endl;
			cout << resp << endl;
			return 0;
		}
	}
	return 0;
}n 0;
}