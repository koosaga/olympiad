#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

set<lint> s;
map<lint, int> mp;

int solve(lint x){
	if(s.find(x) != s.end()) return 1;
	if(mp.find(x) != mp.end()) return mp[x];
	auto it = s.lower_bound(x);
	int ret = solve(*it - x);
	it--;
	ret = min(ret, solve(x - *it));
	return mp[x] = ret + 1;
}

int main(){
	s.insert(1);
	s.insert(2);
	lint a = 1, b = 2;
	while(b <= 5e17){
		s.insert(a + b);
		tie(a, b) = pi(b, a+b);
	}
	int tc;
	cin >> tc;
	while(tc--){
		lint x;
		cin >> x;
		cout << solve(x) << endl;
		mp.clear();
	}
}
