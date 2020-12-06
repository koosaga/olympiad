#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int mod = 1e9 + 7;
const int MAXN = 1000005;

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


int n, k, a[MAXN];

int main(){
	int tc = _readInt();
	while(tc--){
		int n = _readInt();
		int k = _readInt();
		for(int i=0; i<n; i++) a[i] = _readInt();
		sort(a, a + n);
		int j = n;
		int ret = 1e9;
		for(int i=0; i<n; i++){
			while(j > 0 && a[j-1]+a[i]>=k) j--;
			for(int q=j-5; q<=j+5; q++){
				if(q != i && q >= 0 && q < n) ret = min(ret, abs(a[i] + a[q] - k));
			}
		}
		lint dap = 0;
		for(int i=0; i<n; i++){
			if(abs(2 * a[i] - k) <= ret) dap--;
			dap += upper_bound(a, a + n, k + ret - a[i]) - lower_bound(a, a + n, k - ret - a[i]);
		}
		cout << dap / 2<< endl;
	}
}
