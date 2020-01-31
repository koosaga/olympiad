#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1005;

lint trial(lint X, lint N, lint K, lint M){
	lint ret = 0;
	while(K > 0){
		lint val = N / X;
		if(val <= M) break;
		lint itr = min(K, N / val - X);
		itr = max(itr, 1ll);
		if(val > 1e13 / itr) return 1e13;
		N -= val * itr;
		ret += val * itr;
		if(ret > 1e13) return ret;
		K -= itr;
	}
	ret += M * K;
	return ret;
}

int main(){
	freopen("loan.in", "r", stdin);
	freopen("loan.out", "w", stdout);
	lint n, k, t;
	cin >> n >> k >> t;
	lint s = 1, e = 1e13;
	while(s != e){
		lint m = (s+e+1)/2;
		if(trial(m, n, k, t) >= n) s = m;
		else e = m-1;
	}
	cout << s << endl;
}
