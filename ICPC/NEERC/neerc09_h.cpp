#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
#define sz(v) int((v).size())

string s;

int cmp(pi a, pi b){
	int v = a.first * b.second - b.first * a.second;
	if(v < 0) return -1;
	if(v == 0) return 0;
	return 1;
}

int main(){
	cin >> s;
	pi cur(count(s.begin(), s.end(), '1'), sz(s));
	pi nxt(0, 0);
	for(int i=0; i<sz(s); i++){
		if(s[i] == '0'){
			nxt.second++;
			if(s[(i+1)%sz(s)] == '1') nxt.first++;
		}
	}
	if(cmp(cur, nxt) == 0) cout << "EQUAL" << endl;
	if(cmp(cur, nxt) < 0) cout << "ROTATE" << endl;
	if(cmp(cur, nxt) > 0) cout << "SHOOT" << endl;
}
