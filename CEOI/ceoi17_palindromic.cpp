#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
const int MAXN = 1000005;
const int mod1 = 1e9 + 409;
const int mod2 = 1e9 + 433;
const int base = 257;

int t, n;
char str[MAXN];
lint h1[MAXN], h2[MAXN];
lint p1[MAXN], p2[MAXN];

lint get(int s, int e){
	lint v2 = h2[e] - h2[s-1] * p2[e-s+1];
	lint v1 = h1[e] - h1[s-1] * p1[e-s+1];
	v1 = (v1 % mod1 + mod1) % mod1;
	v2 = (v2 % mod2 + mod2) % mod2;
	return v1 * mod2 + v2;
}

int main(){
	scanf("%d",&t);
	for(int i=0; i<t; i++){
		scanf("%s", str+1);
		int n = strlen(str+1);
		p1[0] = p2[0] = 1;
		for(int j=1; j<=n; j++){
			h1[j] = h1[j-1] * base + str[j];
			h2[j] = h2[j-1] * base + str[j];
			p1[j] = p1[j-1] * base;
			p2[j] = p2[j-1] * base;
			h1[j] %= mod1, h2[j] %= mod2;
			p1[j] %= mod1, p2[j] %= mod2;
		}
		int ans = 1;
		for(int i=1; i<n+1-i; ){
			int e = i;
			while(e < n+1-e && get(i, e) != get(n + 1 - e, n + 1 - i)) e++;
			if(e >= n + 1 - e) break;
			ans+=2;
			if(e == n - e) ans--;
			i = e+1;
		}
		cout << ans << endl;
	}
}
