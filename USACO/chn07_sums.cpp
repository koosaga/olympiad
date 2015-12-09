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
const int mod = 98765431;

int pw(int x, int p){
	lint ret = 1, piv = x;
	while(p){
		if(p&1) ret *= piv;
		piv *= piv;
		ret %= mod;
		piv %= mod;
		p >>= 1;
	}
	return ret;
}

int c[50005], s, n, t;

void process(int x){
	lint offset = 1ll * (n-2) * s % mod;
	offset *= (pw(n-1, x) - 1);
	offset %= mod;
	offset *= pw(pw(n-1, 2) - 1, mod - 2);
	offset %= mod;
	for(int i=0; i<n; i++){
		c[i] = (c[i] + offset) % mod;
	}
	s = (1ll * s * pw(n-1, x)) % mod;
}

void process2(){
	for(int i=0; i<n; i++){
		c[i] = (s - c[i] + mod) % mod;
	}
}

int main(){
	scanf("%d %d",&n,&t);
	for(int i=0; i<n; i++){
		scanf("%d",&c[i]);
		s = (s + c[i]) % mod;
	}
	process(t/2*2);
	if(t%2) process2();
	for(int i=0; i<n; i++){
		printf("%d\n",c[i]);
	}
}