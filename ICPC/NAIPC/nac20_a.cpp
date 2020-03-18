#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 998244353;
const int MAXN = 1000005;

lint ipow(int x, int p){
	lint ret = 1, piv = x;
	for(int i=p; i; i>>=1){
		if(i & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
	}
	return ret;
}

int m, n;
int low[MAXN], moe[MAXN];

int main(){
	cin >> m >> n;
	for(int i=2; i<=n; i++){
		for(int j=i; j<=n; j+=i){
			if(!low[j]) low[j] = i;
		}
	}
	moe[1] = 1;
	for(int i=2; i<=n; i++){
		if(low[i] == i) moe[i] = -1;
		else{
			if(low[i / low[i]] == low[i]) moe[i] = 0;
			else moe[i] = -moe[i / low[i]];
		}
	}
	lint ret = 1;
	for(int i=1; i<=n; i++){
		lint foo = ipow(2 * (n / i) + 1, m) - 1;
		ret += (mod + moe[i]) * foo;
		ret %= mod;
	}
	cout << ret << endl;
}
