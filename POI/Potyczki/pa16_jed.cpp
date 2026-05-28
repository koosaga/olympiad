#include <bits/stdc++.h>
using namespace std;

int flag = 0;

string f(int n){
	if(n == 1) return "1";
	auto x = f(n / 2);
	if(flag) x = "("+x+")", flag = 0;
	x = "(1+1)*" + x;
	if(n & 1) x = x + "+1", flag = 1;
	return x;
}

int main(){
	int tc;
	cin >> tc;
	while(tc--){
		int n;
		cin >> n;
		cout << f(n) << endl;
		flag = 0;
	}
}