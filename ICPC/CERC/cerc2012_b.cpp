#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 200005;
int mod;

lint ipow(lint x, lint p){
	lint ret = 1, piv = x % mod;
	while(p){
		if(p&1) ret *= piv;
		piv *= piv;
		ret %= mod;
		piv %= mod;
		p >>= 1;
	}
	return ret % mod;
}

int n;
char a[MAXN * 2];

int main(){
	int x;
	scanf("%d",&x);
	while(x--){
		a[0] = '0';
		scanf("%s", a + 1);
		n = strlen(a);
		a[n] = '0';
		for(int i=n+1; i<2*n; i++){
			a[i] = a[2*n-i];
		}
		mod = 2 * n;
		lint k = ipow(2, n + 10);
		bool surv = 0;
		for(int i=1; i<=n; i++){
			int tmp = a[(i + k) % mod] ^ a[(i - k + mod) % mod];
			if(tmp) surv = 1;
		}
		puts(surv ? "LIVES" : "DIES");
	}
}
