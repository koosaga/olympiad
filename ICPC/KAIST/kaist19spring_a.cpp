#include <bits/stdc++.h>
using namespace std;

int n;
string s;
bool good(char x, char y){
	if(x > y) swap(x, y);
	return x == 'B' && y == 'R';
}

int main(){
	cin >> n >> s;
	int ret = 1; // watch out for trivial cases
	for(int i=0; i<n; ){
		if(s[i] == 'V'){
			i++;
			continue;
		}
		int e = i + 1;
		while(e < n && good(s[e-1], s[e])) e++;
		ret = max(ret, e - i);
		i = e;
	}
	cout << ret << endl;
}
