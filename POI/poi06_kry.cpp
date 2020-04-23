#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = unsigned long long;
using pi = pair<lint, lint>;
const int mod = 1e9 + 7;

int n;
lint a[55];
lint bino[55][55];

lint f(int pos){
	if(pos < 0) return 1;
	vector<lint> v;
	lint rem = 1;
	for(int i=0; i<n; i++){
		if((a[i] >> pos) & 1){
			v.push_back(a[i] & ((1ull << pos) - 1));
			continue;
		}
		rem *= ((a[i] & ((1ull << pos) - 1)) + 1);
	}
	lint dp[55][55] = {};
	dp[0][0] = rem;
	for(int i=0; i<sz(v); i++){
		for(int j=0; j<=i+1; j++){
			dp[i+1][j] = dp[i][j];
			if(j) dp[i+1][j] += dp[i][j-1] * (1+v[i]);
		}
	}
	lint ret = 0;
	for(int i=0; i<=sz(v); i+=2){
		if(i == sz(v)){
			ret += f(pos - 1);
			continue;
		}
		lint val = dp[sz(v)][i];
		for(int j=i+1; j<sz(v); j++){
			val <<= pos;
		}
		ret += val;
	}
	return ret;
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++) cin >> a[i];
	for(int i=0; i<55; i++){
		bino[i][0] = 1;
		for(int j=1; j<=i; j++){
			bino[i][j] = bino[i-1][j] + bino[i-1][j-1];
		}
	}
	cout << (lint)(f(40) - 1ull) << endl;
}
