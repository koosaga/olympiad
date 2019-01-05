#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
using pi = pair<lint, lint>;
const int MAXN = 2505;

int gcd(int x, int y){ return y ? gcd(y,x %y) : x; }

int main(){
	while(true){
		string s;
		cin >> s;
		if(s == "#") break;
		string seq;
		for(int i=0; i<s.size(); ){
			if(s[i] == 'n') seq.push_back('n'), i += 5;
			else seq.push_back('w'), i += 4;
		}
		reverse(seq.begin(), seq.end());
		s = seq;
		int a = 0;
		if(s[0] == 'w') a = 90;
		for(int i=1; i<s.size(); i++){
			if(s[i] == 'n') a = 2 * a - 90;
			else a = 2 * a + 90;
		}
		int denom = (1 << (s.size() - 1));
		int g = gcd(a, denom);
		a /= g;
		denom /= g;
		if(denom != 1) printf("%d/%d\n", a, denom);
		else printf("%d\n", a);
	}
}
