#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 300005;
const int mod = 1e9 + 7;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n; cin >> n;
	int ret = 1;
	for(int i =  0; i <= n; i++){
		int x; cin >> x; ret += (x << i);
	}
	cout<< ret << endl;
}
