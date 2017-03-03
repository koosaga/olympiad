#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

namespace miller_rabin{
	lint mul(lint a, lint b, lint p){
		a %= p, b %= p;
		lint ret = 0;
		while(a){
			if(a&1) ret = (ret + b) % p;
			a >>= 1;
			b = (b << 1) % p;
		}
		return ret;
	}
	lint ipow(lint x, lint y, lint p){
		lint ret = 1, piv = x % p;
		while(y){
			if(y&1) ret = mul(ret, piv, p);
			piv = mul(piv, piv, p);
			y >>= 1;
		}
		return ret;
	}
	bool miller_rabin(lint x, lint a){
		if(x % a == 0) return 0;
		lint d = x - 1;
		while(1){
			lint tmp = ipow(a, d, x);
			if(d&1) return (tmp != 1 && tmp != x-1);
			else if(tmp == x-1) return 0;
			d >>= 1;
		}
	}
	bool isprime(lint n){
		for(auto &i : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
			if(n > 40 && miller_rabin(n, i)) return 0;
			if(n == i) return 1;
		}
		if(n <= 40) return 0;
		return 1;
	}
};

int main(){
	int t;
	cin >> t;
	while(t--){
		int x;
		cin >> x;
		if(x % 2 == 0){
			for(int i=3; ; i++){
				if(miller_rabin::isprime(i) && miller_rabin::isprime(x-i)){
					printf("2\n%d %d\n", i, x-i);
					break;
				}
			}
		}
		else{
			if(miller_rabin::isprime(x)) printf("1\n%d\n",x);
			else{
				printf("3\n3 ");
				x -= 3;
				for(int i=5; ; i++){
					if(miller_rabin::isprime(i) && miller_rabin::isprime(x-i)){
						printf("%d %d\n", i, x-i);
						break;
					}
				}
			}
		}
	}
}
