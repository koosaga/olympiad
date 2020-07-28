// Ivan Carvalho
// Solution to https://dmoj.ca/problem/next1
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3*1e7;
bitset<MAXN> crivo;
vector<int> primos;
int is_prime(int x){
	if(x < MAXN) return !crivo.test(x);
	for(int y : primos){
		if(1LL*y*y > x) break;
		if(x % y == 0) return 0; 
	}
	return 1;
}
int is_semi_prime(int x){
	for(int y : primos){
		if(1LL*y*y > x) break;
		if(x % y == 0){
		    if(is_prime(x/y)) return 1;
		    return 0;
		}
	}
	return 0;
}
int main(){
	int TC;
	crivo.set(0);
	crivo.set(1);
	for(int i = 2;i<MAXN;i++){
		if(crivo.test(i)) continue;
		if(i > 33000) continue;
		primos.push_back(i);
		if(i > 10010) continue;
		for(int j = i*i;j<MAXN;j+=i){
			crivo.set(j);
		}
	}
	scanf("%d",&TC);
	while(TC--){
		int n;
		scanf("%d",&n);
		for(int i = n+1;i<2*1e9;i++){
			if(is_semi_prime(i)){
				printf("%d\n",i);
				break;
			}
		}
	}
	return 0;
}