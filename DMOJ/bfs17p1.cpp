// Ivan Carvalho
// Solution to https://dmoj.ca/problem/bfs17p1
#include <bits/stdc++.h>
using namespace std;
int main(){
	cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0);
	multiset<string> resp;
	int n;
	cin >> n;
	string s;
	while(n--){
		cin >> s;
		if(s.size() <= 10) resp.insert(s);
	}
	cout << resp.size() << endl;
	return 0;
}