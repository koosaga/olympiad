#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod1 = 1e9 + 409;
const int mod2 = 1e9 + 433;
 
int n;
char str[500005], rstr[500005];
char buf[500005];
 
lint m1[500005], m2[500005];
lint mr1[500005], mr2[500005];
lint p1[500005], p2[500005];
 
void make_hash(char *s, lint *m1, lint *m2, int n){
	for(int i=0; i<n; i++){
		m1[i] = (i ? m1[i-1] : 0) * 3 + s[i] - '0';
		m2[i] = (i ? m2[i-1] : 0) * 3 + s[i] - '0';
		m1[i] %= mod1;
		m2[i] %= mod2;
	}
}
 
lint query(lint *m1, lint *m2, int s, int e){
	lint ret1 = m1[e] - (s ? (m1[s-1] * p1[e - s + 1] % mod1) : 0);
	lint ret2 = m2[e] - (s ? (m2[s-1] * p2[e - s + 1] % mod2) : 0);
	ret1 %= mod1;
	ret1 += mod1;
	ret1 %= mod1;
	ret2 %= mod2;
	ret2 += mod2;
	ret2 %= mod2;
	return ret1 * mod2 + ret2;
}
 
bool okay(int x, int l){
	if(l == 0) return 1;
	lint rhash = query(m1, m2, x, x+l-1);
	lint lhash = query(mr1, mr2, n-x, n-x+l-1);
	return lhash == rhash;
}
 
int main(){
	cin >> n >> str;
	p1[0] = p2[0] = 1;
	for(int i=1; i<n; i++){
		p1[i] = p1[i-1] * 3 % mod1;
		p2[i] = p2[i-1] * 3 % mod2;
	}
	for(int i=0; i<n; i++){
		rstr[i] = '0' + '1'- str[n-1-i];
	}
	make_hash(str, m1, m2, n);
	make_hash(rstr, mr1, mr2, n);
	lint ret = 0;
	for(int i=1; i<n; i++){
		int s = 0, e = min(i, n-i);
		while(s != e){
			int m = (s+e+1)/2;
			if(okay(i, m)) s = m;
			else e = m-1;
		}
		ret += s;
	}
	cout << ret;
}