// Ivan Carvalho
// Solution to https://www.spoj.com/problems/TAP2015H/
#include <iostream>
#include <algorithm>
#include <string>
#define endl '\n'
using namespace std;
int ordena(int x){
	string s = to_string(x);
	sort(s.begin(),s.end());
	return stoi(s);
}
int func(int x){
	return x - ordena(x);
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	while(cin >> n){
		int resp = 0;
		while(n != 0){
			resp++;
			n = func(n);
		}
		cout << resp << endl;
	}
	return 0;
}