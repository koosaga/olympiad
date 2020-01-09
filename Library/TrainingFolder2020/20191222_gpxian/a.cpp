#include <bits/stdc++.h>
#include <any>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int mod = 1e9 + 7;
const int MAXN = 500005;

int main(){
	int n, m; cin >> n >> m;
	lint ret = 0;
	for(int i=0; i<=n; i++){
		for(int j=0; j<=m; j++){
			ret += (1 + 2 * min(n-i, i)) * (1 + 2 *  min(m-j, j));
			ret--;
		}
	}
	assert(ret % 2 == 0);
	cout << ret / 2 << endl;
}
