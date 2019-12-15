#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <memory.h> 
#include <math.h> 
#include <assert.h> 
#include <stack> 
#include <queue> 
#include <map> 
#include <set> 
#include <string> 
#include <algorithm> 
#include <iostream> 
#include <functional>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

lint ipow(int x, int p, int mod){
	lint ret = 1, piv = x;
	for(int i=p; i; i>>=1){
		if(i & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
	}
	return ret % mod;
}

int main(){
	lint n, p, r;
	cin >> n >> p >> r;
	if(n >= 2 * p){
		if(r != 0) puts("-1 -1");
		else puts("2 1");
		return 0;
	}
	if(n >= p){
		if(r == 0){
			if(p != 2) puts("2 1");
			else if(n == 2) puts("-1 -1");
			else puts("3 2");
			return 0;
		}
		else{
			lint ret = 1;
			for(int i=1; i<=n; i++){
				if(i != p) ret *= i;
				ret %= p;
			}
			for(int j=1; j<p; j++){
				if((ret * j) % p == r){
					printf("%d %d\n", p, j);
					return 0;
				}
			}
			return 0;
		}
	}
	if(r == 0){
		puts("-1 -1");
		return 0;
	}
	assert(r != 0);
	lint fact = 1;
	for(int i=1; i<=n; i++){
		fact *= i;
		fact %= p;
	}
	fact = ipow(fact, p - 2, p);
	for(int i=1; i<=n; i++){
		lint dap = (1ll * r * i % p) * fact % p;
		if(dap > 0 && dap < i){
			printf("%d %lld\n", i, dap);
			return 0;
		}
	}
	puts("-1 -1");
}
