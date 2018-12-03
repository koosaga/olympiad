#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;

int extract_one_soinsu(int n){
	for(int i=2; i*i<=n; i++){
		if(n % i == 0) return i;
	}
	return n;
}

pi get_sol(int p, int q){
	if(p < q){
		auto ret = get_sol(q, p);
		return pi(ret.second, ret.first);
	}
	for(int i=1; i<q; i++){
		if((p * q - 1 - p * i) % q == 0){
			return pi(i, (p * q - p * i - 1) / q);
		}
	}
	assert(0);
}

int main(){
	int n; cin >> n;
	int x = extract_one_soinsu(n);
	int m = n;
	while(m % x == 0) m /= x;
	if(m == 1){
		puts("NO");
		return 0;
	}
	int y = extract_one_soinsu(m);
	auto v = get_sol(x, y);
	int r = n / (x * y);
	v.first += r * y - y;
	puts("YES");
	puts("2");
	printf("%d %d\n", v.first, n / x);
	printf("%d %d\n", v.second, n / y);
}