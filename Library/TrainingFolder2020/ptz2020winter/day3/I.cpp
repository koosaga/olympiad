#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 101;
const int mod = 998244353;

int n, k, a[MAXN];

int main(){
	cin >> n >> k;
	fill(a, a + k, 1e9);
	for(int i=1; i<=n; i++){
		lint x;
		cin >> x;
		for(int j=0; j<k; j++){
			if(x&1) a[j] = min(a[j], i);
			x >>= 1;
		}
	}
	sort(a, a + k);
	lint ret = 0;
	for(int i=k-1; i>=0; i--){
		lint sum = (1ll << (k - i - 1)) % mod;
		if(a[i] < 1000) ret += 1ll * a[i] * sum % mod;
	}
	cout << ret %  mod << endl;
}
