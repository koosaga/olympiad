#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
using lint = long long;

lint targ;
int ret = 6;

void dfs(lint x, int d){
	if(x == targ){
		ret = min(ret, d);
		return;
	}
	if(d == 5) return;
	for(int i=1; (x >> i); i++){
		dfs(x | (x >> i), d + 1);
	}
}

int main(){
	string str;
	cin >> str;
	if(str[0] == '0'){
		puts("-1");
		return 0;
	}
	reverse(str.begin(), str.end());
	targ = (1ll << str.size()) - 1;
	lint ans = 0;
	for(int i=0; i<str.size(); i++){
		if(str[i] == '1') ans |= (1ll << i);
	}
	dfs(ans, 0);
	cout << ret << endl;
}
