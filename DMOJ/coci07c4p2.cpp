// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci07c4p2
#include <bits/stdc++.h>
using namespace std;
int main(){
	char c;
	vector<int> novo,velho;
	while(cin >> c){
		velho.push_back(c - '0');
	}
	novo = velho;
	next_permutation(novo.begin(),novo.end());
	if(novo > velho){
		for(int x : novo) cout << x;
		cout << endl;
	}
	else{
		cout << 0 << endl;
	}
	return 0;
}