// Ivan Carvalho
// Solution to https://dmoj.ca/problem/mnyc17p3
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
const ll MOD1 = 1e9 + 9;
const ll prime1 = 999983;
const ll MOD2 = 1e9 + 7;
const ll prime2 = 999979;
const ll invprime1 = 943912055;
const ll invprime2 = 672490127;
const int MAXN = 1e6 + 10;
ll hash1[MAXN],hash2[MAXN],pot1[MAXN],pot2[MAXN],inv1[MAXN],inv2[MAXN],shash1[MAXN],shash2[MAXN];
string s1,s2;
int checa(int a,int b,int c,int d){
	ll val1 = ((hash1[b] - hash1[a-1])*(inv1[a-1]))%MOD1;
	if(val1 < 0) val1 += MOD1;
	ll val2 = ((hash2[b] - hash2[a-1])*(inv2[a-1]))%MOD2;
	if(val2 < 0) val2 += MOD2;
	ll sval1 = ((shash1[d] - shash1[c-1])*(inv1[c-1]))%MOD1;
	if(sval1 < 0) sval1 += MOD1;
	ll sval2 = ((shash2[d] - shash2[c-1])*(inv2[c-1]))%MOD2;
	if(sval2 < 0) sval2 += MOD2;
	if(sval1 != val1 || sval2 != val2) return 0;
	return 1;
}
int main(){
	cin >> s1 >> s2;
	pot1[0] = pot2[0] = inv1[0] = inv2[0] = 1;
	for(int i=1;i<=s1.size();i++){
		pot1[i] = (pot1[i-1]*prime1) % MOD1;
		pot2[i] = (pot2[i-1]*prime2) % MOD2;
		inv1[i] = (inv1[i-1]*invprime1) % MOD1;
		inv2[i] = (inv2[i-1]*invprime2) % MOD2;
		hash1[i] = (hash1[i-1] + s1[i-1]*pot1[i]) % MOD1;
		hash2[i] = (hash2[i-1] + s1[i-1]*pot2[i]) % MOD2;
	}
	for(int i=1;i<=s2.size();i++){
		pot1[i] = (pot1[i-1]*prime1) % MOD1;
		pot2[i] = (pot2[i-1]*prime2) % MOD2;
		inv1[i] = (inv1[i-1]*invprime1) % MOD1;
		inv2[i] = (inv2[i-1]*invprime2) % MOD2;
		shash1[i] = (shash1[i-1] + s2[i-1]*pot1[i]) % MOD1;
		shash2[i] = (shash2[i-1] + s2[i-1]*pot2[i]) % MOD2;
	}
	int cand1 = s1.size(),cand2 = 1,melhor1 = -1,melhor2 = -1;
	while(cand1 >= 1 && cand2 <= s2.size()){
		if(checa(cand1,s1.size(),1,cand2)){
			melhor1 = cand1;
			melhor2 = cand2;
		}
		cand1--;
		cand2++;
	}
	if(melhor1 == -1 && melhor2 == -1){
		cout << s1 << s2 << endl;
		return 0;
	}
	melhor1--;
	for(int i=0;i<melhor1;i++){
		cout << s1[i];
	}
	cout << s2 << endl;
	return 0;
}