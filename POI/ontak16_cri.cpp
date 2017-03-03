#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;

int n, k, a[1000005];
int cp;
lint dp[1000005];
lint c1[1000005], c2[1000005], c3[1000005], c4[1000005], c5[1000005], c6[1000005];

lint solve(int s, int e){
	if(s > e) return a[1];
	if(s == e) return a[s];
	int ns = s;
	while(ns % 6 != (e+1) % 6) ns++;
	int ns2 = s+3;
	while(ns2 % 6 != (e+1) % 6) ns2++;
	lint v1 = min(c3[e+1], c5[ns2]), v2 = min(c4[e+1], c6[ns]);
	if((e - s + 1) % 2 == 0){
		return min({v1 - c1[e+1] - c2[s-2] + 2 * a[0] + 2 * a[1],
				v2 - c1[e+1] - c2[s-1] + a[1],
				v1 - c1[e+1] - c2[s] + a[s] + a[0] + 2 * a[1]});
	}
	else{
		return min({v2 - c1[e+1] - c2[s-2] + a[0],
				v1 - c1[e+1] - c2[s-1] + a[0] + 3ll * a[1],
				v2 - c1[e+1] - c2[s] + a[s]});
	}
}

static char _buffer[1 << 19];
static int _currentChar = 0;
static int _charsNumber = 0;

static inline int _read() {
	if (_charsNumber < 0) {
		exit(1);
	}
	if (!_charsNumber || _currentChar == _charsNumber) {
		_charsNumber = (int)fread(_buffer, sizeof(_buffer[0]), sizeof(_buffer), stdin);
		_currentChar = 0;
	}
	if (_charsNumber <= 0) {
		return -1;
	}
	return _buffer[_currentChar++];
}

static inline int _readInt() {
	int c, x, s;
	c = _read();
	while (c <= 32) c = _read();
	x = 0;
	s = 1;
	if (c == '-') {
		s = -1;
		c = _read();
	}
	while (c > 32) {
		x *= 10;
		x += c - '0';
		c = _read();
	}
	if (s < 0) x = -x;
	return x;
}

int main(){
	n = _readInt();
	k = _readInt();
	for(int i=0; i<n; i++){
		a[i] = _readInt();
	}
	if(n <= k){
		printf("%d", a[n-1]);
		return 0;
	}
	if(k == 2){
		lint p1 = a[0], p2 = a[1];
		for(int i=2; i<n; i++){
			auto t = pi(p2, min(p2 + a[0] + a[i], p1 + a[0] + a[1] * 2 + a[i]));
			tie(p1, p2) = t;
		}
		printf("%lld", p2);
		return 0;
	}
	for(int i=n-1; i>=0; i--){
		c1[i] = c1[i+6] + a[i+2] + a[i+5] + min(2ll * a[0] + 4ll * a[1], a[0] + a[1] + 2ll * a[2]);
	}
	for(int i=0; i<n; i++){
		c2[i] = (i >= 2 ? c2[i-2] : 0) + a[i] + a[0];
	}
	cp = n - 3 * ((n-2) / 4);
	memset(c3, 0x3f, sizeof(c3));
	memset(c4, 0x3f, sizeof(c4));
	memset(c5, 0x3f, sizeof(c5));
	memset(c6, 0x3f, sizeof(c6));
	for(int i=cp+3; i<=n; i+=3){
		c3[i] = c1[i] + c2[i-4] + a[i-1];
		if(i-6 >= 0) c3[i] = min(c3[i], c3[i-6]);
	}
	for(int i=cp; i<=n; i+=3){
		c4[i] = c1[i] + c2[i-1];
		if(i-6 >= 0) c4[i] = min(c4[i], c4[i-6]);
	}
	for(int i=cp+3; i>=5; i-=3){
		c5[i] = c1[i] + c2[i-4] + a[i-1]; 
		c5[i] = min(c5[i], c5[i+6]);
	}
	for(int i=cp; i>=2; i-=3){
		c6[i] = c1[i] + c2[i-1];
		c6[i] = min(c6[i], c6[i+6]);
	}
	lint ans = 1e18, sum = 0;
	for(int i=0; i<=(n-2)/4; i++){
		ans = min(ans, solve(i+2, n-3*i-1) + sum);
		sum += a[i+2] + a[n-3*i-1] + a[0] + a[1];
	}
	printf("%lld\n", ans);
}
