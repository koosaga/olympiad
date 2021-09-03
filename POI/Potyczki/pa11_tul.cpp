#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;


int main(){
	int n; cin >> n;
	vector<int> v(n); for(auto &i : v) cin >> i;
	sort(all(v)); v.resize(unique(all(v)) - v.begin());
	cout << 15000 - sz(v) << endl;
}
