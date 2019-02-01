#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 1005;

static char buf[1 << 19];
static int idxx = 0, bytes = 0;

static inline int _read(){
	if(!bytes || idxx == bytes){
		bytes = (int)fread(buf, sizeof(buf[0]), sizeof(buf), stdin);
		idxx = 0;
	}
	return buf[idxx++];
}

static inline int _readInt(){
	int x = 0, s = 1;
	int c = _read();
	while(c <= 32) c = _read();
	if(c == '-') s = -1, c =_read();
	while(c > 32) x = 10 * x + c - '0', c = _read();
	if(s < 0)x = -x;
	return x;
}

int n, m;
pi a[MAXN];
bool chk[MAXN];
int ang[MAXN][MAXN];
int idx[MAXN][MAXN];

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

inline bool inside(int x, int y, int z){
	if(x < z) return x < y && y < z;
	else return x < y || y < z;
}

int count(int x, int y, int z){
	int ans = 0;
	if(idx[x][y] < idx[x][z]){
		for(int j=idx[x][y]+1; j<idx[x][z]; j++){
			int v = ang[x][j];
			if(!chk[v] && inside(idx[y][z], idx[y][v], idx[y][x])){
				ans++;
			}
		}
	}
	else{
		for(int j=idx[x][y]+1; j<n-1; j++){
			int v = ang[x][j];
			if(!chk[v] && inside(idx[y][z], idx[y][v], idx[y][x])){
				ans++;
			}
		}
		for(int j=0; j<idx[x][z]; j++){
			int v = ang[x][j];
			if(!chk[v] && inside(idx[y][z], idx[y][v], idx[y][x])){
				ans++;
			}
		}
	}
	return ans;
}

bool vis[MAXN];

int main(){
	n = _readInt();
	m = _readInt();
	for(int i=0; i<n; i++){
		a[i].first = _readInt();
		a[i].second = _readInt();
		int ptr = 0;
		for(int j=0; j<n; j++){
			if(i != j){
				ang[i][ptr++] = j;
			}
		}
	}
	for(int i=0; i<n; i++){
		sort(ang[i], ang[i] + n - 1, [&](int x, int y){
			bool flag1 = a[i] < a[x];
			bool flag2 = a[i] < a[y];
			if(flag1 != flag2) return flag1 > flag2;
			return ccw(a[i], a[x], a[y]) > 0;
		});
		for(int j=0; j<n-1; j++){
			idx[i][ang[i][j]] = j;
		}
	}
	for(int i=0; i<m; i++){
		vector<int> v;
		int x = _readInt();
		v.resize(x);
		for(auto &j : v) j = _readInt() - 1;
		if(x == n){
			puts("0");
			continue;
		}
		reverse(v.begin(), v.end());
		for(auto &j : v) chk[j] = 1;
		int ans = 0;
		for(int j=2; j<v.size(); j++){
			if(ccw(a[v[0]], a[v[j-1]], a[v[j]]) > 0) ans += count(v[0], v[j-1], v[j]);
			else ans -= count(v[0], v[j], v[j-1]);
		}
		for(auto &j : v) chk[j] = 0;
		printf("%d\n", ans);
	}
}