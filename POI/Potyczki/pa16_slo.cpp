#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

string s;

char nxt[3][3] = {"bc", "ac", "ab"};

void solve(int n, ll k, char l) {
	ll v = (n >= 63) ? (ll)9e18 : (1ll << n) - 1;
	// 빈 칸
	if(n <= 0) {
		puts(s.c_str());
		exit(0);
		exit(1);
	}	

	if(k == 1) {
		puts(s.c_str());
		exit(0);
	}
	k--;

	if(k > v) {
		char d = nxt[l-'a'][1];
		s.push_back(d);
		solve(n-1, k-v, d);
	}else {
		char d = nxt[l-'a'][0];
		s.push_back(d);
		solve(n-1, k, d);
	}

}

int main() {
	int n; ll k;
	scanf("%d%lld", &n, &k);
	char c = 'a';
	if(n <= 63) {
		long long v = (1ll << n) - 1;
		c = 'a';
		if(k > v) k -= v, c += 1;
		if(k > v) k -= v, c += 1;
		if(k > v) {
			return puts("NIE") & 0;
		}
		putchar(c);
		n--;
	}else {
		putchar(c);
		n--;
	}

	solve(n, k, c);
	return 0;
}
