#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

string s, t;

int main(){
	while(1){
		cin >> s;
		if(s == "0") break;
		cin >> t;
		for(int i=0; i<t.size(); i++){
			t[i] += s[i%s.size()] - 'A' + 1;
			while(t[i] > 'Z') t[i] -= 26;
		}
		cout << t << endl;
	}
}
