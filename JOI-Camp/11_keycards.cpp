    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>
    #include <limits.h>
    #include <stack>
    #include <queue>
    #include <map>
    #include <set>
    #include <algorithm>
    #include <string>
    #include <functional>
    #include <vector>
    #include <numeric>
    #include <deque>
    #include <utility>
    #include <bitset>
    #include <iostream>
    using namespace std;
    typedef long long lint;
    typedef long double llf;
    typedef pair<int, int> pi;
    const int mod = 1e9 + 7;
     
    int p2[1000005];
    lint fact[1000005], invf[1000005];
    int n, k;
     
    int pw(int x, int p){
    	lint piv = x, ret = 1;
    	while(p){
    		if(p&1) ret *= piv;
    		piv *= piv;
    		ret %= mod;
    		piv %= mod;
    		p >>= 1;
    	}
    	return ret;
    }
     
    lint choose(int n, int k){
    	return fact[n] * (invf[k] * invf[n-k] % mod) % mod;
    }
     
    int main(){
    	p2[0] = 1;
    	scanf("%d %d",&n,&k);
    	if(n == k){
    		puts("1");
    		return 0;
    	}
    	for(int i=1; i<=n; i++){
    		p2[i] = (p2[i-1] << 1) % (mod - 1);
    	}
    	fact[0] = invf[0] = 1;
    	for(int i=1; i<=n; i++){
    		fact[i] = fact[i-1] * i % mod;
    		invf[i] = pw(fact[i], mod - 2);
    	}
    	lint ret = choose(n, k);
    	lint tmp = 0;
    	for(int i=0; i<=n-k; i++){
    		lint piv = pw(2, p2[n-k-i]) * choose(n-k, i) % mod;
    		if(i % 2 == 0) tmp += piv;
    		else tmp += mod - piv;
    		tmp %= mod;
    	}
    	printf("%lld\n",ret * tmp % mod);
    }