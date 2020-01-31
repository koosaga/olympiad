#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;
const int mod = 998244353;

int inv[MAXN];

lint ipow(int x, int p){
	lint ret = 1, piv = x;
	for(; p; p >>= 1){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
	}
	return ret;
}

lint f(int x, int y, vector<int> z){
	if(x == 0){
		lint dap = 1;
		for(int i=0; i<sz(z); i++){
			for(int j=1; j<=z[i]; j++){
				int sum = z[i] - j + 1;
				for(int k=i+1; k<sz(z); k++){
					if(z[k] >= j) sum++;
				}
				dap = dap * inv[sum] % mod;
			}
		}
		return dap * dap % mod;
	}
	lint ret = 0;
	for(int i=1; i<=y&&i<=x; i++){
		z.push_back(i);
		ret += f(x - i, i, z);
		z.pop_back();
	}
	return ret % mod;
}

int main(){
	int n;
	cin >> n;
	for(int i=1; i<=n; i++) inv[i] = ipow(i, mod - 2);
	lint ret = 0;
	for(int i=1; i<=n/2; i++){
		vector<int> v = {i, i};
		ret += f(n-2*i, i, v);
	}
	ret %= mod;
	for(int i=1; i<=n; i++) ret = ret * i * i % mod;
	cout << ret << endl;
}
