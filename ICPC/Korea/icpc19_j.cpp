#include <bits/stdc++.h>
using namespace std;

int f(int n){
	if(n == 0) return 1;
	if(n % 2 == 1) return (1 << (n/2)) + f(n - 1);
	int ret = 1;
	for(int i=0; i<n/2; i++){
		ret += (3 << i);
	}
	return ret;
}

int main(){
	int n; cin >> n;
	n -= 2;
	for(int i=0; ; i++){
		if(f(i) >= n){
			cout << i << endl;
			return 0;
		}
	}
}
