#include <bits/stdc++.h>
using namespace std;
using lint = long long;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int main(){
	int tc; cin >> tc;
	while(tc--){
		lint l, v1, v2, t, s;
		cin >> l >> v1 >> v2 >> t >> s;
		if(v2 - v1 <= t){
			puts("0");
			continue;
		}
		lint stk = 1;
		for(int i=0; ; i++){
			double foo = (v2 - (1.0L *l / (s * (i+1)))) / t;
			lint leafNow = max((lint)ceil(foo - 1), 0ll);
			stk = stk - leafNow;
			if(stk <= 0){
				puts("impossible");
				break;
			}
			stk *= 2;
			v2 -= leafNow * t;
			if(v1 + stk * t >= v2){
				cout << i + 1 << endl;
				break;
			}
		}
	}
}
