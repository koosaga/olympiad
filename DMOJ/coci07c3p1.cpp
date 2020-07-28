// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci07c3p1
#include <bits/stdc++.h>
using namespace std;
int main(){
	vector<int> v(3);
	cin >> v[0] >> v[1] >> v[2];
	sort(v.begin(),v.end());
	if(v[1] - v[0] == v[2] - v[1]){
		cout << v[2] + v[1] - v[0] << endl;
		return 0;
	}
	int cand1 = v[0] + v[2] - v[1];
	if(cand1 - v[0] == v[1] - cand1 && v[2] - v[1] == v[1] - cand1){
		cout << cand1 << endl;
	}
	reverse(v.begin(),v.end());
	if(cand1 - v[0] == v[1] - cand1 && v[2] - v[1] == v[1] - cand1){
		cout << cand1 << endl;
	}
	return 0;
}