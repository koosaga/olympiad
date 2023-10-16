#include <bits/stdc++.h>
using namespace std;
using lint = long long;

lint query(lint x, lint y){
	lint ret = 0;
	for(int i=1; i<=999; i++){
		for(int j=1; i+j<=999; j++){
			if(gcd(i, j) == 1){
				ret += min(x / i, y / j);
			}
		}
	}
	return ret;
}

int main(){
	lint a, b, c, d;
	cin >> a >> b >> c >> d;
	cout << query(b, d) - query(a-1, d) - query(b, c-1) + query(a-1, c-1) << endl;
}
