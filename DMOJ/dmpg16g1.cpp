// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmpg16g1
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
ll freq[1010];
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie();
	ll n,maxh = 1001;
	cin >> n;
	while(n--){
		ll davez;
		cin >> davez;
		freq[davez]++;
	}
	ll resp = 0;
	for(ll i = 2;i<=maxh;i++) resp += freq[i]*i;
	resp = max(resp,1LL);
	cout << resp << endl;
	resp = 0;
	ll minimo = min(freq[1],freq[2]);
	freq[3] += minimo;
	freq[1] -= minimo;
	freq[2] -= minimo;
	minimo = freq[1] / 3;
	freq[1] -= minimo*3;
	freq[3] += minimo;
	minimo = freq[1] / 2;
	freq[1] -= minimo*2;
	freq[2] += minimo;
	if(freq[1] == 1){
		for(ll i = 2;i<=maxh;i++){
			if(freq[i]){
				freq[i]--;
				freq[i+1]++;
				break;
			}
		}
	}
	resp = 1;
	for(ll i = 1;i<=maxh;i++){
		while(freq[i]--){
			resp *= i;
			resp %= MOD;
		}
	}
	cout << resp << endl;
	return 0;
}