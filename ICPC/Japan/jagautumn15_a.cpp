#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 3000005;
 
int main(){
	string s, t, u;
	cin >> s >> t;
	int p = 0;
	int ok = 1;
	for(int i=1; i<s.size(); i+=2){
		while(p < t.size() && s[i] != t[p]) p++;
		if(p >= t.size()){
			ok = 0;
			break;
		}
		p++;
	}
	if(ok) puts("Yes");
	else{
		p = 0;
		ok = 1;
		for(int i=0; i<s.size(); i+=2){
			while(p < t.size() && s[i] != t[p]) p++;
			if(p >= t.size()){
				puts("No");
				return 0;
			}
			p++;
		}
		puts("Yes");
	}
}
