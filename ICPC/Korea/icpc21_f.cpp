#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 1000005;

int n;
lint a[MAXN], b[MAXN], dpl[MAXN][2], dpr[MAXN][2];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= n; i++) cin >> b[i];
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
	for(int i = 1; i <= n; i++){
		dpl[i][0] = max(dpl[i-1][0], abs(a[i] - b[i]));
		dpl[i][1] = max(min(dpl[i-1][0], dpl[i-1][1]), abs(a[i] - b[i + 1]));
	}
	for(int i = n; i; i--){
		dpr[i][0] = max(dpr[i+1][0], abs(a[i] - b[i]));
		dpr[i][1] = max(min(dpr[i+1][0], dpr[i+1][1]), abs(a[i] - b[i - 1]));
	}
	pi ret(2.1e9, 0);
	for(int i = 1; i <= n; i++){
		int l0 = max(dpl[i-1][0], min(dpr[i+1][0], dpr[i+1][1]));
		int l1 = max(min(dpl[i-1][0], dpl[i-1][1]), dpr[i+1][0]);
		ret = min(ret, pi(min(l0, l1), i));
	}
	cout << a[ret.second] << endl;
}
