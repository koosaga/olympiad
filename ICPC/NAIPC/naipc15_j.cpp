#include <bits/stdc++.h>
using namespace std;

string s;
int n;

int pot(int x){
	if(x <= 0) return s.size();
	x -= max(s.back() - 'a', 'z' - s.back());
	if(x <= 0) return s.size() + 1;
	return s.size() + 1 + ((x + 24)/25);
}

int main(){
	cin >> n;
	s.push_back('a');
	int t = pot(n);
	while(n > 0){
		int prv = s.back();
		for(int j='a'; j<='z'; j++){
			s.push_back(j);
			if(pot(n - abs(prv - j)) != t){
				s.pop_back();
			}
			else{
				n -= abs(prv - j);
				break;
			}
		}
	}
	if(n != 0) s.back()++;
	cout << s << endl;
}
