#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int mod = 1e9 + 7;
const int MAXN = 10005;

int n;
string a, b, t;
bool vis[MAXN][3];

bool f(int x, int y){
	if(x == sz(a) && y == sz(b)) return 1;
	if(vis[x][y]) return 0;
	vis[x][y] = 1;
	if(x < sz(a) && t[x+y] == a[x] && f(x+1, y)) return 1;
	if(y < sz(b) && t[x+y] == b[y] && f(x, y+1)) return 1;
	return 0;
}

int main(){
	cin >> n >> a >> t;
	int i, j; cin >> i >> j;
	b.push_back(a[i]);
	b.push_back(a[j]);
	a.erase(a.begin() + j);
	a.erase(a.begin() + i);
	puts(f(0, 0) ? "YES" : "NO");
}
