#include <bits/stdc++.h>
using namespace std;

int main(){
	long long n; cin >> n;
	for(int i=1; ; i++){
		if(((i + 1ll) << (i + 1)) > n){
			cout << i << endl;
			return 0;
		}
	}
}
