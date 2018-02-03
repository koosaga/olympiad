#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 1000010;
typedef pair<lint, int> pi;

static char buf[1 << 19]; // size : any number geq than 1024
static int idx = 0;
static int bytes = 0;
static inline int _read() {
    if (!bytes || idx == bytes) {
        bytes = (int)fread(buf, sizeof(buf[0]), sizeof(buf), stdin);
        idx = 0;
    }
    return buf[idx++];
}
static inline int _readInt() {
    int x = 0, s = 1;
    int c = _read();
    while (c <= 32) c = _read();
    if (c == '-') s = -1, c = _read();
    while (c > 32) x = 10 * x + (c - '0'), c = _read();
    if (s < 0) x = -x;
    return x;
}

int n, k; lint a[MAXN];
pi dp[MAXN];

pi trial(lint x){
	pi tmp(0, 0);
	for(int i=1; i<=n; i++){
		dp[i] = dp[i-1];
		dp[i] = max(dp[i-1], pi(tmp.first + a[i] - x, tmp.second - 1));
		tmp = max(tmp, pi(dp[i].first - a[i], dp[i].second));
	}
	return pi(dp[n].first, -dp[n].second);
}

int main(){
	n = _readInt();
	k = _readInt();
	for(int i=1; i<=n; i++){
		a[i] = _readInt() + a[i-1];
	}
	lint s = 0, e = 1e12;
	while(s != e){
		lint m = (s+e)/2;
		if(trial(m).second <= k) e = m;
		else s = m+1;
	}
	cout << trial(s).first + k * s << endl;
}
