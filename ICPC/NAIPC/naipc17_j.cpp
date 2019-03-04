#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;


int main(){
	string s;
	cin >> s;
	cout << (count(s.begin(), s.end(), 'W') == count(s.begin(), s.end(), 'B'));
}
