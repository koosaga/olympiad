// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci13c1p1
#include <bits/stdc++.h>
using namespace std;
int main(){
	map<char,int> mapa;
	int n;
	cin >> n;
	while(n--){
		string s;
		cin >> s;
		mapa[s[0]]++;
	}
	int existe = 0;
	for(auto it = mapa.begin();it != mapa.end();it++){
		char c = (*it).first;
		int freq = (*it).second;
		if(freq >= 5){
			existe = 1;
			cout << c;
		}
	}
	if(existe == 0) cout << "PREDAJA";
	cout << endl;
	return 0;
}