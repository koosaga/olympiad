#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500050;
const int mod = 1e9 + 7;
typedef long long lint;
typedef pair<int, int> pi;

int n;
lint x[MAXN], y[MAXN], z[MAXN];
lint mx[8];

int main(){
	scanf("%d",&n);
	fill(mx, mx + 8, -1e18);
	for(int i=0; i<n; i++){
		scanf("%lld %lld %lld",&x[i],&y[i],&z[i]);
		for(int j=0; j<8; j++){
			lint ans = 0;
			if(j & 1) ans += x[i];
			else ans -= x[i];
			if(j & 2) ans += y[i];
			else ans -= y[i];
			if(j & 4) ans += z[i];
			else ans -= z[i];
			mx[j] = max(mx[j], ans);
		}
	}
	for(int i=0; i<n; i++){
		lint dap = 0;
		for(int j=0; j<8; j++){
			lint ans = 0; 
			if(j & 1) ans += x[i];
			else ans -= x[i];
			if(j & 2) ans += y[i];
			else ans -= y[i];
			if(j & 4) ans += z[i];
			else ans -= z[i];
			dap = max(dap, mx[j] - ans);
		}
		printf("%lld\n", dap);
	}
}
