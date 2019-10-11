#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3005;
#define sz(v) ((int)(v).size())
using lint = long long;
const int mod = 16769023;

int main(){
	int n;
	cin >> n;
	n = (n + 1) / 2;
	int dap = 1;
	while(n--) dap = (dap << 1) % mod;
	cout << dap << endl;
}
