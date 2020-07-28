// Ivan Carvalho
// Solution to https://dmoj.ca/problem/inaho5
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long llu;
int main(){
	llu n, v = 0;
	cin >> n;
	while(n--){
		ll x;
		cin >> x;
		v += -x;
	}
	if(v == 0) cout << v << endl;
	else cout << "-" << v << endl;
	return 0;
}