// Ivan Carvalho
// Solution to https://dmoj.ca/problem/tle17c1p1
#include <bits/stdc++.h>
using namespace std;
int main(){
	string s;
	cin >> s;
	reverse(s.begin(),s.end());
	for(int i = 0;i < s.size();i++){
		if('a' <= s[i] && s[i] <= 'm'){
			s[i] = 'a';
			break;
		}
		else{
			s[i] = 'a';
			if(i  + 1 < s.size()){
				if(s[i+1] != 'z'){
					s[i+1]++;
					break;
				}
			}
			else{
				s.push_back('a');
			}
		}
	}
	reverse(s.begin(),s.end());
	cout << s << endl;
	return 0;
}