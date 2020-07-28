// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c2p2
#include <bits/stdc++.h>
using namespace std;
multiset<string> cjt;
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for(int i=1;i<=n;i++){
		string s;
		cin >> s;
		cjt.insert(s);
	}
	for(int i = 1;i<n;i++){
		string s;
		cin >> s;
		cjt.erase(cjt.find(s));
	}
	for(string s : cjt) cout << s << endl;
	return 0;
}