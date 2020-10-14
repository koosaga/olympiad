#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 5005;
const int mod = 998244353;

char str[1005][1005];
char buf[1005];


int main(){
	int n, m, k;
	cin >> n >> m >> k;
	if(min(n, m) < k){
		puts("0");
		return 0;
	}
	int r = n / k, c = m / k;
	if(min(n, m) < 2 * k){
		cout << max(r, c) << endl;
		return 0;
	}
	cout << max(1, (r + c - 2) * 2) << endl;
}
