#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50005;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())

int main(){
	int t; cin >> t;
	while(t--){
		lint k, m; cin >> k >> m;
		lint ret = 5e18;
		for(int i=1; i<4096; i++){
			lint n = k ^ i;
			if(n == 0) continue;
			lint cur = n;
			for(int j=1; j<=m; j++){
				cur++;
				while(cur <= n + i && gcd(cur, n) > 1) cur++; 
				if(cur > n + i) break;
			}
			if(cur == n + i) ret = min(ret, n);
		}
		if(ret > 4e18) ret = -1;
		printf("%lld\n", ret);
	}
}

