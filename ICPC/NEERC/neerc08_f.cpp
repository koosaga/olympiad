#include <bits/stdc++.h>
using namespace std;
const int MAXN = 4005;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<lint, lint>;

lint fib[100], n;

string printFib(lint n){
	string s;
	for(int i=80; i; i--){
		if(fib[i] <= n){
			n -= fib[i];
			s.push_back('1');
		}
		else if(s.size()) s.push_back('0');
	}
	s.pop_back();
	return s;
}

map<tuple<lint, lint, lint>, lint> mp;

lint ctZero(int l, lint k, int usedBef){
	if(l == 0) return 0;
	if(k == 0) return 0;
	if(mp.find(make_tuple(l, k, usedBef)) != mp.end()){
		return mp[make_tuple(l, k, usedBef)];
	}
	lint ret = 0;
	if(usedBef){
		ret += ctZero(l - 1, k, 0);
	}
	else{
	ret += ctZero(l - 1, min(k, fib[l + 1]), 0);
	ret += ctZero(l - 1, max(k - fib[l + 1], 0ll), 1) + max(k - fib[l + 1], 0ll);
	}
	return mp[make_tuple(l, k, usedBef)] = ret;
}

int main(){
	freopen("fibonacci.in", "r", stdin);
	freopen("fibonacci.out", "w", stdout);
	cin >> n;
	fib[1] = fib[2] = 1;
	for(int i=3; i<100; i++){
		fib[i] = fib[i-1] + fib[i-2];
	}
	lint ret = 0;
	lint curNum = 0;
	for(int i=1; ; i++){
		if(n <= fib[i] * i){
			ret += ctZero(i - 1, n / i, 1) + n / i;
			curNum += n / i;
			n -= (n / i) * i;
			string s = printFib(curNum + 1);
			for(int i=0; i<n; i++){
				if(s[i] == '1') ret++;
			}
			cout << ret << endl;
			return 0;
		}
		else{
			curNum += fib[i];
			ret += ctZero(i - 1, fib[i], 1) + fib[i];
			n -= fib[i] * i;
		}
	}
}
