#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int mod = 1e9 + 7;
typedef pair<int, int> pi;
typedef long long lint;

lint n;
vector<lint> divs;
vector<int> moes;

lint ipow(int x, lint p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}

int main(){
	freopen("gymnasts.in", "r", stdin);
	freopen("gymnasts.out", "w", stdout);
	cin >> n;
	for(lint i=1; i*i<=n; i++){
		if(n % i == 0) divs.push_back(i), divs.push_back(n / i);
	}
	sort(divs.begin(), divs.end());
	divs.pop_back();
	divs.resize(unique(divs.begin(), divs.end()) - divs.begin());
	moes.resize(divs.size());
	moes[0] = 1;
	for(int i=0; i<moes.size(); i++){
		for(int j=i+1; j<moes.size(); j++){
			if(divs[j] % divs[i] == 0) moes[j] -= moes[i];
		}
	}
	lint ans = -n+2;
	for(int i=0; i<divs.size(); i++){
		for(int j=i; j<divs.size(); j++){
			if(divs[j] % divs[i] == 0) ans += ipow(2, divs[j] / divs[i]) * moes[i] * ((n / divs[j] - 1) % mod) %mod;
			ans %= mod;
		}
	}
	ans += mod;
	ans %= mod;
	cout << ans << endl;
}
