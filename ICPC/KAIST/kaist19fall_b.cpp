#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
const int MAXN = 505;
using lint = long long;
using pi = pair<lint, int>;

int main(){
	int ret = 0, a[11];
	for(int i=0; i<11; i++){
		int x;
		cin >> a[i] >> x;
		ret += 20 * x;
	}
	sort(a, a + 11);
	for(int i=0; i<11; i++) ret += a[i] * (11 - i);
	cout << ret << endl;
}
