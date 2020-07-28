// Ivan Carvalho
// Solution to https://dmoj.ca/problem/bts17p1
#include <bits/stdc++.h>
using namespace std;
int main(){
	int flag = 0;
	string s;
	while(cin >> s){
		if('A' <= s[0] && s[0] <= 'Z' && flag) cout << ". ";
		else if(flag){
			cout << " ";
		}
		else{
			flag = 1;
		}
		cout << s;
	}
	cout << "." << endl;
	return 0;
}