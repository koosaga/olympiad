#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;

int ptr, l[125], r[125];

int newnode(int lv, int rv){
	l[ptr] = lv;
	r[ptr] = rv;
	return ptr++;
}

pi solve(lint n){ // returns (r + 1, r)
	if(n == 1){
		int r = newnode(-1, -1);
		int l = newnode(r, r);
		return pi(l, r);
	}
	auto s = solve(n / 2);
	if(n % 2 == 0) return pi(newnode(s.first, s.second), newnode(s.second, s.second));
	else return pi(newnode(s.first, s.first), newnode(s.first, s.second));
}

int main(){
	int tc; cin >> tc;
	while(tc--){
		ptr = 0;
		lint n; cin >> n;
		int root = solve(n).second;
		printf("%d\n", ptr);
		for(int i=0; i<ptr; i++) printf("%d %d\n", l[i], r[i]);
		printf("%d\n", root);
	}
}
