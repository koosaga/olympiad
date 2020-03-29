#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, int> pi;
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

vector<pi> gph[MAXN];

pi dfs(int x, int p){
	pi ret(0, x);
	for(auto &[u, v] : gph[x]){
		if(v != p){
			auto tmp = dfs(v, x);
			tmp.first += u;
			ret = max(ret, tmp);
		}
	}
	return ret;
}

int main(){
	int tc = _readInt();
	while(tc--){
		int n = _readInt();
		lint ret = 0;
		for(int i=0; i<n-1; i++){
			int s = _readInt();
			int e = _readInt();
			int x = _readInt();
			gph[s].emplace_back(x, e);
			gph[e].emplace_back(x, s);
			ret += 2 * x;
		}
		printf("%lld\n", ret - dfs(dfs(1, 0).second, 0).first);
		for(int i=1; i<=n; i++) gph[i].clear();
	}
}
