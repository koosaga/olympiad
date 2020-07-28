// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c4p1
#include <bits/stdc++.h>
using namespace std;
int main(){
	string s;
	cin >> s;
	int soma = 0;
	vector<int> e;
	for(char n : s){
		e.push_back(n - '0');
		soma += n - '0';
	}
	sort(e.begin(),e.end());
	if(e[0] != 0 || soma % 3 != 0){
		cout << -1 << endl;
		return 0;
	}
	for(int i = e.size() - 1;i>=0;i--) cout << e[i];
	cout << endl;
	return 0;
}